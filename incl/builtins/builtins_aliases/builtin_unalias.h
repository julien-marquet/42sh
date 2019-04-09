/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unalias.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:11:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 18:43:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_UNALIAS_H
# define BUILTIN_UNALIAS_H

# include "common.h"
# include "aliases/aliases.h"
# include "error_handler.h"
# include "builtins/builtins_utils.h"

int		builtin_unalias(t_sh_state *sh_state, int ac, const char **av,
		t_builtin_context *context);

#endif
