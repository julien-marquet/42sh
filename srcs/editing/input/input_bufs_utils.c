/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_bufs_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:25 by jmarquet    ###    #+. /#+    ###.fr     */
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

int		prepare_input(t_input_data *input_data)
{
	if (ask_start_position(input_data->start_pos) == 1)
		return (1);
	print_prompt(input_data->stored_buf->len > 0 ? PROMPT_MULTI : PROMPT_SIMPLE);
	input_data->rel_cur_pos = 0;
	return (0);
}

int		merge_bufs(t_input_data *input_data, t_list *hist_copy, char *here_doc)
{
	if (input_data->stored_buf->len > 0)
	{
		if (insert_dyn_buf(input_data->stored_buf->buf, input_data->active_buf, 0) == 1)
			return (1);
		reset_dyn_buf(input_data->stored_buf);
	}
	if (output_is_ready(input_data->active_buf, here_doc) == false)
	{
		ft_swap((void **)(&(input_data->active_buf)), (void **)(&(input_data->stored_buf)));
		if (history_navigate(input_data, hist_copy, HIST_RESET) == -1)
			return (free_hist_copy(&hist_copy, 1));
	}
	return (0);
}



