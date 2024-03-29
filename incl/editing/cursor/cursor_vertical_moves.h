/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_vertical_moves.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:44:40 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:13:13 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CURSOR_VERTICAL_MOVES_H
# define CURSOR_VERTICAL_MOVES_H

# include "common.h"
# include "editing/cursor/cursor.h"

int		move_up(t_input_data *input_data);
int		move_down(t_input_data *input_data);

#endif
