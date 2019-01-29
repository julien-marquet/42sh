/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:51:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 22:53:07 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "common.h"
# include "input_buf.h"

int				handle_input(t_sh_state *sh_state, t_input_buf *input_buf);
t_input_buf		*init_input_buf(void);

#endif
