/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/04 17:40:17 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:37:35 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

int		free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
	return (0);
}

void	free_current_cmd(t_sh_state *sh_state)
{
	t_list	*old;

	old = sh_state->history;
	sh_state->history = sh_state->history->next;
	free(old->content);
	free(old);
}
