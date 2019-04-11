/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tests.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:51:20 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 21:51:21 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"

static void	check_1arg(const char **av, t_sh_state *sh_state)
{
	if (av[0][0] != '\0')
		sh_state->status = 0;
}

static int	check_2args(t_test_infos *infos,
				const char **av, int ac, t_sh_state *sh_state)
{
	if (ft_strcmp("!", av[0]) == 0)
	{
		sh_state->status = 2;
		if ((infos->base_ac == 3 || infos->base_ac == 4) ||
			(infos->base_ac > 3 && ft_strcmp(av[1], "!") == 0))
		{
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
					NULL, (infos->base_ac == 3 || infos->base_ac == 4) ?
					"too many arguments" : "argument expected"));
		}
		sh_state->status = av[1][0] == '\0' ? 0 : 1;
	}
	else if (is_unary_op(av[0]))
		sh_state->status = make_unary_test(av[0][1], av[1]);
	else
	{
		if (infos->base_ac > 3)
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
					NULL, "too many arguments"));
		else
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
					(char *)av[0], "unary operator expected"));
	}
	return (0);
}

static int	check_3args(t_test_infos *infos,
				const char **av, int ac, t_sh_state *sh_state)
{
	if (is_binary_op(av[1]))
		sh_state->status = make_binary_test(av[0], av[1], av[2]);
	else if (ft_strcmp("!", av[0]) == 0)
	{
		infos->negate = !infos->negate;
		return (make_test(infos, av + 1, ac - 1, sh_state));
	}
	else if (ft_strcmp("(", av[0]) == 0 && ft_strcmp(")", av[2]) == 0)
		sh_state->status = av[1][0] != '\0' ? 0 : 1;
	else
	{
		if ((ft_strcmp(av[ac - 1], "]") == 0 && infos->base_ac > 5) ||
			(ft_strcmp(av[ac - 1], "]") != 0 && infos->base_ac > 4))
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
				(char *)av[1], "too many arguments"));
		else
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
				(char *)av[1], "binary operator expected"));
	}
	return (0);
}

static int	check_more_args(t_test_infos *infos,
				const char **av, int ac, t_sh_state *sh_state)
{
	if (ft_strcmp("!", av[0]) == 0)
	{
		infos->negate = !infos->negate;
		return (make_test(infos, av + 1, ac - 1, sh_state));
	}
	else
		return (test_error((char *)((av - (infos->base_ac - ac))[0]),
			(char *)av[1], "too many arguments"));
}

int			make_test(t_test_infos *infos,
				const char **av, int ac, t_sh_state *sh_state)
{
	if (ac == 1)
		check_1arg(av, sh_state);
	else if (ac == 2)
	{
		if (check_2args(infos, av, ac, sh_state) == 1)
			return (1);
	}
	else if (ac == 3)
	{
		if (check_3args(infos, av, ac, sh_state) == 1)
			return (1);
	}
	else
	{
		if (check_more_args(infos, av, ac, sh_state) == 1)
			return (1);
	}
	if (sh_state->status > 1)
		return (1);
	if (infos->negate)
		sh_state->status = !sh_state->status;
	return (0);
}
