/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_edition.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:17:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:13:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/history/history.h"

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

t_list		*add_to_history_list(t_list **history, const char *buf, size_t len)
{
	t_list	*elem;

	if ((elem = ft_lstnew(buf, len)) == NULL)
		return (NULL);
	((char *)(elem->content))[elem->content_size - 1] = '\0';
	ft_lstprepend(history, elem);
	return (*history);
}