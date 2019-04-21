/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_dispatcher.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:30:27 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 23:14:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_DISPATCHER_H
# define EXEC_DISPATCHER_H

# include "common.h"
# include "builtins/builtin_hash/builtin_hash.h"
# include "storage/storage.h"
# include "exec/exec_binary.h"

int		exec_dispatcher(t_sh_state *sh_state, t_cmd *cmd,
		t_context *context);

#endif
