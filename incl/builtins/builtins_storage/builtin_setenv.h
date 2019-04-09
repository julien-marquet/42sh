/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_setenv.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:40:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:51:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_SETENV_H
# define BUILTIN_SETENV_H

# include "common.h"
# include "storage/storage.h"
# include "builtins/builtins_storage/builtin_env.h"

int		builtin_setenv(t_sh_state *sh_state, int ac, const char **av, const t_fds fds);

#endif
