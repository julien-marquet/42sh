/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_control.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:42:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/06 23:39:49 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input_control.h"
#include "input/cursor.h"
#include "utils/dyn_buf.h"
#include "input/prompt.h"

int		clear_line(void)
{
	t_cur_abs_pos	pos;

	if (get_cursor_position(&pos) != 0)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), 0, pos.row), 1, ft_putchar) != 0)
		return (1);
	if (tputs(tgetstr("cd", NULL), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int		delete_prev_char(t_input_data *input_data)
{
	if (del_at_dyn_buf(input_data->input_buf, input_data->rel_cur_pos - 1) == 1)
	{
		if (move_cursor_left(input_data) != 0)
			return (1);
		update_vbuf(input_data->input_buf->buf, input_data->rel_cur_pos);
	}
	return (0);
}

void	delete_cur_char(t_input_data *input_data)
{
	if (del_at_dyn_buf(input_data->input_buf, input_data->rel_cur_pos) == 1)
		update_vbuf(input_data->input_buf->buf, input_data->rel_cur_pos);
}

/*
**	input will be
*/

int		update_vbuf(char *buf, size_t rel_cur_pos)
{
	t_cur_abs_pos	pos;

	if (get_cursor_position(&pos) != 0)
		return (1);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_putstr(&(buf[rel_cur_pos]));
	tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar); // remove remaining lines
	return (0);
}
