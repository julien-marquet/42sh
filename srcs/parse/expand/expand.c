/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 23:23:18 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"

int		parse_expansion(t_cmd *cmd, t_sh_state *sh_state)
{
	parse_tilde(cmd, sh_state);
	if (parse_param(cmd, sh_state))
		return (1);
	parse_localvar(cmd, sh_state);
	return (0);
}

char	*get_expand_str(char *str, t_sh_state *sh_state)
{
	t_cmd	*cmd;
	size_t	len;

	len = ft_strlen(str);
	if (!(cmd = parse_cmdcreate(str, len, NULL, 0)))
		return (NULL);
	parse_param(cmd, sh_state);
	if (!(str = ft_strdup(cmd->str)))
		return (NULL);
	parse_nextfree(cmd);
	return (str);
}
