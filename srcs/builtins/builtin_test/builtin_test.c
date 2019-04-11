/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_test.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 18:05:10 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 18:05:11 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	error(char *builtin, char *file, char *msg)
{
	if (file != NULL)
		dprintf(2, "-%s: %s: %s: %s\n", NAME, builtin, file, msg);
	else
		dprintf(2, "-%s: %s: %s\n", NAME, builtin, msg);
	return (1);
}

static int	is_unary_op(const char *arg)
{
	return (ft_strlen(arg) == 2 &&
		arg[0] == '-' &&
		ft_strchr("bcdefgLprSsuwxz", arg[1]) != NULL);
}

static int	is_binary_op(const char *arg)
{
        dprintf(1, "Arg is: |%s|\n", arg);
	return (ft_strcmp("-eq", arg) == 0 ||
		ft_strcmp("-ne", arg) == 0 ||
		ft_strcmp("-ge", arg) == 0 ||
		ft_strcmp("-lt", arg) == 0 ||
		ft_strcmp("-le", arg) == 0 ||
		ft_strcmp("=", arg) == 0 ||
		ft_strcmp("!=", arg) == 0);
}

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

int	check_args(const char *arg1, const char *arg2)
{
	if (check_arg(arg1) == 1)
	{
		return (error("test", (char *)arg1,
				"integer expression expected"));
	}
	if (check_arg(arg2) == 1)
	{
		return (error("test", (char *)arg2,
				"integer expression expected"));
	}
	return (0);
}

static int          make_test(t_test_infos infos, const char **av, int ac, t_sh_state *sh_state)
{
	if (ac == 1)
	{
		if (av[0][0] != '\0')
			sh_state->status = 0;
	}
        else if (ac == 2)
        {
                if (ft_strcmp("!", av[0]) == 0)
                {
                        sh_state->status = 2;
                        if (infos.base_ac == 3 || infos.base_ac == 4)
                            return (error((char *)((av - (infos.base_ac - ac))[0]), NULL, "too many arguments"));
                        if (infos.base_ac > 3 && ft_strcmp(av[1], "!") == 0)
                            return (error((char *)((av - (infos.base_ac - ac))[0]), NULL, "argument expected"));
                        sh_state->status = av[1][0] == '\0' ? 0 : 1;
                }
                else if (is_unary_op(av[0]))
                        sh_state->status = make_unary_test(av[0][1], av[1]);
                else
                        return (error((char *)((av - (infos.base_ac - ac))[0]), (char *)av[0],
				"unary operator expected"));
        }
	else if (ac == 3)
	{
                if (is_binary_op(av[1]))
                        sh_state->status = make_binary_test(av[0], av[1], av[2]);
                else if (ft_strcmp("!", av[0]) == 0)
                {
                        infos.negate = !infos.negate;
                        return (make_test(infos, av + 1, ac - 1, sh_state));
                }
                else if (ft_strcmp("(", av[0]) == 0 && ft_strcmp(")", av[2]) == 0)
                        sh_state->status = av[1][0] != '\0' ? 0 : 1;
                else
                        return (error((char *)((av - (infos.base_ac - ac))[0]), (char *)av[1],
				(ft_strcmp(av[ac - 1], "]") == 0  && infos.base_ac > 5) || (ft_strcmp(av[ac - 1], "]") != 0  && infos.base_ac > 4) ? "too many arguments" : "binary operator expected"));
	}
        else
        {
                if (ft_strcmp("!", av[0]) == 0)
                {
                        infos.negate = !infos.negate;
                        return (make_test(infos, av + 1, ac - 1, sh_state));
                }
                else
                        return (error((char *)((av - (infos.base_ac - ac))[0]), (char *)av[1],
				"too many arguments"));
        }
	if (sh_state->status > 1)
		return (1);
	if (infos.negate)
		sh_state->status = !sh_state->status;
	return (0);
}

int			builtin_test(t_sh_state *sh_state, int ac,
					const char **av, t_builtin_context *context)
{
        t_test_infos    infos;

        infos.negate = 0;
        infos.base_ac = ac - 1;
	sh_state->status = 1;
	if (ft_strcmp("[", av[0]) == 0)
	{
		if (ft_strcmp("]", av[ac - 1]) != 0)
			return (error((char *)av[0], NULL, "missing `]`"));
		ac -= 1;
	}
	if (ac == 1)
		return (0);
        return (make_test(infos, av + 1, ac - 1, sh_state));
}
