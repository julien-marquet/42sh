/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 20:25:04 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 03:07:06 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include "common.h"
# include "storage/storage.h"
# include "builtins/builtins_utils.h"

int		builtin_cd(t_sh_state *sh_state, int ac,
		const char **av, t_builtin_context *context);

#endif
