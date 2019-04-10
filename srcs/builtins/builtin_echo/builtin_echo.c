/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:59:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 02:52:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_echo/builtin_echo.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	print_octal(const char *str)
{
	int				res;
	unsigned char	to_print;
	int				ret;
	char			*new;

	ret = get_octal_chars_nb(str);
	if (ret > 4)
		new = ft_strndup(str, 4);
	else
		new = NULL;
	res = ft_atoi(new ? new : str);
	res = convert_to_decimal(res);
	to_print = (unsigned char)res;
	write(1, &to_print, 1);
	if (new)
	{
		free(new);
		ret = 4;
	}
	return (ret);
}

static int	print_extended(const char *str, int fd)
{

	if (*str == '0')
		return (print_octal(str));
	else if (*str == 'a')
		write(fd, "\a", 1);
	else if (*str == 'b')
		write(fd, "\b", 1);
	else if (*str == 'f')
		write(fd, "\f", 1);
	else if (*str == 'n')
		write(fd, "\n", 1);
	else if (*str == 'r')
		write(fd, "\r", 1);
	else if (*str == 't')
		write(fd, "\t", 1);
	else if (*str == 'v')
		write(fd, "\v", 1);
	else if (*str == '\\')
		write(fd, "\\", 1);
	else
	{
		write(fd, "\\", 1);
		write(fd, str, 1);
	}
	return (1);
}

static int	handle_ext(const char *str, int fd)
{
	int		res;
	int		tmp;

	res = 0;
	while (*str)
	{
		if (*str != '\\')
		{
			write(fd, str, 1);
			str++;
		}
		else
		{
			str++;
			if (*str == 'c')
				res = 1;
			else
			{
				tmp = print_extended(str, fd);
				str += tmp;
			}
		}
	}
	return (res);
}

static void	printer(int i, int fd, const char **av, const char *opts)
{
	int		first;
	int		ext_opt;
	int		no_nl_opt;

	first = 1;
	ext_opt = opts && ft_strchr(opts, 'e') != NULL;
	no_nl_opt = opts && ft_strchr(opts, 'n') != NULL;
	while (av[i] != NULL)
	{
		if (first)
			first = 0;
		else
			write(fd, " ", 1);
		if (ext_opt == 1)
			no_nl_opt |= handle_ext(av[i], fd);
		else
			ft_putstr_fd(av[i], fd);
		i++;
	}
	if (!opts || !no_nl_opt)
		write(fd, "\n", 1);
}

int			builtin_echo(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;
	char	*opts;

	add_origin(&context->origin, "echo");
	if ((i = handle_builtin_options(av, "ne", &opts, context)) == -1)
		return (1);
	else if (i == 0)
	{
		print_error(context->origin, "usage: echo [-ne] [args ... ]",
	context->fds.err);
		return (1);
	}
	else
		printer(i, context->fds.out, av, opts);
	ft_strdel(&opts);
	return (0);
}
