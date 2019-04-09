/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:37:02 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 20:36:22 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_EXPORT_H
# define BUILTIN_EXPORT_H

# include "common.h"
# include "storage/storage.h"
# include "builtins/builtins_utils.h"
# include "error_handler.h"

int		builtin_export(t_sh_state *sh_state, int ac, const char **av,
		t_builtin_context *context);

#endif