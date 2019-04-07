/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_dispatcher.h                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 19:00:22 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 19:33:54 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_DISPATCHER_H
# define BUILTINS_DISPATCHER_H

# include "common.h"
# include "builtins/builtins_defines.h"
# include "builtins/builtins_execution.h"
# include "builtins/builtins_storage/builtins_storage.h"

int			builtins_dispatcher(t_sh_state *sh_state, char *name, int	fd_out);

#endif
