/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 19:25:31 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 19:25:32 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_completion.h"

int		lstfree(t_list *list)
{
	t_list	*previous;

	while (list != NULL)
	{
		previous = list;
		list = list->next;
		free(previous->content);
		free(previous);
	}
	return (1);
}

void	lstmerge(t_list **list1, t_list *list2)
{
	t_list	*pointer;

	pointer = *list1;
	if (pointer == NULL)
	{
		*list1 = list2;
		return ;
	}
	while (pointer->next != NULL)
		pointer = pointer->next;
	pointer->next = list2;
}
