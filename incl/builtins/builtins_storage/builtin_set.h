/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_set.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:49:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 06:09:10 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_SET_H
# define BUILTIN_SET_H

# include "common.h"
# include "storage/storage_print.h"

int		builtin_set(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context);

#endif
