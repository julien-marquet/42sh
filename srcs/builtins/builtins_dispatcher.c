/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_dispatcher.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 19:00:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 21:24:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_dispatcher.h"

static t_builtin_func	get_builtins_func(const char *name)
{
	static char	*assoc_name[BUILTINS_NB + 1] = {
		"set", "env", "setenv", "unsetenv", "unset", "exit", "echo", "export",
		"alias", "unalias", "jobs", "fg", NULL
	};
	static int	(*assoc_func[BUILTINS_NB + 1])(t_sh_state *, int, const char **, t_builtin_context *) = {
		builtin_set, builtin_env, builtin_setenv, builtin_unsetenv,
		builtin_unset, builtin_exit, builtin_echo, builtin_export,
		builtin_alias, builtin_unalias, builtin_jobs, builtin_fg, NULL
	};
	size_t		i;

	i = 0;
	if (name != NULL)
	{
		while (assoc_name[i] != NULL)
		{
			if (ft_strcmp(assoc_name[i], name) == 0)
				return (assoc_func[i]);
			i++;
		}
	}
	return (NULL);
}

t_builtin_context	*init_builtin_context()
{
	t_builtin_context *builtin_context;

	if ((builtin_context = ft_memalloc(sizeof(t_builtin_context))) == NULL)
		return (NULL);
	if (add_origin(&builtin_context->origin, "42sh") == 1)
		return (NULL);
	builtin_context->fds.err = 2;
	builtin_context->fds.out = 1;
	builtin_context->fds.in = 0;
	return (builtin_context);
}

int			builtins_dispatcher(t_sh_state *sh_state,
const char **av, t_context *context)
{
	t_builtin_func	f;
	int				res;

	res = 0;
	if ((f = get_builtins_func(av[0])) != NULL)
	{
		if ((context->builtin_context = init_builtin_context()) == NULL)
			return (-1);
		if (context->background == 0)
		{
			sh_state->status = exec_builtin(sh_state, av, f, context);
			res = 1;
		}
		else
		{
			if (background_exec_builtin(sh_state, av, f, context) == 1)
				res = -1;
			else
				res = 1;
		}
		free(context->builtin_context);
		context->builtin_context = NULL;
	}
	return (res);
}
