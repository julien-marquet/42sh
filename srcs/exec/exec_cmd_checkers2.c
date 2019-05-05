/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_cmd_checkers2.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 19:57:46 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:05:09 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_cmd_checkers.h"

int		is_background(t_cmd *cmd_list)
{
	while (!cmd_is_empty(cmd_list))
	{
		if (cmd_is_empty(cmd_list->next))
		{
			return (cmd_list->red != NULL &&
		ft_strcmp(cmd_list->red, "&") == 0);
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

int		is_last(t_cmd *cmd_list)
{
	if (cmd_is_empty(cmd_list->next))
		return (1);
	else if (ft_strcmp(cmd_list->red, "&&") == 0 ||
ft_strcmp(cmd_list->red, "||") == 0)
		return (1);
	return (0);
}

int		is_new_proc_grp(t_context *context)
{
	if (context->proc_grp != NULL && context->proc_grp->last_red != NULL)
		return (0);
	return (1);
}
