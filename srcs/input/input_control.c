/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_control.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:42:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 10:05:45 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input_control.h"
#include "input/cursor.h"
#include "utils/dyn_buf.h"
#include "input/prompt.h"

int		print_anew(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (tputs(tgoto(tgetstr("cm", NULL), input_data->start_pos->col,
input_data->start_pos->row), 1, ft_putchar) != 0)
		return (1);
	if (tputs(tgetstr("cd", NULL), 1, ft_putchar) != 0)
		return (1);
	print_prompt(PROMPT_NO_SET);
	write(1, input_data->input_buf->buf, input_data->input_buf->len);
	get_cursor_position(&pos, input_data->input_buf, input_data->rel_cur_pos,
input_data->start_pos);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int		delete_prev_char(t_input_data *input_data)
{
	if (del_at_dyn_buf(input_data->input_buf, input_data->rel_cur_pos - 1) == 1)
	{
		if (move_cursor_left(input_data) != 0)
			return (1);
		print_anew(input_data);
	}
	return (0);
}

void	delete_cur_char(t_input_data *input_data)
{
	if (del_at_dyn_buf(input_data->input_buf, input_data->rel_cur_pos) == 1)
		print_anew(input_data);
}

int		insertn_chars(t_input_data *input_data, size_t n, int force)
{
	if (force == 0)
		input_data->rel_cur_pos += n;
	if (force == 0 && input_data->rel_cur_pos == input_data->input_buf->len)
	{
		write(1, input_data->build_buf->buf, n);
	}
	else
	{
		print_anew(input_data);
	}
	return (0);
}
