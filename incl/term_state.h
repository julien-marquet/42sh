/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_state.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 23:05:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 15:35:46 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TERM_STATE_H
# define TERM_STATE_H

# include "common.h"

int			init_term_state(t_sh_state *sh_state, char **env);
int			set_term_state_backup(t_sh_state *sh_state);
int			set_term_state(t_sh_state *sh_state);

#endif
