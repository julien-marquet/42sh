/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unsetenv.h                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 21:00:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:51:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_UNSETENV_H
# define BUILTIN_UNSETENV_H

# include "common.h"
# include "storage/storage.h"


int		builtin_unsetenv(t_sh_state *sh_state, int ac,
		const char **av, const t_fds fds);

#endif
