/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_alias.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:03:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 22:36:30 by mmoya       ###    #+. /#+    ###.fr     */
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
		tmplst = ft_lstnew(tmp, ft_strlen(tmp) + 1);
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
/*
static t_list	*ft_test(char *tmp, t_list *aliases, t_list *skip)
{
	char	*alias;
	char	*ret;
	
	skip = skiplst_handle(tmp, &skip);
	alias = get_alias(aliases, tmp);
	ft_strdel(&tmp);
	ret = parse_alias(alias, aliases, skip);
	ft_strdel(&alias);
	skip = skiplst_last(skip);
	str = strinsert(str, ret, j, i);
	i = j + ft_strlen(ret);
	ft_strdel(&ret);
}
*/
char			*parse_alias(char *src, t_list *aliases, t_list *skip)
{
	int i;
	int j;
	int is_var;
	char *str;
	char *tmp;
	char	*alias;
	char	*ret;

	is_var = 0;
	i = 0;
	str = ft_strdup(src);
	tmp = NULL;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
		{
			i++;
		}
		j = i;
		while (str[i] && !ft_isspace(str[i]))
		{
			if (str[i] == '=')
				is_var = 1;
			i++;
		}
		tmp = ft_strndup(str + j, i - j);

		if (find_alias_by_name(aliases, tmp) && skiplst_check(tmp, skip))
		{
			skip = skiplst_handle(tmp, &skip);
			alias = get_alias(aliases, tmp);
			ft_strdel(&tmp);
			ret = parse_alias(alias, aliases, skip);
			ft_strdel(&alias);
			skip = skiplst_last(skip);
			str = strinsert(str, ret, j, i);
			i = j + ft_strlen(ret);
			ft_strdel(&ret);
		}
		ft_strdel(&tmp);


		while (str[i] && !stresc(";|&", str, i))
		{
			while (str[i] && is_quoted(str, i))
				i++;
			str[i] ? i++ : 0;
		}
		while (str[i] && stresc(";|&", str, i))
			i++;
	}
	return (str);
}
