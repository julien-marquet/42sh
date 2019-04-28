/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_history.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 23:50:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 00:42:29 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"
#include "editing/history/history.h"

static char	*event_error(char *str, size_t len)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(": ", 2);
	write(2, str, len);
	ft_putstr_fd(": event not found\n", 2);
	return (NULL);
}

static char	*expand_event(char *str, size_t start, size_t i, t_list *hist)
{
	char	*tmp;

	if (str[start] == '!')
		hist = get_history_index(hist, 1);
	else if (ft_isdigit(str[start]))
		hist = get_history_index_rev(hist, ft_atoi(str + start));
	else if (str[start] == '-')
		hist = get_history_index(hist, ft_atoi(str + start + 1));
	else
	{
		if (!(tmp = ft_strndup(str + start, i - start)))
			return (NULL);
		hist = get_history_search(hist, tmp);
		ft_strdel(&tmp);
	}
	return (hist ? ft_strdup(hist->content) : NULL);
}

static char	*event_hanlder(char *str, size_t *i, t_list *hist)
{
	size_t	start;
	char	*tmp;

	start = (*i);
	tmp = NULL;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	if ((tmp = expand_event(str, start + 1, *i, hist)))
	{
		if (!(str = strinsert(str, tmp, start, *i)))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
		(*i) = start + ft_strlen(tmp);
		ft_strdel(&tmp);
	}
	else
		return (event_error(str + start, (*i) - start));
	return (str);
}

char		*parse_event(char *str, t_list *hist)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(str = ft_strdup(str)))
		return (NULL);
	while (str[i])
	{
		while (str[i] && is_quoted(str, i) == 1)
			i++;
		if (stresc("!", str, i) && !ft_strchr(" \n}", str[i + 1]))
		{
			tmp = event_hanlder(str, &i, hist);
			if (tmp == NULL)
			{
				ft_strdel(&str);
				return (NULL);
			}
			str = tmp;
		}
		str[i] ? i++ : 0;
	}
	return (str);
}