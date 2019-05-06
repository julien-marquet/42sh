/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 04:56:29 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 04:56:29 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

int				is_processable(t_cmd *cmd)
{
	char	*str;
	int		res;

	if ((str = ft_strtrim(cmd->str)) == NULL)
		return (0);
	if (ft_strlen(str) == 0)
		res = 0;
	else
		res = 1;
	ft_strdel(&str);
	return (res);
}

void			cut_cmd(t_cmd *acmd, t_cmd *next_cmd)
{
	while (acmd && acmd->next != next_cmd)
		acmd = acmd->next;
	if (acmd)
		acmd->next = NULL;
}

int				parse_exit2(t_cmd *cmd, int ret)
{
	free_cmds(cmd);
	return (ret);
}
