/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   localvarutils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 04:39:42 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 04:39:43 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/localvar.h"

int			is_var(char *str)
{
	char	**arr;

	if ((arr = ft_strsplit(str, '=')) == NULL)
		return (-1);
	if (*arr == NULL || *(arr + 1) == NULL)
	{
		ft_freetab(&arr);
		return (0);
	}
	if (ft_strchr(*arr, '"') == NULL && ft_strchr(*arr, '\'') == NULL)
	{
		ft_freetab(&arr);
		return (1);
	}
	ft_freetab(&arr);
	return (0);
}

static void	forward(char *str, size_t *i)
{
	if (str[*i] == '"' && stresc(str, str, *i) != NULL)
	{
		*i += 1;
		while (str[*i] != '"')
			*i += 1;
	}
	if (str[*i] == '\'' && stresc(str, str, *i) != NULL)
	{
		*i += 1;
		while (str[*i] != '\'')
			*i += 1;
	}
}

int			is_tmp(char *str)
{
	size_t	i;
	int		ret;
	size_t	is_tmp;

	i = 0;
	is_tmp = 0;
	while (str[i])
	{
		forward(str, &i);
		if (is_stopping(str[i]) && str[i] != ' ' &&
	(i == 0 || (i > 0 && stresc(str, str, i) != NULL)))
			return (is_tmp);
		if (str[i] != ' ' && str[i] != '\n')
		{
			if ((ret = is_var(&(str[i]))) == -1)
				return (-1);
			return (!ret);
		}
		i += 1;
	}
	return (is_tmp);
}
