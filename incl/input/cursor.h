/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:40:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 22:35:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_H
# define CURSOR_H

# include "common.h"
# include "input/input_data.h"

int		get_cursor_position(t_cur_abs_pos *pos);
int		move_cursor_left(t_input_data *input_data);
int		move_cursor_right(t_input_data *input_data);
int		get_line_length(size_t pos, char *buf);

#endif
