/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_control.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:42:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 18:37:39 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input_control.h"
#include "input/cursor.h"
#include "utils/dyn_buf.h"

int		clear_line(void)
{
	t_cur_abs_pos	pos;

	if (get_cursor_position(&pos) != 0)
		return (1);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos.row), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	return (0);
}

int		delete_prev_char(t_input_data *input_data)
{
	if (del_at_dyn_buf(input_data->input_buf, input_data->rel_cur_pos - 1) == 1)
	{
		if (move_cursor_left(input_data) != 0)
			return (1);
		update_vbuf(input_data);
	}
	return (0);
}

void	delete_cur_char(t_input_data *input_data)
{
	del_at_dyn_buf(input_data->input_buf, input_data->rel_cur_pos);
}

int		update_vbuf(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (get_cursor_position(&pos) != 0)
		return (1);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_putstr(&(input_data->input_buf->buf[input_data->rel_cur_pos]));
	tputs(tgoto(tgetstr("cm", NULL), pos.col - 1, pos.row), 1, ft_putchar);
	return (0);
}
