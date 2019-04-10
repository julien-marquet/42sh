/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unset.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:24:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 17:59:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_UNSET_H
# define BUILTIN_UNSET_H

# include "common.h"
# include "storage/storage.h"

int		builtin_unset(t_sh_state *sh_state, int ac, const char **av,
		t_builtin_context *context);

#endif
