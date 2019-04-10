/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_set.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:49:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 17:59:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_SET_H
# define BUILTIN_SET_H

# include "common.h"
# include "storage/storage_manipulations.h"

int		builtin_set(t_sh_state *sh_state, int ac, const char **av, t_builtin_context *context);

#endif
