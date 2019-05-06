/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 03:02:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 10:16:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_utils.h"

static int	check_validity(const char *str, const char *valid,
t_builtin_context *context)
{
	size_t	i;
	char	*err;
	char	inv_char[2];

	i = 1;
	inv_char[1] = '\0';
	while (str[i] != '\0')
	{
		if (valid == NULL || ft_strchr(valid, str[i]) == NULL)
		{
			inv_char[0] = str[i];
			if ((err = ft_construct_str(3, "-", inv_char,
		": invalid option")) == NULL)
				return (-1);
			print_error(context->origin, err, 2);
			free(err);
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

int			handle_builtin_options(const char **av, const char *valid,
char **valid_options, t_builtin_context *context)
{
	int		args_i;
	int		res;

	args_i = 1;
	*valid_options = NULL;
	while (av[args_i] && av[args_i][0] == '-' && av[args_i][1] != '\0')
	{
		if ((res = check_validity(av[args_i], valid, context)) <= 0)
		{
			ft_strdel(valid_options);
			return (res);
		}
		if (add_to_valid(av[args_i], valid_options) == 1)
			return (-1);
		args_i++;
	}
	return (args_i);
}

int			add_origin(char **origin, const char *src)
{
	char	*tmp;

	if (origin && src)
	{
		tmp = *origin;
		if ((*origin = ft_construct_str(3, tmp, src, ": ")) == NULL)
			return (1);
		ft_strdel(&tmp);
	}
	return (0);
}

void		free_builtin_context(t_builtin_context **builtin_context)
{
	ft_strdel(&(*builtin_context)->origin);
	free(*builtin_context);
	*builtin_context = NULL;
}
