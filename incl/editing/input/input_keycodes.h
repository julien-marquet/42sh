/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_keycodes.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:18:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 23:07:42 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_KEYCODES_H
# define INPUT_KEYCODES_H

# define KEY_ARROW_UP "\033[A"
# define KEY_ARROW_DOWN "\033[B"
# define KEY_ARROW_RIGHT "\033[C"
# define KEY_ARROW_LEFT "\033[D"
# define ALT_ARROW_RIGHT "\033\033[C"
# define ALT_ARROW_LEFT "\033\033[D"
# define ALT_ARROW_UP "\033\033[A"
# define ALT_ARROW_DOWN "\033\033[B"
# define KEY_SHIFT_LEFT "\033[1;2D"
# define KEY_SHIFT_RIGHT "\033[1;2C"
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

#endif
