/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_basic_moves.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:02:03 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 00:05:36 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_BASIC_MOVES_H
# define CURSOR_BASIC_MOVES_H

# include "common.h"
# include "editing/cursor/cursor.h"

int		move_cursor_left(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf,
		size_t *rel_cur_pos);
int		move_cursor_right(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf,
		size_t *rel_cur_pos);

#endif
