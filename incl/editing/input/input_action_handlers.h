/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_action_handlers.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:16:45 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 23:28:02 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_ACTION_HANDLERS_H
# define INPUT_ACTION_HANDLERS_H

# include "common.h"
# include "editing/input/input.h"
# include "editing/history/history_edition.h"

int		handle_enter(t_input_data *input_data);
int		handle_user_reset(t_input_data *input_data, t_sh_state *sh_state);
int		clear_input(t_input_data *input_data);

#endif
