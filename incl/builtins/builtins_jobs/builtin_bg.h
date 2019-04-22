/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_bg.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:22:44 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 01:23:59 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_BG_H
# define BUILTIN_BG_H

# include "common.h"
# include "jobs/jobs.h"
# include "builtins/builtins_utils.h"
# include "error_handler.h"

int			builtin_bg(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context);

#endif
