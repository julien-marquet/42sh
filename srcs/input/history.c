/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 10:51:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/21 20:54:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/history.h"
#include "utils/dyn_buf.h"

t_list		*init_history_list(void)
{
	return (NULL);
}

t_list		*add_to_history_list(t_list **history, const char *buf, size_t len)
{
	t_list	*elem;

	if ((elem = ft_lstnew(buf, len)) == NULL)
		return (NULL);
	((char *)(elem->content))[elem->content_size - 1] = '\0';
	ft_lstprepend(history, elem);
	return (*history);
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

t_list		*edit_history_index(t_list *history, size_t index, const char *buf)
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
	if (tmp_hist != NULL)
	{
		ft_memdel(&(tmp_hist->content));
		tmp_hist->content_size = ft_strlen(buf);
		if ((tmp_hist->content = malloc(tmp_hist->content_size + 1)) == NULL)
			return (NULL);
		ft_memcpy(tmp_hist->content, buf, tmp_hist->content_size);
		((char *)(tmp_hist->content))[tmp_hist->content_size] = '\0';
	}
	return (history);
}

int		history_navigate(t_input_data *input_data, t_list *hist_copy, int action)
{
	static int	index = 0;
	int	old_i;
	t_list	*hist_entry;

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
		if (index == 0)
		{
			if (old_i >= 1 + (input_data->stored_buf->len > 0))
				edit_history_index(hist_copy, old_i - (1 + (input_data->stored_buf->len > 0)), input_data->active_buf->buf); 
			set_dyn_buf(input_data->active_buf, input_data->initial_buf->buf);
		}
		else
		{
			if (old_i == 0)
			{
				set_dyn_buf(input_data->initial_buf, input_data->active_buf->buf);
			}
			if (index == 1 && input_data->stored_buf->len > 0)
			{
				if (old_i >= 1 + (input_data->stored_buf->len > 0))
					edit_history_index(hist_copy, old_i - (1 + (input_data->stored_buf->len > 0)), input_data->active_buf->buf); 
				set_n_dyn_buf(input_data->active_buf, input_data->stored_buf->buf, input_data->stored_buf->len - 1);
			}
			else
			{
				if ((hist_entry = get_history_index(hist_copy,
			index - (1 + (input_data->stored_buf->len > 0)))) == NULL)
				{
					index = old_i;
					return (index);
				}
				else
				{
					if (old_i >= 1 + (input_data->stored_buf->len > 0))
						edit_history_index(hist_copy, old_i - (1 + (input_data->stored_buf->len > 0)), input_data->active_buf->buf); 
					set_dyn_buf(input_data->active_buf, (char *)(hist_entry->content));
				}
			}
		}
		input_data->rel_cur_pos = input_data->active_buf->len;
	}
	return (index);
}
