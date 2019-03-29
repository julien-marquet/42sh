/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:51:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 22:19:00 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define READ_SIZE 1024
# define KEY_ARROW_UP "\033[A"
# define KEY_ARROW_DOWN "\033[B"
# define KEY_ARROW_RIGHT "\033[C"
# define KEY_ARROW_LEFT "\033[D"
# define ALT_ARROW_RIGHT "\033\033[C"
# define ALT_ARROW_LEFT "\033\033[D"
# define ALT_ARROW_UP "\033\033[A"
# define ALT_ARROW_DOWN "\033\033[B"
# define KEY_GOHOME "\033[H"
# define KEY_GOEND "\033[F"
# define KEY_SIGINT "\03"
# define KEY_BS "\010"
# define KEY_BS2 "\177"
# define KEY_TAB "\t"
# define KEY_DEL "\033[3~"
# define CTRL_C "\03"
# define CTRL_D "\04"
# define CTRL_Z "\032"
# define KEY_NL "\012"
# define KEY_NP "\014"


# include "common.h"
# include "utils/dyn_buf.h"
# include "input/input_data.h"

int				handle_input(t_sh_state *sh_state, t_input_data *input_data, char *here_doc);
t_dyn_buf		*init_dyn_buf(void);

#endif
