/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_history.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 23:50:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 02:07:55 by mmoya       ###    #+. /#+    ###.fr     */
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

static char	*add_event_history(t_sh_state *sh_state, char *str, int change)
{
	t_list *old;

	if (change)
	{
		old = sh_state->history;
		sh_state->history = sh_state->history->next;
		free(old->content);
		free(old);
		if (add_to_history_list(&(sh_state->history),
			str, ft_strlen(str)) == NULL)
			return (NULL);
	}
	return (str);
}

static char	*expand_event(char *str, size_t start,
size_t i, t_sh_state *sh_state)
{
	t_list	*new;
	char	*tmp;

	new = sh_state->history;
	if (str[start] == '!')
		new = get_history_index(new, 1);
	else if (ft_isdigit(str[start]))
		new = get_history_index_rev(new, ft_atoi(str + start));
	else if (str[start] == '-')
		new = get_history_index(new, ft_atoi(str + start + 1));
	else
	{
		if (!(tmp = ft_strndup(str + start, i - start)))
			return (NULL);
		new = get_history_search(new, tmp);
		ft_strdel(&tmp);
	}
	return (new ? ft_strdup(new->content) : NULL);
}

static char	*event_hanlder(char *str, size_t *i, t_sh_state *sh_state)
{
	size_t	start;
	char	*tmp;

	start = (*i);
	tmp = NULL;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	if ((tmp = expand_event(str, start + 1, *i, sh_state)))
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

char		*parse_event(char *str, t_sh_state *sh_state)
{
	char	*tmp;
	size_t	i;
	int		change;

	i = 0;
	change = 0;
	if (!(str = ft_strdup(str)))
		return (NULL);
	while (str[i])
	{
		while (str[i] && is_quoted(str, i) == 1)
			i++;
		if (stresc("!", str, i) && !ft_strchr(" \n}=", str[i + 1]))
		{
			change = 1;
			if ((tmp = event_hanlder(str, &i, sh_state)) == NULL)
			{
				ft_strdel(&str);
				return (NULL);
			}
			str = tmp;
		}
		str[i] ? i++ : 0;
	}
	return (add_event_history(sh_state, str, change));
}
