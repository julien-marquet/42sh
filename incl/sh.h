/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 23:05:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 22:57:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "common.h"

t_sh_state	*init_sh(void);
void		exit_sh(t_sh_state *sh_state);
#endif
