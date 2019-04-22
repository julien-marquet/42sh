/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipes.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 00:04:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 01:46:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "common.h"
# include "pipe_redir/pipe_defines.h"

int		use_pipes(t_context *context, int new_pipe[3]);

#endif
