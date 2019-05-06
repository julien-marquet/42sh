/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_basic_moves.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:56:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:48:47 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/cursor/cursor_basic_moves.h"

int		move_cursor_left(t_cur_abs_pos *start_pos,
t_dyn_buf *active_buf, size_t *rel_cur_pos)
{
	t_cur_abs_pos	pos;

	if (*rel_cur_pos > 0)
	{
		*rel_cur_pos -= 1;
		if ((get_cursor_position(&pos, active_buf,
	*rel_cur_pos, start_pos)) == 1)
			return (1);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}

int		move_cursor_right(t_cur_abs_pos *start_pos,
t_dyn_buf *active_buf, size_t *rel_cur_pos)
{
	t_cur_abs_pos	pos;

	if (*rel_cur_pos < active_buf->len)
	{
		(*rel_cur_pos) += 1;
		if ((get_cursor_position(&pos, active_buf,
	*rel_cur_pos, start_pos)) == 1)
			return (1);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}
