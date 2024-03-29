/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_bufs_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 21:18:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_bufs_utils.h"

void		reset_input(t_input_data *input_data)
{
	reset_dyn_buf(input_data->stored_buf);
	reset_dyn_buf(input_data->active_buf);
	input_data->rel_cur_pos = 0;
}

int			prepare_input(t_input_data *input_data, const char *here_doc)
{
	if (ask_start_position(input_data->start_pos) == 1)
		return (1);
	print_prompt(here_doc != NULL || input_data->stored_buf->len > 0 ?
PROMPT_MULTI : PROMPT_SIMPLE);
	input_data->rel_cur_pos = 0;
	return (0);
}

static int	handle_here_doc_merge(t_input_data *input_data,
char *here_doc, int *valid_here_doc)
{
	int		res;

	res = 0;
	if (here_doc != NULL)
	{
		*valid_here_doc = get_eof() == 2 ||
	here_doc_is_closed(input_data->active_buf, here_doc);
	}
	if (*valid_here_doc == 1 && get_eof() != 2)
	{
		res = 1;
		ft_swap((void **)(&(input_data->active_buf)),
	(void **)(&(input_data->stored_buf)));
		reset_dyn_buf(input_data->stored_buf);
	}
	return (res);
}

void		remove_end_slash(t_dyn_buf *dyn_buf)
{
	if (dyn_buf->len > 0 && is_escaped(dyn_buf->buf, dyn_buf->len - 1))
	{
		if (is_quoted(dyn_buf->buf, dyn_buf->len - 1) != 1)
		{
			dyn_buf->buf[dyn_buf->len - 2] = '\0';
			dyn_buf->len -= 2;
		}
	}
}

int			merge_bufs(t_sh_state *sh_state, t_input_data *input_data,
t_list *hist_copy, char *here_doc)
{
	int		valid_here_doc;

	valid_here_doc = -1;
	if (save_history_before_ctrl_c(input_data, sh_state) == 1)
		return (1);
	if (handle_here_doc_merge(input_data, here_doc,
&valid_here_doc) != 1 && input_data->stored_buf->len > 0)
	{
		if (insert_dyn_buf(input_data->stored_buf->buf,
	input_data->active_buf, 0) == 1)
			return (1);
		reset_dyn_buf(input_data->stored_buf);
	}
	if (output_is_ready(input_data->active_buf, valid_here_doc) == false)
	{
		remove_end_slash(input_data->active_buf);
		ft_swap((void **)(&(input_data->active_buf)),
	(void **)(&(input_data->stored_buf)));
		if (history_navigate(input_data, hist_copy, HIST_RESET) == -1)
			return (free_hist_copy(&hist_copy, 1));
	}
	return (valid_here_doc ? 2 : 0);
}
