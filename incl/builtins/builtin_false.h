/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_false.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 09:58:28 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 09:59:07 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_FALSE_H
# define BUILTIN_FALSE_H

# include "common.h"

int		builtin_false(t_sh_state *sh_state, int ac,
		const char **av, t_builtin_context *context);

#endif
