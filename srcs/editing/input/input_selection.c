/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_selection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 23:12:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 01:06:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_selection.h"

int		expand_selection_right(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf,
size_t *rel_cur_pos)
{
	if (*rel_cur_pos < active_buf->len)
	{
		if (active_buf->sel_start == -1)
		{
			active_buf->sel_start = *rel_cur_pos;
			active_buf->sel_len = 1;
		}
		else
			active_buf->sel_len++;
		if (move_cursor_right(start_pos, active_buf, rel_cur_pos) == 1)
			return (1);
		if (print_anew(start_pos, active_buf, *rel_cur_pos) == 1)
			return (1);
	}
	return (0);
}

int		expand_selection_left(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf,
size_t *rel_cur_pos)
{
	if (*rel_cur_pos > 0)
	{
		if (active_buf->sel_start == -1)
		{
			active_buf->sel_start = *rel_cur_pos;
			active_buf->sel_len = -1;
		}
		else
			active_buf->sel_len--;
		if (move_cursor_left(start_pos, active_buf, rel_cur_pos) == 1)
			return (1);
		if (print_anew(start_pos, active_buf, *rel_cur_pos) == 1)
			return (1);
	}
	return (0);
}

int		reset_selection(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf,
size_t *rel_cur_pos)
{
	active_buf->sel_start = -1;
	active_buf->sel_len = 0;
	return (print_anew(start_pos, active_buf, *rel_cur_pos));
}

int		get_first_selected_char(t_dyn_buf *active_buf)
{
	if (active_buf->sel_start == -1)
		return (-1);
	if (active_buf->sel_len > 0)
		return (active_buf->sel_start);
	else if (active_buf->sel_len < 0)
		return (active_buf->sel_start + active_buf->sel_len);
	else
		return (-1);
}
