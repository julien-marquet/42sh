/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_history.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 23:50:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 16:25:26 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"
#include "editing/history/history.h"

t_list		*get_history_search(t_list *hist, char *find)
{
	if (hist)
		hist = hist->next;
	while (hist)
	{
		if (ft_strstr(hist->content, find) != NULL)
			return (hist);
		hist = hist->next;
	}
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

char		*event_handle(char *str, t_list *hist)
{
	size_t	start;
	size_t	i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		while (str[i] && is_quoted(str, i) == 1)
			i++;
		if (stresc("!", str, i) && !ft_strchr(" \n", str[i + 1]))
		{
			start = i;
			while (str[i] && !ft_isspace(str[i]))
				i++;
			if ((tmp = expand_event(str, start + 1, i, hist)))
			{
				if (!(str = strinsert(str, tmp, start, i)))
					return (NULL);
				i = start + ft_strlen(tmp);
				ft_strdel(&tmp);
			}
		}
		str[i] ? i++ : 0;
	}
	return (str);
}

char		*parse_event(char *str, t_list *hist)
{
	if (!(str = ft_strdup(str)))
		return (NULL);
	return (event_handle(str, hist));
}
