/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 03:02:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 06:00:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_utils.h"

static int	is_builtin_option(const char *str)
{
	return (str && str[0] == '-' && str[1] != '\0');
}

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
			print_error(context->origin, err, context->fds.err);
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
	while (is_builtin_option(av[args_i]))
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

t_builtin_context	*duplicate_builtin_context(t_builtin_context *context)
{
	t_builtin_context	*new_context;

	if ((new_context = ft_memalloc(sizeof(t_builtin_context))) == NULL)
		return (NULL);
	new_context->fds = context->fds;
	if ((new_context->origin = ft_strdup(context->origin)) == NULL)
	{
		free(new_context);
		return (NULL);
	}
	return (new_context);
}

const char	**get_builtins_names(void)
{
	static const char	*assoc_names[BUILTINS_NB + 1] = {BUILTINS_NAMES};

	return (assoc_names);
}

int			builtin_exist(const char *name)
{
	const char	**assoc_names;
	int			i;

	assoc_names = get_builtins_names();
	i = 0;
	while (assoc_names[i] != NULL)
	{
		if (ft_strcmp(assoc_names[i], name) == 0)
			return (1);
		i++;
	}
	return (0);
}

const t_builtin_func	*get_builtins_funcs(void)
{
	static const t_assoc_func	assoc_funcs = {BUILTINS_FUNCS};

	return (assoc_funcs);
}