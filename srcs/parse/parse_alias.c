/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_alias.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:03:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 00:22:06 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse_alias.h"

static int		skiplst_check(char *tmp, t_list *skip)
{
	while (skip)
	{
		if (skip->content == NULL || tmp == NULL)
			return (0);
		if (ft_strcmp(skip->content, tmp) == 0)
			return (0);
		skip = skip->next;
	}
	return (1);
}

static t_list	*skiplst_handle(char *tmp, t_list **skip)
{
	t_list *tmplst;

	if (!*skip)
		*skip = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	else
	{
		if (!(tmplst = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			return (NULL);
		ft_lstadd(skip, tmplst);
	}
	return (*skip);
}

static t_list	*skiplst_last(t_list *skip)
{
	t_list *start;

	start = skip->next;
	ft_strdel((char**)&skip->content);
	free(skip);
	return (start);
}

static char		*alias_getfirstword(char *str, int *start, int *i)
{
	int		is_var;
	char	*tmp;

	is_var = 0;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	(*start) = (*i);
	while (str[*i] && !ft_isspace(str[*i]))
	{
		if (str[*i] == '=')
			is_var = 1;
		(*i)++;
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

/*
static void		alias_handle(char *tmp, t_list *aliases, t_list *skip)
{
	if (find_alias_by_name(aliases, tmp) && skiplst_check(tmp, skip))
	{
		skip = skiplst_handle(tmp, &skip);
		alias = get_alias(aliases, tmp);
		ft_strdel(&tmp);
		if ((ret = parse_alias(alias, aliases, skip)))
		{
			skip = skiplst_last(skip);
			str = strinsert(str, ret, start, i);
			i = start + ft_strlen(ret);
			ft_strdel(&ret);
		}
		ft_strdel(&alias);
	}
}*/

static char		*alias_handle(char *tmp, t_list *aliases, t_list *skip)
{
	char	*alias;
	char	*ret;

	ret = NULL;
	if (find_alias_by_name(aliases, tmp) && skiplst_check(tmp, skip))
	{
		if (!(alias = get_alias(aliases, tmp)))
		{
			ft_strdel(&alias);
			return (NULL);
		}
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
	str = ft_strdup(line);
	while (str[i])
	{
		tmp = alias_getfirstword(str, &start, &i);
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
