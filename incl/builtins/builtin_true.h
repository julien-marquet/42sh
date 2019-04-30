/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_true.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 09:57:17 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 09:58:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_TRUE_H
# define BUILTIN_TRUE_H

# include "common.h"

int		builtin_true(t_sh_state *sh_state, int ac,
		const char **av, t_builtin_context *context);

#endif
