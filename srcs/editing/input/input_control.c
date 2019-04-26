/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_control.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:42:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 06:28:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_control.h"

int		print_anew(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf,
size_t rel_cur_pos)
{
	t_cur_abs_pos	pos;
	int				start;

	if (tputs(tgoto(tgetstr("cm", NULL), start_pos->col,
start_pos->row), 1, ft_putchar) != 0)
		return (1);
	if (tputs(tgetstr("cd", NULL), 1, ft_putchar) != 0)
		return (1);
	print_prompt(PROMPT_NO_SET);
	if ((start = get_first_selected_char(active_buf)) != -1)
	{
		write(1, active_buf->buf, start);
		tputs(tgetstr("so", NULL), 1, ft_putchar);
		write(1, &(active_buf->buf[start]), ft_abs(active_buf->sel_len));
		tputs(tgetstr("se", NULL), 1, ft_putchar);
		write(1, &(active_buf->buf[start + ft_abs(active_buf->sel_len)]),
	active_buf->len - ft_abs(active_buf->sel_len) - start);
	}
	else
		write(1, active_buf->buf, active_buf->len);
	if (get_cursor_position(&pos, active_buf, rel_cur_pos, start_pos) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int		delete_prev_char(t_input_data *input_data)
{
	if (del_at_dyn_buf(input_data->active_buf, input_data->rel_cur_pos - 1) == 1)
	{
		if (move_cursor_left(input_data->start_pos, input_data->active_buf, &input_data->rel_cur_pos) != 0)
			return (1);
		if (print_anew(input_data->start_pos, input_data->active_buf, input_data->rel_cur_pos) == 1)
			return (1);
	}
	return (0);
}

int		delete_cur_char(t_input_data *input_data)
{
	if (del_at_dyn_buf(input_data->active_buf, input_data->rel_cur_pos) == 1)
	{
		if (print_anew(input_data->start_pos, input_data->active_buf, input_data->rel_cur_pos) == 1)
			return (1);
	}
	return (0);
}

int		insertn_chars(t_input_data *input_data, const char *str, size_t n, int force)
{
	if (update_start_position(input_data->active_buf, input_data->start_pos) == 1)
		return (1);
	if (force == 0)
		input_data->rel_cur_pos += n;
	if (force == 0 && input_data->rel_cur_pos == input_data->active_buf->len)
	{
		write(1, str, n);
		if (tputs(tgetstr("cd", NULL), 1, ft_putchar) != 0)
			return (1);
	}
	else
	{
		if (print_anew(input_data->start_pos, input_data->active_buf, input_data->rel_cur_pos) == 1)
			return (1);
	}
	return (0);
}
