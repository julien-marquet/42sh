/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 19:40:53 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 15:02:54 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

/*
static int		split_wordlen(char *str, int i, int start)
{
	char c;

	if (str[i] == '"' || str[i] == '\'')
	{
		c = str[i];
		start = i++;
		while (str[i] && str[i] != c)
			i++;
		str[i] ? i++ : 0;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (i);
}

static t_list	*split_listfill(t_list *lst, char *str, int len)
{
	t_list	*tmp;

	if (lst == NULL)
	{
		lst = ft_lstnew(str, len);
		return (lst);
	}
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = ft_lstnew(str, len);
	return (tmp);
}

t_list			*split_strtolist(char *str)
{
	t_list	*lst;
	char	*tmp;
	int		i;
	int		start;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		start = i;
		i = split_wordlen(str, i, start);
		tmp = ft_strndup(str + start, i - start);
		lst = split_listfill(lst, tmp, i - start);
	}
	return (lst);
}
*/

char	*strndup_qr(char *str, size_t len)
{
	int	i;

	i = 0;
	str = ft_strndup(str, len);
	while (str[i])
	{
		if (str[i] == '\\')
		{
			ft_memcpy(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			i++;
		}
		else if (str[i] == '"' || str[i] == '\'')
			ft_memcpy(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
		else
			i++;
	}
	return (str);
}

char	*strinsert(char *dst, char *new, size_t i, size_t end)
{
	char	*out;
	size_t	len;

	len = ft_strlen(dst) - (end - i) + ft_strlen(new);
	if (!(out = ft_strnew(len)))
		return (NULL);
	len = i + ft_strlen(new);
	ft_memcpy(out, dst, i);
	ft_memcpy(out + i, new, ft_strlen(new));
	ft_memcpy(out + len, dst + end, ft_strlen(dst + end));
	ft_strdel(&dst);
	return (out);
}

/*
**	ft_strchr with backslash escape
*/

char	*stresc(char *find, char *str, int i)
{
	char	*out;
	int		k;

	out = ft_strchr(find, str[i]);
	if (out && i > 0)
	{
		if (*out == '&' && str[i - 1] == '>')
			return (NULL);
		k = --i;
		while (i >= 0 && str[i] == '\\')
			i--;
		if ((k - i) % 2)
			return (NULL);
	}
	return (out);
}

int		is_quoted(char *str, int i)
{
	int	j;
	int	q;
	int	dq;

	j = 0;
	q = 0;
	dq = 0;
	while (str[j] && j <= i)
	{
		if (stresc("\"", str, j) && !q)
			dq = dq == 2 ? 0 : 2;
		if ((stresc("'", str, j) || (q == 1 && str[j] == '\'')) && !dq)
			q = q == 1 ? 0 : 1;
		j++;
	}
	return (dq ? dq : q);
}
