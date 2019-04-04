/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_handlers.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:52:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_HANDLERS_H
# define INPUT_HANDLERS_H

# include "common.h"
# include "editing/input/input.h"

int		handle_capabilities(t_input_data *input_data, t_list *hist_copy);
int		handle_sig(t_input_data *input_data, t_sh_state *sh_state);
int		handle_insertion(t_input_data *input_data);

#endif
