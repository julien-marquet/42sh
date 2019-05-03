/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_main_process.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:55:56 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 13:29:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_main_process.h"
#include "editing/input/completion/completion.h"

static int		get_buf(t_dyn_buf *build_buf)
{
	char	buf[READ_SIZE + 1];
	ssize_t	ret;

	ret = READ_SIZE;
	ft_bzero(buf, READ_SIZE + 1);
	ret = read(0, &buf, READ_SIZE);
	if (ret == -1 || insert_dyn_buf(buf, build_buf, build_buf->len) != 0)
		return (1);
	else if (ret == 0)
		return (0);
	return (0);
}

static int		process_buf(t_input_data *input_data, t_sh_state *sh_state, t_list *hist_copy)
{
	if (is_sig(input_data->build_buf->buf) == 1)
	{
		if (handle_sig(input_data, sh_state) == 1)
			return (1);
	}
	else if (get_search_mode() == 1)
	{
		if (handle_search_input(sh_state, input_data) == 1)
			return (1);
	}
	else
	{
		if (is_capability(input_data->build_buf->buf) == 1)
		{
			if (handle_capabilities(input_data, hist_copy, sh_state) == 1)
				return (1);
		}
		else
		{
			reset_selection(input_data->start_pos, input_data->active_buf,
		&input_data->rel_cur_pos);
			if (handle_insertion(input_data) == -1)
				return (1);
		}
	}
	return (0);
}

static int		process_entry(t_input_data *input_data, t_sh_state *sh_state, t_list *hist_copy)
{
	while (get_eof() != 2 && input_data->sig_call == 0 && sh_state->exit_sig == 0 && (input_data->active_buf->len == 0 || input_data->enter == 0))
	{
		if (input_data->build_buf->len == 0)
		{
			if (get_buf(input_data->build_buf) == 1)
				return (1);
		}
		if (process_buf(input_data, sh_state, hist_copy) == 1)
			return (1);
		if (input_data->processed_chars > 0)
		{
			shift_dyn_buf(input_data->build_buf, input_data->processed_chars);
			input_data->processed_chars = 0;
		}
	}
	input_data->enter = 0;
	return (0);
}

int		handle_input(t_sh_state *sh_state, t_input_data *input_data,
char *here_doc)
{
	t_list	*hist_copy;
	int		valid_here_doc;

	input_data->sig_call = 0;
	if (dup_history(input_data, &hist_copy) == 1)
		return (1);
	valid_here_doc = 0;
	input_data->here_doc = here_doc;
	set_eof(here_doc != NULL);
	while (valid_here_doc != 2 && input_data->sig_call == 0 &&
(input_data->active_buf->len == 0 || input_data->stored_buf->len > 0))
	{
		if (prepare_input(input_data, (const char *)here_doc) == 1)
			return (free_hist_copy(&hist_copy, 1));
		if (process_entry(input_data, sh_state, hist_copy) == 1)
			return (free_hist_copy(&hist_copy, 1));
		if ((valid_here_doc = merge_bufs(input_data, hist_copy, here_doc)) == 1)
			return (free_hist_copy(&hist_copy, 1));
	}
	if (here_doc == NULL && input_data->active_buf->len > 0 &&
input_data->active_buf->buf[0] != '\n')
	{
		if (add_to_history_list(&(input_data->history_list),
	input_data->active_buf->buf, input_data->active_buf->len) == NULL)
			return (free_hist_copy(&hist_copy, 1));
	}
	if (handle_user_reset(input_data) == 1)
		return (free_hist_copy(&hist_copy, 1));
	if (history_navigate(input_data, hist_copy, HIST_RESET) == -1)
		return (free_hist_copy(&hist_copy, 1));
	return (free_hist_copy(&hist_copy, 0));
}
