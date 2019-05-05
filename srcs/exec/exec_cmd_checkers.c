/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_cmd_checkers.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 01:05:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 20:00:22 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_cmd_checkers.h"

int		cmd_is_empty(t_cmd *cmd)
{
	return (cmd == NULL || (cmd->arg == NULL &&
cmd->assign == 0 && cmd->red == NULL));
}

int		cmd_is_null(t_cmd *cmd)
{
	return ((cmd->arg == NULL));
}

int		is_end_flag(const char *red)
{
	return (red == NULL || ft_strcmp(red, "&") == 0 ||
ft_strcmp(red, ";") == 0);
}

int		is_pipe_flag(const char *red)
{
	return (ft_strcmp(red, "|") == 0);
}

int		is_conditionned_flag(const char *red)
{
	return (ft_strcmp(red, "&&") == 0 ||
ft_strcmp(red, "||") == 0);
}
