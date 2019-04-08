/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_dispatcher.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 19:00:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 02:08:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_dispatcher.h"

static t_builtin_func	get_builtins_func(const char *name)
{
	static char	*assoc_name[BUILTINS_NB + 1] = {
		"set", "env", "setenv", "unsetenv", "unset", "exit", "echo", "export", NULL
	};
	static int	(*assoc_func[BUILTINS_NB + 1])(t_sh_state *, int, const char **, int) = {
		builtin_set, builtin_env, builtin_setenv, builtin_unsetenv,
		builtin_unset, builtin_exit, builtin_echo, builtin_export, NULL
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

int			builtins_dispatcher(t_sh_state *sh_state,
const char **av, int fd_out, int background)
{
	t_builtin_func	f;

	if ((f = get_builtins_func(av[0])) != NULL)
	{
		if (background == 0)
			return (exec_builtin(sh_state, av, f, fd_out));
		else
			return (background_exec_builtin(sh_state, av, f, fd_out));
	}
	else
		return (0);
}