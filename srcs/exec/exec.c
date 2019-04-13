/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 21:31:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"
#include "signal.h"

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

int		execute(t_sh_state *sh_state, char **parsed)
{
	int	i;
	int	found;
	t_context	*context;

	i = 0;
	context = init_context(is_background(0));
	// DEBUG simulate background
	if (parsed && parsed[0])
		context->background = ft_strcmp(parsed[0], "1") == 0;
	if (context->background == 1)
		parsed = &(parsed[1]);
	// placeholder for loop in cmd
	while (parsed[i] != NULL)
	{
		if ((found = builtins_dispatcher(sh_state, (const char **)&(parsed[i]), context)) == -1)
			return (1);
		else if (found == 0)
			found = exec_dispatcher(context);
		if (found == 1)
			dprintf(2, "EXEC_DONE\n");
		i++;
	}
	return (0);
}
