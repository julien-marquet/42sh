/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_state.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 23:05:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 23:38:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TERM_STATE_H
# define TERM_STATE_H

# include "common.h"

int			init_term_state(t_sh_state *sh_state);
int			reset_term_state(t_sh_state *sh_state);

#endif
