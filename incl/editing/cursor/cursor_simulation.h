/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_simulation.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 19:07:03 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:55:13 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#ifndef CURSOR_SIMULATION_H
# define CURSOR_SIMULATION_H

# include "common.h"
# include "editing/cursor/cursor.h"
# include "data/dyn_buf/dyn_buf.h"

int		sim_cursor_movements(t_cur_abs_pos *pos, t_cur_abs_pos *last_pos, t_dyn_buf *active_buf, size_t rel_cur_pos);
int		sim_cursor_movement_light(t_dyn_buf *active_buf, size_t rel_cur_pos, t_cur_abs_pos *pos, int win_col);

#endif
