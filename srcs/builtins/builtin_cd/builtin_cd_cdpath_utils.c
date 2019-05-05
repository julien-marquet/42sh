/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd_cdpath_utils.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 15:16:32 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:17:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd/builtin_cd.h"

int		get_prec_slash_pos(char *path, int i)
{
	if (i > 0)
		i--;
	while (i > 0)
	{
		if (path[i] == '/')
			return (i);
		i--;
	}
	return (i);
}

int		count_unnecessary_slashes(char *path, int i)
{
	int		cpt;

	cpt = 0;
	i++;
	while (path[i] == '/')
	{
		cpt++;
		i++;
	}
	return (cpt);
}

int	remove_dot(char **path, int *i)
{
	if (ft_strncmp(&(*path)[*i], "/.", 2) == 0 &&
((*path)[*i + 2] == '\0' || (*path)[*i + 2] == '/'))
	{
		ft_strcpy(&(*path)[*i], &(*path)[*i + 2]);
		*i -= 1;
		return (1);
	}
	return (0);
}

int	remove_dot_dot(char **path, int *i)
{
	int		j;

	if (ft_strncmp(&(*path)[*i], "/..", 3) == 0 &&
((*path)[*i + 3] == '\0' || (*path)[*i + 3] == '/'))
	{
		j = get_prec_slash_pos(*path, *i);
		ft_strcpy(&(*path)[j],
	&(*path)[*i + 3]);
		*i = j - 1;
		return (1);
	}
	return (0);
}

int	remove_slashes(char **path, int *i)
{
	int		j;

	if ((j = count_unnecessary_slashes(*path, *i)) > 0)
	{
		if ((*i == 0 && j > 1) || (*i != 0))
		{
			ft_strcpy(&(*path)[*i],
		&(*path)[*i + j]);
			*i -= 1;
			return (1);
		}
	}
	return (0);
}