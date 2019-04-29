/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_exit.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:38:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 10:15:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_exit.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		builtin_exit(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	add_origin(&context->origin, "exit");
	if (ac == 2)
	{
		if (str_is_digit(av[1]) == 0)
		{
			add_origin(&context->origin, av[1]);
			print_error(context->origin, "numeric argument required", 2);
			return (1);
		}
		sh_state->exit_sig = 1;
		return (ft_atoi(av[1]));
	}
	else if (ac > 2)
	{
		print_error(context->origin, "too many arguments", 2);
		return (1);
	}
	else
	{
		sh_state->exit_sig = 1;
		return (0);
	}
}
