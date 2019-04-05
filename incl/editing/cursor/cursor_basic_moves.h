/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_basic_moves.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:02:03 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:12:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_BASIC_MOVES_H
# define CURSOR_BASIC_MOVES_H

# include "common.h"
# include "editing/cursor/cursor.h"

int		move_cursor_left(t_input_data *input_data);
int		move_cursor_right(t_input_data *input_data);

#endif
