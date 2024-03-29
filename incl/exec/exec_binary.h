/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_binary.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 22:43:28 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:30:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_BINARY_H
# define EXEC_BINARY_H

# include "common.h"
# include "jobs/jobs.h"
# include "exec/exec_utils.h"
# include "pipe_redir/pipe_redir.h"
# include "storage/storage_tmp.h"

int		exec_binary(t_cmd *cmd, char **env,
const char *path, t_context *context);

#endif
