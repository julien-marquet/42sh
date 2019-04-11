/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 02:01:32 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"

static int	is_background(int i)
{
	return (i);
}

t_context	*init_context(int background)
{
	t_context	*context;

	if ((context = ft_memalloc(sizeof(t_context))) == NULL)
		return (NULL);
	context->background = background;
	return (context);
}

int		execute(t_sh_state *sh_state, const char **parsed)
{
	int	i;
	int	found;
	t_context	*context;

	i = 0;
	context = init_context(is_background(1));
	// placeholder for loop in cmd
	while (i < 2)
	{
		if ((found = builtins_dispatcher(sh_state, parsed, context)) == -1)
			return (1);
		else if (found == 0)
		{
			found = exec_dispatcher(context);
		}
		if (found == 1)
			dprintf(2, "EXEC_DONE\n");
		i++;
	}
	dprintf(2, "list = \n");
	list_jobs();
	return (0);
}
