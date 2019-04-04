/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_utils.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:59:45 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 18:48:51 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_UTILS_H
# define CURSOR_UTILS_H

#include "common.h"
#include "input/cursor.h"

int			get_next_move_num(t_input_data *input_data);
int			get_prev_move_num(t_input_data *input_data);
int			get_prev_position(t_input_data *input_data, t_cur_abs_pos *pos_prev, size_t i);
int			get_next_position(t_input_data *input_data, t_cur_abs_pos *pos_next, size_t i);

#endif
