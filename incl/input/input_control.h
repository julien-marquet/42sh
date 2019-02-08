/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_control.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:43:40 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 18:16:29 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_CONTROL_H
# define INPUT_CONTROL_H

# include "common.h"
# include "input/input_data.h"

int		clear_line(void);
int		delete_prev_char(t_input_data *input_data);
void	delete_cur_char(t_input_data *input_data);
int		update_vbuf(char *buf, size_t rel_cur_pos);
int		insertn_chars(t_input_data *input_data, size_t n);

#endif
