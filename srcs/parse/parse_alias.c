/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_alias.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:03:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 00:18:31 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse_alias.h"

static int		skiplst_check(char *tmp, t_list *skip)
{
	while (skip)
	{
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

static int		skip_white_var(char *str, int *i, int *j)
{
	int is_var;

	is_var = 0;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	*j = *i;
	while (str[*i] && !ft_isspace(str[*i]))
	{
		if (str[*i] == '=')
			is_var = 1;
		while (str[*i] && is_quoted(str, *i))
			(*i)++;
		str[*i] ? (*i)++ : 0;
	}
	return (is_var);
}

char			*parse_alias(char *src, t_list *aliases)
{
	int i;
	int j;
	//int is_var;
	char *str;
	char *tmp;
	char *cur;
	char *alias;
	t_list *skip;

	i = 0;
	str = ft_strdup(src);
	cur = NULL;
	tmp = NULL;
	skip = NULL;
	while (str[i])
	{
		ft_strdel(&tmp);
		if (skip_white_var(str, &i, &j))
		{
			while (str[i] && ft_isspace(str[i]))
				i++;
		}
		else
		{
			if (cur == NULL)
				tmp = ft_strndup(str + j, i - j);
			if ((find_alias_by_name(aliases, tmp) && skiplst_check(tmp, skip))
			|| (cur && find_alias_by_name(aliases, cur)))
			{
				dprintf(2, "tmp = %s\n", tmp);
				if (!cur)
					cur = ft_strdup(tmp);
				skiplst_handle(cur, &skip);
				dprintf(2, "%s\n", skip->content);
				alias = get_alias(aliases, cur);
				str = strinsert(str, alias, j, i);
				dprintf(2, "%i to %zu\n", i, j + ft_strlen(alias));
				i = j + ft_strlen(alias);
			}
			while (str[i] && !stresc(";|&", str, i))
				i++;
			while (str[i] && stresc(";|&", str, i))
				i++;
		}
		if (cur && str[i] == 0)
		{
			dprintf(2, "SEDRFTGY\n");
			ft_strdel(&cur);
			i = 0;
			continue ;
		}
	}
	return (str);
}
