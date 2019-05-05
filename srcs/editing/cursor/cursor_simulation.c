/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_simulation.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 19:05:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:51:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/cursor/cursor_simulation.h"

static void	sim_wrap(t_cur_abs_pos *pos)
{
	pos->row += 1;
	pos->col = 1;
}

static void	sim_break(t_cur_abs_pos *pos)
{
	pos->row += 1;
	pos->col = 0;
}

static int	update_wanted_pos(t_cur_abs_pos *pos,
t_dyn_buf *active_buf, size_t i, size_t rel_cur_pos)
{
	int				win_col;

	if ((win_col = get_win_col()) == -1)
		return (1);
	if (pos->col >= win_col)
		sim_wrap(pos);
	else if (active_buf->buf[i] == '\n')
		sim_break(pos);
	else
	{
		if (i < rel_cur_pos)
			pos->col++;
	}
	return (0);
}

/*
**	Simulate cursor movement updating pos to wanted pos
**	And last pos to position of last char
*/

int			sim_cursor_movements(t_cur_abs_pos *pos, t_cur_abs_pos *last_pos,
t_dyn_buf *active_buf, size_t rel_cur_pos)
{
	int				win_col;
	size_t			i;

	i = 0;
	if ((win_col = get_win_col()) == -1)
		return (1);
	while (i < active_buf->len)
	{
		if (last_pos->col >= win_col)
			sim_wrap(last_pos);
		else if (active_buf->buf[i] == '\n')
			sim_break(last_pos);
		else
			last_pos->col++;
		if (i < rel_cur_pos)
		{
			if (update_wanted_pos(pos, active_buf, i, rel_cur_pos) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int			sim_cursor_movement_light(t_dyn_buf *active_buf,
size_t rel_cur_pos, t_cur_abs_pos *pos, int win_col)
{
	size_t	i;

	i = 0;
	while (i < active_buf->len && i < rel_cur_pos)
	{
		if (pos->col >= win_col)
			sim_wrap(pos);
		else if (active_buf->buf[i] == '\n')
			sim_break(pos);
		else
		{
			if (i < rel_cur_pos)
				pos->col++;
		}
		i++;
	}
	return (i);
}
