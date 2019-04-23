/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirs.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 23:22:40 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 01:44:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef REDIRS_H
# define REDIRS_H

# include "pipe_redir/pipe_defines.h"
# include "common.h"
# include <fcntl.h>
# include "error_handler.h"

int		handle_redir(t_cmd *cmd, char *origin);

#endif