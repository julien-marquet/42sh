/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_control.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:42:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 01:22:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input_control.h"
#include "input/cursor.h"

int		clear_line(void)
{
	t_cur_abs_pos	pos;

	if (get_cursor_position(&pos) != 0)
		return (1);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos.row), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	return (0);
}

int		delete_char(t_input_data *input_data)
{
	if (input_data->rel_cur_pos > 0)
	{
		ft_strcpy(&(input_data->input_buf->buf[input_data->rel_cur_pos - 1]),
	&(input_data->input_buf->buf[input_data->rel_cur_pos]));
		input_data->input_buf->buf[input_data->input_buf->len - 1] = '\0';
		input_data->input_buf->len -= 1;
		input_data->rel_cur_pos -= 1;
	}
	return (0);
}
