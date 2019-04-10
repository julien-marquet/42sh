/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:00:21 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 02:53:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_ECHO_H
# define BUILTIN_ECHO_H

# include "common.h"
# include "builtins/builtins_utils.h"
# include "builtins/builtin_echo/builtin_echo_utils.h"

int			builtin_echo(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context);

#endif
