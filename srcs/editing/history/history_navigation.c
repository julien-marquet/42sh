/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_navigation.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 10:51:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 04:18:04 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/history/history.h"

t_list		*get_history_search(t_list *hist, char *find)
{
	size_t	len;

	len = ft_strlen(find);
	if (hist)
		hist = hist->next;
	while (hist)
	{
		if (ft_strncmp(hist->content, find, len) == 0)
			return (hist);
		hist = hist->next;
	}
	return (NULL);
}

t_list		*get_history_index_rev(t_list *history, size_t index)
{
	size_t	i;
	t_list	*cur;
	t_list	*behind;

	cur = history;
	i = 1;
	if (index < 1)
		return (NULL);
	while (i < index)
	{
		if (cur->next)
			cur = cur->next;
		else
			return (NULL);
		i++;
	}
	behind = history;
	while (cur->next)
	{
		cur = cur->next;
		behind = behind->next;
	}
	return (behind);
}

t_list		*get_history_index(t_list *history, size_t index)
{
	size_t	i;
	t_list	*tmp_hist;

	tmp_hist = history;
	i = 0;
	while (i < index && tmp_hist != NULL)
	{
		tmp_hist = tmp_hist->next;
		i++;
	}
	return (tmp_hist);
}

static void	update_index(int action, int *index, t_input_data *input_data)
{
	if (action == HIST_NEXT)
	{
		(*index)++;
		if (input_data->here_doc != NULL &&
	input_data->stored_buf->len > 0 && *index == 1)
			(*index)++;
	}
	else
	{
		(*index)--;
		if (input_data->here_doc != NULL &&
	input_data->stored_buf->len > 0 && *index == 1)
			(*index)--;
	}
}

int			history_navigate(t_input_data *input_data,
t_list *hist_copy, int action)
{
	static int	index = 0;
	int			old_i;

	if (action == HIST_RESET)
		index = 0;
	else
	{
		old_i = index;
		update_index(action, &index, input_data);
		if (index < 0)
			return ((index = 0));
		if ((index = navigate(input_data, hist_copy, index, old_i)) == -1)
			return (-1);
		if (index != old_i)
			input_data->rel_cur_pos = input_data->active_buf->len;
	}
	return (index);
}
