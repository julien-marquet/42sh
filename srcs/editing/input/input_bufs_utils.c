/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_bufs_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 07:48:01 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_bufs_utils.h"

void	reset_input(t_input_data *input_data)
{
	reset_dyn_buf(input_data->stored_buf);
	reset_dyn_buf(input_data->active_buf);
	input_data->rel_cur_pos = 0;
}

int		prepare_input(t_input_data *input_data, const char *here_doc)
{
	if (ask_start_position(input_data->start_pos) == 1)
		return (1);
	print_prompt(here_doc != NULL || input_data->stored_buf->len > 0 ?
PROMPT_MULTI : PROMPT_SIMPLE);
	input_data->rel_cur_pos = 0;
	return (0);
}

int		merge_bufs(t_input_data *input_data, t_list *hist_copy, char *here_doc)
{
	int		valid_here_doc;

	valid_here_doc = -1;
	if (here_doc != NULL)
	{
		valid_here_doc = get_eof() == 2 ||
	here_doc_is_closed(input_data->active_buf, here_doc);
	}
	if (valid_here_doc == 1 && get_eof() != 2)
	{
		ft_swap((void **)(&(input_data->active_buf)),
	(void **)(&(input_data->stored_buf)));
		reset_dyn_buf(input_data->stored_buf);
	}
	else if (input_data->stored_buf->len > 0)
	{
		if (insert_dyn_buf(input_data->stored_buf->buf,
	input_data->active_buf, 0) == 1)
			return (1);
		reset_dyn_buf(input_data->stored_buf);
	}
	if (output_is_ready(input_data->active_buf, valid_here_doc) == false)
	{
		ft_swap((void **)(&(input_data->active_buf)),
	(void **)(&(input_data->stored_buf)));
		if (history_navigate(input_data, hist_copy, HIST_RESET) == -1)
			return (free_hist_copy(&hist_copy, 1));
	}
	return (valid_here_doc ? 2 : 0);
}



