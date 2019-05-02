/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_test.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:03:31 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 03:41:52 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	check_arg(const char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < 48 || arg[i] > 57)
			return (1);
		i += 1;
	}
	return (0);
}

// @TODO remove dprintf2
int			test_error(char *builtin, char *file, char *msg)
{
	if (file != NULL)
		dprintf(2, "-%s: %s: %s: %s\n", NAME, builtin, file, msg);
	else
		dprintf(2, "-%s: %s: %s\n", NAME, builtin, msg);
	return (2);
}

int			check_args(char **av)
{
	if (check_arg(av[0]) == 1)
	{
		return (test_error(((char *)(*(av - 1))), (char *)(av[0]),
				"integer expression expected"));
	}
	if (check_arg(av[2]) == 1)
	{
		return (test_error(((char *)(*(av - 1))), (char *)(av[2]),
				"integer expression expected"));
	}
	return (0);
}

char		**arrdup(const char **av, int ac)
{
	size_t	i;
	char	**args;

	if ((args = malloc(sizeof(char *) * (ac + 1))) == NULL)
		return (NULL);
	i = 0;
	while (ac > 0)
	{
		if ((*(args + i) = ft_strdup(*(av + i))) == NULL)
			return (NULL);
		i += 1;
		ac -= 1;
	}
	*(args + i) = NULL;
	return (args);
}

int			builtin_test(t_sh_state *sh_state, int ac,
					const char **av, t_builtin_context *context)
{
	int				ret;
	t_test_infos	infos;
	char			**args;

	infos.negate = 0;
	if ((args = arrdup(av, ac)) == NULL)
		return (-1);
	infos.base_ac = ft_strcmp(av[0], "[") == 0 ? ac - 1 : ac;
	if (ft_strcmp("[", av[0]) == 0)
	{
		if (ft_strcmp("]", av[ac - 1]) != 0)
			return (test_error((char *)av[0], NULL, "missing `]`"));
		ac -= 1;
	}
	if (ac == 1)
		return (1);
	if ((ret = make_test(&infos, args + 1, ac - 1)) == -1)
		return (-1);
	if (ret == 2)
		return (ret);
	if (infos.negate)
		ret = !ret;
	ft_freetab(&args);
	return (ret);
}
