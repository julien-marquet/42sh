/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipes.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 00:04:33 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 02:43:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "pipe_redir/pipes.h"

int		use_pipes(t_context *context, int new_pipe[3])
{
	if (context->last_pipe_read != -1)
	{
		dprintf(2, "child dup2(%d, 0)\n", context->last_pipe_read);
		dup2(context->last_pipe_read, 0);
		close(context->last_pipe_read);
	}
	if (new_pipe[0] == 1)
	{
		dprintf(2, "child dup2(%d, 1)\n", new_pipe[2]);
		dup2(new_pipe[WRITE_END], 1);
		close(new_pipe[READ_END]);
		close(new_pipe[WRITE_END]);
	}

	return (0);
}
