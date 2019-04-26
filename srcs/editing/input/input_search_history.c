/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_search_history.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 04:24:25 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 05:44:22 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_search_history.h"

t_list	*history_search(t_list *hist, char *find)
{
	while (hist)
	{
		if (ft_strstr(hist->content, find) != NULL)
			return (hist);
		hist = hist->next;
	}
	return (NULL);
}

char	*search_in_history(char *searched)
{
	t_list	*active_search_node;
	t_list	*match;

	if ((active_search_node = get_active_search_node()) == NULL ||
active_search_node->next == NULL)
		return (NULL);
	if ((match = history_search(active_search_node, searched)) != NULL)
	{
		set_active_search_node(match);
		return ((char *)match->content);
	}
	return (NULL);
}

int		handle_search_input(t_sh_state *sh_state, t_input_data *input_data)
{
	char	*searched;
	const char	*tmp;
	size_t	len;
	char	*result;

	searched = NULL;
	input_data->processed_chars = input_data->build_buf->len;
	if (is_capability(input_data->build_buf->buf) ||
input_data->build_buf->len > 1)
	{
		if (ft_strncmp(input_data->build_buf->buf, KEY_BS, 1) == 0 ||
ft_strncmp(input_data->build_buf->buf, KEY_BS2, 1) == 0)
		{
			tmp = get_searched();
			len = tmp == NULL ? 0 : ft_strlen(tmp);
			if (len > 0)
			{
				if ((searched = ft_strndup(tmp, len - 1)) == NULL)
					return (1);
			}
		}
	}
	else
	{
		tmp = get_searched();
		len = tmp == NULL ? 0 : ft_strlen(tmp);
		if ((searched = ft_memalloc(len + 2)) == NULL)
			return (1);
		if (tmp != NULL)
			ft_strcpy(searched, tmp);
		ft_strcpy(&(searched[len]), input_data->build_buf->buf);
	}
	if (searched != NULL)
	{
		if (get_active_search_node() == NULL)
			set_active_search_node(sh_state->history);
		if ((result = search_in_history(searched)) != NULL)
		{
			if (set_dyn_buf(input_data->active_buf, result) == 1)
				return (1);
			input_data->rel_cur_pos = 0;
			set_searched(searched);
			if (print_anew(input_data->start_pos, input_data->active_buf,
		input_data->rel_cur_pos) == 1)
				return (1);
		}
		else
		{
			ft_strdel(&searched);
			write(1, "\a", 1);
		}
	}
	return (0);
}
