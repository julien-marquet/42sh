/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_dispatcher.h                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 19:00:22 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 13:56:47 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_DISPATCHER_H
# define BUILTINS_DISPATCHER_H

# include "common.h"
# include "builtins/builtins_defines.h"
# include "builtins/builtins_execution.h"
# include "builtins/builtins_storage/builtins_storage.h"
# include "builtins/builtins_aliases/builtins_aliases.h"
# include "builtins/builtin_exit.h"
# include "builtins/builtin_echo/builtin_echo.h"
# include "builtins/builtin_fc.h"
# include "builtins/builtins_jobs/builtins_jobs.h"
# include "builtins/builtin_hash/builtin_hash.h"
# include "builtins/builtin_test/builtin_test.h"
# include "builtins/builtin_cd/builtin_cd.h"
# include "builtins/builtin_type.h"
# include "builtins/builtin_true.h"
# include "builtins/builtin_false.h"

int		builtins_dispatcher(t_sh_state *sh_state,
		t_cmd *cmd, t_context *context);

#endif
