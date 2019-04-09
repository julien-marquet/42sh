/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_alias.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:12:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 17:59:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_ALIAS_H
# define BUILTIN_ALIAS_H

# include "common.h"
# include "aliases/aliases.h"
# include "builtins/builtins_utils.h"

int		builtin_alias(t_sh_state *sh_state, int ac, const char **av,
		t_builtin_context *context);

#endif
