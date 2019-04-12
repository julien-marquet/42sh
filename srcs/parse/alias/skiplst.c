/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   skiplst.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 23:50:54 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 23:51:30 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse_alias.h"

int		skiplst_check(char *tmp, t_list *skip)
{
	while (skip)
	{
		if (skip->content == NULL || tmp == NULL)
			return (0);
		if (ft_strcmp(skip->content, tmp) == 0)
			return (0);
		skip = skip->next;
	}
	return (1);
}

t_list	*skiplst_handle(char *tmp, t_list **skip)
{
	t_list *tmplst;

	if (!*skip)
		*skip = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	else
	{
		if (!(tmplst = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			return (NULL);
		ft_lstadd(skip, tmplst);
	}
	return (*skip);
}

t_list	*skiplst_last(t_list *skip)
{
	t_list *start;

	start = skip->next;
	ft_strdel((char**)&skip->content);
	free(skip);
	return (start);
}