/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:51:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 00:16:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define READ_SIZE 10
# define KEY_ARROW_UP "\033[A"
# define KEY_ARROW_DOWN "\033[B"
# define KEY_ARROW_RIGHT "\033[C"
# define KEY_ARROW_LEFT "\033[D"
# define KEY_SIGINT "\03"
# define KEY_BS "\010"
# define KEY_DEL "\177"

# include "common.h"
# include "utils/dyn_buf.h"

int				handle_input(t_sh_state *sh_state, t_input_data *input_data);
t_dyn_buf		*init_dyn_buf(void);

#endif
