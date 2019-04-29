/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:59:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 15:31:47 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_echo/builtin_echo.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	print_octal(const char *str, int *err)
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
	if (write(1, &to_print, 1) == -1)
		*err = 1;
	if (new)
	{
		free(new);
		ret = 4;
	}
	return (ret);
}

static int	print_extended(const char *str, int fd, int *err)
{

	if (*str == '0')
		return (print_octal(str, err));
	else if (*str == 'a' && write(fd, "\a", 1))
		*err = 1;
	else if (*str == 'b' && write(fd, "\b", 1))
		*err = 1;
	else if (*str == 'f' && write(fd, "\f", 1))
		*err = 1;
	else if (*str == 'n' && write(fd, "\n", 1))
		*err = 1;
	else if (*str == 'r' && write(fd, "\r", 1))
		*err = 1;
	else if (*str == 't' && write(fd, "\t", 1))
		*err = 1;
	else if (*str == 'v' && write(fd, "\v", 1))
		*err = 1;
	else if (*str == '\\' && write(fd, "\\", 1))
		*err = 1;
	else
	{
		if (write(fd, "\\", 1) == -1 || write(fd, str, 1) == -1)
			*err = 1;
	}
	return (1);
}

static int	handle_ext(const char *str, int fd, int *err)
{
	int		res;
	int		tmp;

	res = 0;
	while (*str)
	{
		if (*str != '\\')
		{
			if (write(fd, str, 1) == -1)
				*err = 1;
			str++;
		}
		else
		{
			str++;
			if (*str == 'c')
				res = 1;
			else
			{
				tmp = print_extended(str, fd, err);
				str += tmp;
			}
		}
	}
	return (res);
}

static int	printer(int i, int fd, const char **av, const char *opts)
{
	int		first;
	int		ext_opt;
	int		no_nl_opt;
	int		err;

	err = 0;
	first = 1;
	ext_opt = opts && ft_strchr(opts, 'e') != NULL;
	no_nl_opt = opts && ft_strchr(opts, 'n') != NULL;
	while (av[i] != NULL)
	{
		if (first)
			first = 0;
		else if (write(fd, " ", 1) == -1)
			return (1);
		if (ext_opt == 1)
			no_nl_opt |= handle_ext(av[i], fd, &err);
		else if (write(fd, av[i], ft_strlen(av[i])) == -1)
			return (1);
		i++;
	}
	if (err != 0)
		return (err);
	if (!opts || !no_nl_opt)
		return (write(fd, "\n", 1) == -1);
	return (0);
}

int			builtin_echo(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;
	char	*opts;
	int		res;

	res = 0;
	add_origin(&context->origin, "echo");
	if ((i = handle_builtin_options(av, "ne", &opts, context)) == -1)
		res = 1;
	else if (i == 0)
	{
		print_error(context->origin, "usage: echo [-ne] [args ... ]", 2);
		res = 1;
	}
	else if (printer(i, 1, av, opts) != 0)
		res = 1;
	ft_strdel(&opts);
	return (res);
}
