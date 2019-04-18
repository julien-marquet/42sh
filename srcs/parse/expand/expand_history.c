/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_history.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 23:50:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 02:48:50 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"
#include "editing/history/history.h"

t_list			*get_history_search(t_list *hist, char *find)
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

char			*expand_event(char *line, int start, int i, t_list *hist)
{
	char	*tmp;

	if (line[start] == '!')
		hist = get_history_index(hist, start);
	else if (ft_isdigit(line[start]))
		hist = get_history_index_rev(hist, ft_atoi(line + start));
	else if (line[start] == '-')
		hist = get_history_index(hist, ft_atoi(line + start + 1));
	else
	{
		if (!(tmp = ft_strndup(line + start, i - start)))
			return (NULL);
		hist = get_history_search(hist, tmp);
		ft_strdel(&tmp);
	}
	return (hist ? ft_strdup(hist->content) : NULL);
}

char			*parse_event(char *line, t_list *hist)
{
	char	*tmp;
	int		start;
	int		i;

	i = 0;
	while (line[i])
	{
		while (is_quoted(line, i) == 1)
			i++;
		if (stresc("!", line, i) && !ft_strchr(" \n", line[i + 1]))
		{
			start = i;
			while (line[i] && !ft_isspace(line[i]))
				i++;
			tmp = expand_event(line, start + 1, i, hist);
			dprintf(2, "%s\n", tmp);
			//strinsert(line, tmp, i, );
		}
		line[i] ? i++ : 0;
	}
	return (line);
}
