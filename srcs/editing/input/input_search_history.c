/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_search_history.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 04:24:25 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 17:25:27 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_search_history.h"

char	*search_in_history(char *searched, int next)
{
	t_list	*active_search_node;

	if ((active_search_node = get_active_search_node()) == NULL ||
active_search_node->next == NULL)
		return (NULL);
	if (next)
		active_search_node = active_search_node->next;
	while (active_search_node)
	{
		if (ft_strstr(active_search_node->content, searched) != NULL)
			break ;
		active_search_node = active_search_node->next;
	}
	if (active_search_node != NULL)
	{
		set_active_search_node(active_search_node);
		return ((char *)active_search_node->content);
	}
	return (NULL);
}

char	*handle_actions(t_input_data *input_data)
{
	const char	*tmp;
	size_t		len;

	if (ft_strncmp(input_data->build_buf->buf, KEY_BS, 1) == 0 ||
	ft_strncmp(input_data->build_buf->buf, KEY_BS2, 1) == 0)
	{
		tmp = get_searched();
		len = tmp == NULL ? 0 : ft_strlen(tmp);
		if (len > 0)
			return (ft_strndup(tmp, len - 1));
	}
	else
	{
		set_search_mode(0);
		input_data->processed_chars = 0;
	}
	return (NULL);
}

char	*append_to_searched(t_input_data *input_data)
{
	const char	*tmp;
	size_t		len;
	char		*searched;

	tmp = get_searched();
	len = tmp == NULL ? 0 : ft_strlen(tmp);
	if ((searched = ft_memalloc(len + 2)) == NULL)
		return (NULL);
	if (tmp != NULL)
		ft_strcpy(searched, tmp);
	ft_strcpy(&(searched[len]), input_data->build_buf->buf);
	return (searched);
}

int		find_in_history(t_sh_state *sh_state, t_input_data *input_data,
char *searched, int next)
{
	char	*result;

	if (searched != NULL)
	{
		if (get_active_search_node() == NULL)
			set_active_search_node(sh_state->history);
		if ((result = search_in_history(searched, next)) != NULL)
		{
			if (set_dyn_buf(input_data->active_buf, result) == 1)
				return (-1);
			input_data->rel_cur_pos = 0;
			set_searched(searched);
			if (update_start_position(input_data->active_buf,
		input_data->start_pos) == 1)
				return (1);
			if (print_anew(input_data->start_pos, input_data->active_buf,
		input_data->rel_cur_pos) == 1)
				return (-1);
			return (1);
		}
	}
	write(1, "\a", 1);
	return (0);
}

int		handle_search_input(t_sh_state *sh_state, t_input_data *input_data)
{
	char	*searched;
	int		result;

	searched = NULL;
	input_data->processed_chars = input_data->build_buf->len;
	if (is_capability(input_data->build_buf->buf) ||
input_data->build_buf->len > 1)
		searched = handle_actions(input_data);
	else
		searched = append_to_searched(input_data);
	if (searched != NULL)
	{
		if ((result = find_in_history(sh_state, input_data, searched, 0)) <= 0)
		{
			ft_strdel(&searched);
			return (result == -1 ? 1 : 0);
		}
	}
	return (0);
}
