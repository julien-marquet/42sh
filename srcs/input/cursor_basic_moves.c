/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_basic_moves.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:56:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 17:15:13 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/cursor_basic_moves.h"

int		move_cursor_left(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos > 0)
	{
		input_data->rel_cur_pos -= 1;
		if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
			return (1);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}

int		move_cursor_right(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos < input_data->active_buf->len)
	{
		input_data->rel_cur_pos += 1;
		if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
			return (1);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}