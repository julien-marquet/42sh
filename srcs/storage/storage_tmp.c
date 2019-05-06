/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_tmp.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 08:48:27 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 05:48:51 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_tmp.h"

void			remove_tmp_env(t_list **storage)
{
	t_list	*pointer;
	t_list	*previous;
	t_list	*tmp;

	previous = NULL;
	pointer = *storage;
	while (pointer != NULL)
	{
		if (((t_internal_storage *)(pointer->content))->tmp)
		{
			if (previous == NULL)
				*storage = (*storage)->next;
			free(((t_internal_storage *)pointer->content)->string);
			free(pointer->content);
			tmp = pointer;
			if (previous)
				previous->next = pointer->next;
			pointer = (previous == NULL) ? *storage : previous->next;
			free(tmp);
			continue ;
		}
		previous = pointer;
		pointer = pointer->next;
	}
}

static t_list	*init_new_var(t_list *vars)
{
	t_list				*tmp;
	t_internal_storage	new;

	if ((new.string =
	ft_strdup(((t_internal_storage *)(vars->content))->string)) == NULL)
		return (NULL);
	new.exported = 1;
	new.tmp = 1;
	if ((tmp = ft_lstnew(&new, sizeof(t_internal_storage))) == NULL)
	{
		ft_strdel(&new.string);
		return (NULL);
	}
	return (tmp);
}

int				update_builtin_env(t_list **storage, t_list *vars)
{
	t_list				*tmp;
	t_list				*pointer;

	pointer = *storage;
	while (pointer != NULL && pointer->next != NULL)
		pointer = pointer->next;
	while (vars != NULL)
	{
		if (!(tmp = init_new_var(vars)))
			return (-1);
		if (pointer == NULL)
			*storage = tmp;
		else
		{
			pointer->next = tmp;
			pointer = pointer->next;
		}
		vars = vars->next;
	}
	return (0);
}
