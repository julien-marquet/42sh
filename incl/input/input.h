/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:51:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 23:30:23 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "common.h"
# include "utils/dyn_buf.h"

int				handle_input(t_sh_state *sh_state, t_input_data *input_data);
t_dyn_buf		*init_dyn_buf(void);

#endif
