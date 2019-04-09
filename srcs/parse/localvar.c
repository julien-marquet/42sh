/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   localvar.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:43:22 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 00:21:57 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/localvar.h"

static int	store_localvar(char *str, int i, int len, t_sh_state *sh_state)
{
	char *name;
	char *value;

	name = ft_strndup(str, i++);
	value = strndup_qr(str + i, len - i);
	ft_memset(str, ' ', len);
	if (name != NULL && value != NULL)
		add_entry_storage(&sh_state->internal_storage, name, value, 0);
	ft_strdel(&name);
	ft_strdel(&value);
	return (1);
}

static	int	handle_localvar(char *str, int len, t_sh_state *sh_state)
{
	int i;

	i = 0;
	while ((ft_isalnum(str[i]) || str[i] == '_' || str[i] == '=') && i < len)
	{
		if (stresc("=", str, i))
			return (store_localvar(str, i, len, sh_state));
		i++;
	}
	return (0);
}

int			parse_localvar(t_cmd *cmd, t_sh_state *sh_state)
{
	int i;
	int start;

	i = 0;
	while (cmd->str[i])
	{
		while (cmd->str[i] && ft_isspace(cmd->str[i]))
			i++;
		start = i;
		while (cmd->str[i] && !ft_isspace(cmd->str[i]))
		{
			while (cmd->str[i] && is_quoted(cmd->str, i))
				i++;
			cmd->str[i] ? i++ : 0;
		}
		if (handle_localvar(cmd->str + start, i - start, sh_state) == 1)
			continue ;

		while (cmd->str[i] && !stresc(";|&", cmd->str, i))
			i++;
		cmd->str[i] ? i++ : 0;
	}
	return (0);
}