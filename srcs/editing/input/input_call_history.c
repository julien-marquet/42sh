/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_call_history.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:01:37 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_call_history.h"

int		hist_move_up(t_input_data *input_data, t_list *hist_copy)
{
	if (history_navigate(input_data, hist_copy, HIST_NEXT) == -1)
		return (1);
	if (print_anew(input_data->start_pos, input_data->active_buf, input_data->rel_cur_pos) == 1)
		return (1);
	if (update_start_position(input_data->active_buf, input_data->start_pos) == 1)
		return (1);
	return (0);
}

int		hist_move_down(t_input_data *input_data, t_list *hist_copy)
{
	if (history_navigate(input_data, hist_copy, HIST_PREV) == -1)
		return (1);
	if (print_anew(input_data->start_pos, input_data->active_buf, input_data->rel_cur_pos) == 1)
		return (1);
	if (update_start_position(input_data->active_buf, input_data->start_pos) == 1)
		return (1);
	return (0);
}

int		free_hist_copy(t_list **hist_copy, int res)
{
	if (hist_copy && *hist_copy)
	{
		void (*del)(void *, size_t);
		del = free_lstnode;
		ft_lstdel(hist_copy, del);
		*hist_copy = NULL;
	}
	return (res);
}

int		dup_history(t_input_data *input_data, t_list **hist_copy)
{
	if (input_data->history_list != NULL)
	{
		if ((*hist_copy = ft_lstdup(input_data->history_list)) == NULL)
			return (1);
	}
	else
		*hist_copy = NULL;
	return (0);
}