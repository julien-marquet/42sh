/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 22:52:45 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"
#include "signal.h"

static int	is_background(int i)
{
	return (i);
}

static t_exec_mode	get_exec_mode(t_exec_mode i)
{
	return (i);
}

t_context	*init_context(int background, t_exec_mode exec_mode)
{
	t_context	*context;

	if ((context = ft_memalloc(sizeof(t_context))) == NULL)
		return (NULL);
	context->background = background;
	context->exec_mode = exec_mode;
	return (context);
}

int		execute(t_sh_state *sh_state, char **parsed)
{
	t_context		*context;
	t_exec_func		exec_func;

	context = init_context(is_background(0), get_exec_mode(0));
	// DEBUG simulate background
	if (parsed && parsed[0])
		context->background = ft_strcmp(parsed[0], "1") == 0;
	if (context->background == 1)
		parsed = &(parsed[1]);
	if ((exec_func = get_exec_function(context->exec_mode)) == NULL)
		return (1);
	exec_func(sh_state, (const char **)parsed, context);
	return (0);
}
