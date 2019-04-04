/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_control.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:43:40 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_CONTROL_H
# define INPUT_CONTROL_H

# include "common.h"
# include "editing/input/input.h"
# include "editing/cursor/cursor.h"
# include "data/dyn_buf.h"
# include "editing/prompt.h"
# include "sh.h"

int		delete_prev_char(t_input_data *input_data);
int		delete_cur_char(t_input_data *input_data);
int		print_anew(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf, size_t rel_cur_pos);
int		insertn_chars(t_input_data *input_data, const char *str, size_t n, int force);

#endif
