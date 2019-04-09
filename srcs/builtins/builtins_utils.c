/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 03:02:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 04:02:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_utils.h"

static int	is_builtin_option(const char *str)
{
	return (str && str[0] == '-' && str[1] != '\0');
}

static int	check_validity(const char *str, const char *valid, int fd_err)
{
	size_t	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (valid == NULL || ft_strchr(valid, str[i]) == NULL)
		{
			dprintf(fd_err, "-%c: invalid option\n", str[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	add_to_valid(const char *str, char **valid_options)
{
	char	*tmp;
	size_t	str_len;
	size_t	opts_len;

	tmp = *valid_options;
	str_len = ft_strlen(str) - 1;
	opts_len = *valid_options == NULL ? 0 : ft_strlen(*valid_options);
	if ((*valid_options = ft_memalloc(str_len + opts_len + 1)) == NULL)
	{
		free(tmp);
		return (1);
	}
	if (tmp != NULL)
		ft_strcpy(*valid_options, tmp);
	free(tmp);
	ft_strcpy(&((*valid_options)[opts_len]), &(str[1]));
	return (0);
}

/*
**	args_i equals 0 if parse error, -1 if critical
**	error otherwise equal index at which
**	non options args start
*/

int		handle_builtin_options(const char **av, const char *valid,
char **valid_options, int fd_err)
{
	int		args_i;

	args_i = 1;
	*valid_options = NULL;
	while (is_builtin_option(av[args_i]))
	{
		if (!check_validity(av[args_i], valid, fd_err))
		{
			ft_strdel(valid_options);
			return (0);
		}
		if (add_to_valid(av[args_i], valid_options) == 1)
			return (-1);
		args_i++;
	}
	return (args_i);
}