/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_sig_handlers.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 18:34:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:45:21 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_SIG_HANDLERS_H
# define INPUT_SIG_HANDLERS_H

# include "common.h"
# include "input.h"

int		ctrl_c_handler(t_input_data *input_data);
int		ctrl_d_handler(t_sh_state *sh_state, t_input_data *input_data);
int		ctrl_r_handler(t_sh_state *sh_state, t_input_data *input_data);

#endif
