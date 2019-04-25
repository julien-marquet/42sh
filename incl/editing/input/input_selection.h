/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_selection.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 23:12:32 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 00:05:54 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_SELECTION_H
# define INPUT_SELECTION_H

# include "common.h"
# include "editing/input/input.h"


int		expand_selection_right(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf, size_t *rel_cur_pos);
int		expand_selection_left(t_cur_abs_pos *start_pos, t_dyn_buf *active_buf, size_t *rel_cur_pos);
void	reset_selection(t_dyn_buf *active_buf);
int		get_first_selected_char(t_dyn_buf *active_buf);

#endif
