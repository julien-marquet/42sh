/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_exit.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:38:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 05:57:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "error_handler.h"
#include "builtins/builtin_exit.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	check_error(char *arg)
{
	char	*tmp;
	char	*pointer;

	pointer = arg;
	while (*pointer)
	{
		if (*pointer < 48 || *pointer > 57)
		{
			if ((tmp =
		ft_construct_str(6, NAME, ": ", "exit", ": ", arg, ": ")) == NULL)
				return (-1);
			print_error(tmp, "numeric argument required", 2);
			free(tmp);
			return (-1);
		}
		pointer += 1;
	}
	return (0);
}

int		builtin_exit(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	if (check_error((char *)(*(av + 1))) == -1)
		return (1);
	if (ac > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	sh_state->exit_sig = 1;
	if (ac > 1)
		return (ft_atoi(av[1]));
	else
		return (0);
}
