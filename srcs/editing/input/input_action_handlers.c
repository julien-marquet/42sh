/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_action_handlers.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:11:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 08:17:36 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_action_handlers.h"

int		handle_user_reset(t_input_data *input_data)
{
	if (input_data->sig_call == 1 && get_eof() == 0)
	{
		if (get_eof())
		{
			if (input_data->active_buf->len > 0 && input_data->active_buf->buf[0] != '\n')
			{
				if (add_to_history_list(&(input_data->history_list), input_data->active_buf->buf, input_data->active_buf->len + 1) == NULL)
					return (1);
			}
			else if (input_data->stored_buf->len > 0 && input_data->stored_buf->buf[0] != '\n')
			{
				if (add_to_history_list(&(input_data->history_list), input_data->stored_buf->buf, input_data->stored_buf->len + 1) == NULL)
					return (1);
			}
		}
		reset_input(input_data);
		input_data->sig_call = 0;
	}
	return (0);
}

int		handle_enter(t_input_data *input_data)
{
	t_cur_abs_pos copy_pos;

	if (get_cursor_position(&copy_pos, input_data->active_buf, input_data->active_buf->len ,input_data->start_pos) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), copy_pos.col, copy_pos.row), 1, ft_putchar) != 0)
		return (1);
	if (insert_dyn_buf("\n", input_data->active_buf, input_data->active_buf->len) == 1)
		return (1);
	write(1, "\n", 1);
	input_data->rel_cur_pos = input_data->active_buf->len;
	input_data->enter = 1;
	return (0);
}

int		clear_input(t_input_data *input_data)
{
	input_data->start_pos->row = 0;
	if (print_anew(input_data->start_pos, input_data->active_buf, input_data->rel_cur_pos) == 1)
		return (1);
	return (0);
}