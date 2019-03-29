/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:40:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 22:18:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_H
# define CURSOR_H

# define SCROLL_RESET -1

# include "common.h"
# include "input/input_data.h"

int		get_cursor_position(t_cur_abs_pos *pos, t_dyn_buf *active_buf,
size_t rel_cur_pos, t_cur_abs_pos *start_pos);
int		update_start_position(t_dyn_buf *active_buf,
t_cur_abs_pos *start_pos);
int		ask_start_position(t_cur_abs_pos *pos);
int		move_cursor_left(t_input_data *input_data);
int		move_cursor_right(t_input_data *input_data);
int		get_line_length(t_dyn_buf *active_buf, size_t start);
int		move_to_next_word(t_input_data *input_data);
int		move_to_prev_word(t_input_data *input_data);
int		move_up(t_input_data *input_data);
int		move_down(t_input_data *input_data);
int		goto_home(t_input_data *input_data);
int		goto_end(t_input_data *input_data);

#endif
