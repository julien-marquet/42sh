/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_capabilities_dispatchers.h                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:48:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 23:38:28 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_CAPABILITIES_DISPATCHER_H
# define INPUT_CAPABILITIES_DISPATCHER_H

# include "common.h"
# include "editing/input/input.h"
# include "editing/input/input_selection.h"

int		capabilities_dispatcher_1(t_input_data *input_data,
		t_sh_state *sh_state);
int		capabilities_dispatcher_2(t_input_data *input_data);
int		capabilities_dispatcher_3(t_input_data *input_data);
int		capabilities_dispatcher_4(t_input_data *input_data, t_list *hist_copy);
int		capabilities_dispatcher_selection(t_input_data *input_data);

#endif
