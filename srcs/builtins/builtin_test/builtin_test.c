/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_test.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:03:31 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 18:03:33 by legrivel    ###    #+. /#+    ###.fr     */
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

int			test_error(char *builtin, char *file,
					char *msg, unsigned char *status)
{
	if (status != NULL)
		*status = 2;
	if (file != NULL)
		dprintf(2, "-%s: %s: %s: %s\n", NAME, builtin, file, msg);
	else
		dprintf(2, "-%s: %s: %s\n", NAME, builtin, msg);
	return (1);
}

int			check_args(const char *arg1, const char *arg2)
{
	if (check_arg(arg1) == 1)
	{
		return (test_error("test", (char *)arg1,
				"integer expression expected", NULL));
	}
	if (check_arg(arg2) == 1)
	{
		return (test_error("test", (char *)arg2,
				"integer expression expected", NULL));
	}
	return (0);
}

int			builtin_test(t_sh_state *sh_state, int ac,
					const char **av, t_builtin_context *context)
{
	t_test_infos	infos;

	infos.negate = 0;
	infos.base_ac = ac - 1;
	infos.is_last_builtin = ft_strcmp(av[ac - 1], "]") == 0 ? 1 : 0;
	sh_state->status = 1;
	if (ft_strcmp("[", av[0]) == 0)
	{
		if (ft_strcmp("]", av[ac - 1]) != 0)
			return (test_error((char *)av[0], NULL, "missing `]`", NULL));
		ac -= 1;
	}
	if (ac == 1)
		return (0);
	if (make_test(&infos, av + 1, ac - 1, sh_state) == 1)
		return (1);
	if (infos.negate)
		sh_state->status = !sh_state->status;
	return (0);
}
