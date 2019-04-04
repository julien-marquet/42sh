/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_action_handlers.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:16:45 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 20:10:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_ACTION_HANDLERS_H
# define INPUT_ACTION_HANDLERS_H

# include "common.h"
# include "input/input.h"
# include "input/history_edition.h"

int		handle_enter(t_input_data *input_data);
int		handle_user_reset(t_input_data *input_data);
int		clear_input(t_input_data *input_data);

#endif