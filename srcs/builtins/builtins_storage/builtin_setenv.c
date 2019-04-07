/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_setenv.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:39:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 21:14:39 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_setenv.h"

static int	params_is_valid(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int			builtin_setenv(t_sh_state *sh_state, int ac,
const char **av, int fd_out)
{
	if (ac == 1)
		return (builtin_env(sh_state, ac, av, fd_out));
	else if (ac > 3)
		write(fd_out, "setenv:, Too many arguments.\n", 30);
	else if (!params_is_valid(av[1]))
		write(fd_out,
	"setenv: Variable name must contain alphanumeric characters.\n", 61);
	else
		return (add_entry_storage(&sh_state->env, av[1], av[2]));
	return (1);
}
