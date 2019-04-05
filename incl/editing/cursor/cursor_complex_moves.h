/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_complex_moves.h                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:00:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:12:16 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_COMPLEX_MOVES_H
# define CURSOR_COMPLEX_MOVES_H

# include "common.h"
# include "editing/cursor/cursor.h"

int		move_to_next_word(t_input_data *input_data);
int		move_to_prev_word(t_input_data *input_data);
int		goto_home(t_input_data *input_data);
int		goto_end(t_input_data *input_data);

#endif
