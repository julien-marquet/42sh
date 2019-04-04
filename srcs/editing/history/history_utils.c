/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:19:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:13:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/history/history_utils.h"

static int		navigate_to_initial_input(t_input_data *input_data, int old_i, t_list *hist_copy)
{
	if (old_i >= 1 + (input_data->stored_buf->len > 0))
	{
		if (edit_history_index(hist_copy, old_i - (1 + (input_data->stored_buf->len > 0)), input_data->active_buf->buf) == NULL)
			return (1);
	}
	if (set_dyn_buf(input_data->active_buf, input_data->initial_buf->buf) == 1)
		return (1);
	return (0);
}

static int		move_from_initial_input(int old_i, t_input_data *input_data)
{
	if (old_i == 0)
	{
		if (set_dyn_buf(input_data->initial_buf, input_data->active_buf->buf) == 1)
			return (1);
	}
	return (0);
}

static int		navigate_to_stored_buf(t_input_data *input_data, int old_i, t_list *hist_copy)
{
	if (old_i >= 1 + (input_data->stored_buf->len > 0))
	{
		if (edit_history_index(hist_copy, old_i - (1 + (input_data->stored_buf->len > 0)), input_data->active_buf->buf) == NULL)
			return (1);
	}
	if (set_n_dyn_buf(input_data->active_buf, input_data->stored_buf->buf, input_data->stored_buf->len - 1) == 1)
		return (1);
	return (0);
}

static int		navigate_in_history(t_input_data *input_data, t_list *hist_copy, int index, int old_i)
{
	t_list	*hist_entry;

	if ((hist_entry = get_history_index(hist_copy,
index - (1 + (input_data->stored_buf->len > 0)))) == NULL)
		index = old_i;
	else
	{
		if (old_i >= 1 + (input_data->stored_buf->len > 0))
		{
			if (edit_history_index(hist_copy, old_i - (1 + (input_data->stored_buf->len > 0)), input_data->active_buf->buf) == NULL)
				return (-1);
		}
		if (set_dyn_buf(input_data->active_buf, (char *)(hist_entry->content)) == 1)
			return (-1);
	}
	return (index);
}

int		navigate(t_input_data *input_data, t_list *hist_copy, int index, int old_i)
{
	if (index == 0)
	{
		if (navigate_to_initial_input(input_data, old_i, hist_copy) == 1)
			return (-1);
	}
	else
	{
		if (move_from_initial_input(old_i, input_data) == 1)
			return (-1);
		if (index == 1 && input_data->stored_buf->len > 0)
		{
			if (navigate_to_stored_buf(input_data, old_i, hist_copy) == 1)
				return (-1);
		}
		else
		{
			if ((index = navigate_in_history(input_data, hist_copy, index, old_i)) == -1)
				return (-1);
		}
	}
	return (index);
}