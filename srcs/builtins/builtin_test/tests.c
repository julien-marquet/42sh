/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tests.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:04:11 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 18:04:12 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	handle_negate(t_test_infos *infos, char **av, int ac)
{
	if (infos->base_ac == 4 || infos->base_ac == 5)
	{
		return (test_error((char *)((av - (infos->base_ac - ac))[0]),
		NULL, "too many arguments"));
	}
	if ((infos->base_ac > 4 && ft_strcmp(av[1], "!") == 0))
	{
		return (test_error((char *)((av - (infos->base_ac - ac))[0]),
			NULL, "argument expected"));
	}
	return (!(av[1][0] == '\0'));
}

static int	check_2args(t_test_infos *infos, char **av, int ac)
{
	int		ret;

	if (ft_strcmp("!", av[0]) == 0)
	{
		if ((ret = handle_negate(infos, av, ac)) != 0)
			return (ret);
	}
	else if (is_unary_op(av[0]))
		return (make_unary_test(av[0][1], av[1]));
	else
	{
		if (infos->base_ac > 4)
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
							NULL, "too many arguments"));
		else
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
			(char *)av[0], "unary operator expected"));
	}
	return (0);
}

static int	check_3args(t_test_infos *infos, char **av, int ac)
{
	if (is_binary_op(av[1]))
		return (make_binary_test(av));
	else if (ft_strcmp("!", av[0]) == 0)
	{
		infos->negate = !infos->negate;
		return (make_test(infos, av + 1, ac - 1));
	}
	else if (ft_strcmp("(", av[0]) == 0 && ft_strcmp(")", av[2]) == 0)
		return (av[1][0] == '\0');
	else
	{
		if (infos->base_ac > 5)
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
			(char *)av[1], "too many arguments"));
		else
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
		(char *)av[1], "binary operator expected"));
	}
	return (0);
}

static char	**remove_negate(char **av)
{
	size_t	i;

	free(av[1]);
	i = 1;
	while (av[i])
	{
		av[i] = av[i + 1];
		i += 1;
	}
	return (av);
}

static int	check_more_args(t_test_infos *infos, char **av, int ac)
{
	if (ft_strcmp("!", av[0]) == 0 ||
		(ft_strcmp("(", av[0]) == 0 && ft_strcmp("!", av[1]) == 0))
	{
		infos->negate = !infos->negate;
		if (ft_strcmp("(", av[0]) == 0 && ft_strcmp("!", av[1]) == 0)
		{
			infos->base_ac -= 1;
			return (make_test(infos, remove_negate(av), ac - 1));
		}
		return (make_test(infos, av + 1, ac - 1));
	}
	else
		return (test_error((char *)((av - (infos->base_ac - ac))[0]),
			NULL, "too many arguments"));
}

int			make_test(t_test_infos *infos, char **av, int ac)
{
	int		ret;

	ret = 1;
	if (ac == 1)
	{
		if (av[0][0] != '\0')
			return (0);
	}
	else if (ac == 2)
	{
		if ((ret = check_2args(infos, av, ac)) == -1)
			return (-1);
	}
	else if (ac == 3)
	{
		if ((ret = check_3args(infos, av, ac)) == -1)
			return (-1);
	}
	else
	{
		if ((ret = check_more_args(infos, av, ac)) == -1)
			return (-1);
	}
	return (ret);
}
