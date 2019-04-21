/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:03:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 22:03:57 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse_alias.h"

static char		*alias_getfirstword(char *str, int *start, int *i)
{
	int		is_var;
	char	*tmp;

	while (str[*i])
	{
		is_var = 0;
		while (str[*i] && ft_isspace(str[*i]))
			(*i)++;
		(*start) = (*i);
		while (str[*i] && !ft_isspace(str[*i]) && !stresc(";|&", str, *i))
		{
			if (str[*i] == '=')
				is_var = 1;
			(*i)++;
		}
		if (is_var == 0)
			break ;
	}
	tmp = ft_strndup(str + (*start), (*i) - (*start));
	return (tmp);
}

static int		alias_getnext(char *str, int i)
{
	while (str[i] && !stresc(";|&", str, i))
	{
		while (str[i] && is_quoted(str, i))
			i++;
		str[i] ? i++ : 0;
	}
	while (str[i] && stresc(";|&", str, i))
		i++;
	return (i);
}

static char		*alias_handle(char *tmp, t_list *aliases, t_list *skip)
{
	char	*alias;
	char	*ret;

	ret = NULL;
	if (find_alias_by_name(aliases, tmp) && skiplst_check(tmp, skip))
	{
		if (!(alias = get_alias(aliases, tmp)))
			return (NULL);
		if (!(skip = skiplst_handle(tmp, &skip)))
		{
			ft_strdel(&alias);
			return (NULL);
		}
		if ((ret = parse_alias(alias, aliases, skip)))
		{
			skip = skiplst_last(skip);
			ft_strdel(&alias);
			return (ret);
		}
		ft_strdel(&alias);
	}
	return (NULL);
}

char			*parse_alias(char *line, t_list *aliases, t_list *skip)
{
	int		i;
	int		start;
	char	*str;
	char	*tmp;
	char	*ret;

	i = 0;
	start = 0;
	if (!(str = ft_strdup(line)))
		return (NULL);
	while (str[i])
	{
		if (!(tmp = alias_getfirstword(str, &start, &i)))
			return (NULL);
		if ((ret = alias_handle(tmp, aliases, skip)))
		{
			if (!(str = strinsert(str, ret, start, i)))
				return (NULL);
			i = start + ft_strlen(ret);
		}
		ft_strdel(&ret);
		i = alias_getnext(str, i);
		ft_strdel(&tmp);
	}
	return (str);
}
