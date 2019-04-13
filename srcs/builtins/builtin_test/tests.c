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

static int	handle_negate(t_test_infos *infos,
				const char **av, int ac, t_sh_state *sh_state)
{
	if (!infos->is_last_builtin)
		ac -= 1;
	sh_state->status = 2;
	if (((infos->base_ac == 3 || infos->base_ac == 4) &&
		!infos->is_last_builtin) ||
((infos->base_ac == 4 || infos->base_ac == 5) && infos->is_last_builtin))
	{
		return (test_error((char *)((av - (infos->base_ac - ac))[0]),
	    NULL, "too many arguments", &(sh_state->status)));
	}
	if (((infos->base_ac > 4 && ft_strcmp(av[1], "!") == 0) &&
			infos->is_last_builtin) ||
		((infos->base_ac > 3 && ft_strcmp(av[1], "!") == 0) &&
			!infos->is_last_builtin))
	{
		return (test_error((char *)((av - (infos->base_ac - ac))[0]),
            NULL, "argument expected", &(sh_state->status)));
	}
	sh_state->status = av[1][0] == '\0' ? 0 : 1;
	return (0);
}

static int	check_2args(t_test_infos *infos,
				const char **av, int ac, t_sh_state *sh_state)
{
	if (ft_strcmp("!", av[0]) == 0)
	{
		if (handle_negate(infos, av, ac, sh_state) == 1)
			return (1);
	}
	else if (is_unary_op(av[0]))
		sh_state->status = make_unary_test(av[0][1], av[1]);
	else
	{
		if ((infos->base_ac > 3 && !infos->is_last_builtin) ||
			(infos->base_ac > 4 && infos->is_last_builtin))
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
                            NULL, "too many arguments", &(sh_state->status)));
		else
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
                            (char *)av[0], "unary operator expected", &(sh_state->status)));
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
		if ((infos->is_last_builtin && infos->base_ac > 5) ||
			(!infos->is_last_builtin && infos->base_ac > 4))
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
            (char *)av[1], "too many arguments", &(sh_state->status)));
		else
			return (test_error((char *)((av - (infos->base_ac - ac))[0]),
	    (char *)av[1], "binary operator expected", &(sh_state->status)));
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
            (char *)av[1], "too many arguments", &(sh_state->status)));
}

int			make_test(t_test_infos *infos,
				const char **av, int ac, t_sh_state *sh_state)
{
	if (ac == 1)
	{
		if (av[0][0] != '\0')
			sh_state->status = 0;
	}
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
