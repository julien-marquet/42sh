/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_position.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 19:10:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 20:22:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_POSITION_H
# define CURSOR_POSITION_H

#include "common.h"
#include "input/cursor.h"
#include "input/prompt.h"
#include "input/input_control.h"
#include "win_data.h"

int		get_cursor_position(t_cur_abs_pos *pos, t_dyn_buf *active_buf,
size_t rel_cur_pos, t_cur_abs_pos *start_pos);
int		update_start_position(t_dyn_buf *active_buf,
t_cur_abs_pos *start_pos);
int		ask_start_position(t_cur_abs_pos *pos);

#endif