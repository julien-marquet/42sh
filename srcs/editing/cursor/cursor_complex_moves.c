/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_complex_moves.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:56:27 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:49:36 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/cursor/cursor_complex_moves.h"

int			goto_end(t_input_data *input_data)
{
	t_cur_abs_pos pos;

	input_data->rel_cur_pos = input_data->active_buf->len;
	if ((get_cursor_position(&pos, input_data->active_buf,
input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int			goto_home(t_input_data *input_data)
{
	t_cur_abs_pos pos;

	input_data->rel_cur_pos = 0;
	if ((get_cursor_position(&pos, input_data->active_buf,
input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int			move_to_next_word(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	input_data->rel_cur_pos += get_next_move_num(input_data);
	if ((get_cursor_position(&pos, input_data->active_buf,
input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int			move_to_prev_word(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	input_data->rel_cur_pos -= get_prev_move_num(input_data);
	if ((get_cursor_position(&pos, input_data->active_buf,
input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}
