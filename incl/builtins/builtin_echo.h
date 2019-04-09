/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:00:21 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:51:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_ECHO_H
# define BUILTIN_ECHO_H

# include "common.h"

int			builtin_echo(t_sh_state *sh_state, int ac,
const char **av, const t_fds fds);

#endif
