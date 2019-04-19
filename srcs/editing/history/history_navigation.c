/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_navigation.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 10:51:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 02:50:53 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/history/history.h"

t_list			*get_history_index_rev(t_list *history, size_t index)
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

int		history_navigate(t_input_data *input_data, t_list *hist_copy, int action)
{
	static int	index = 0;
	int	old_i;

	if (action == HIST_RESET)
		index = 0;
	else
	{
		old_i = index;
		if (action == HIST_NEXT)
			index++;
		else
			index--;
		if (index < 0)
			return ((index = 0));
		if ((index = navigate(input_data, hist_copy, index, old_i)) == -1)
			return (-1);
		if (index != old_i)
			input_data->rel_cur_pos = input_data->active_buf->len;
	}
	return (index);
}
