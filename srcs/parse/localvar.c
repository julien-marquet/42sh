/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   localvar.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:43:22 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 02:27:09 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/localvar.h"

static int	store_localvar(char *str, int i, int len, t_sh_state *sh_state)
{
	char *name;
	char *value;

	if (!(name = ft_strndup(str, i++)))
		return (-1);
	if (!(value = strndup_qr(str + i, len - i)))
	{
		ft_strdel(&name);
		return (-1);
	}
	ft_memset(str, ' ', len);
	if (name != NULL && value != NULL)
		add_entry_storage(sh_state, name, value, 2);
	ft_strdel(&name);
	ft_strdel(&value);
	return (1);
}

static int	handle_localvar(t_cmd *cmd, char *str, int len, t_sh_state *sh_state)
{
	int i;

	i = 0;
	while ((ft_isalnum(str[i]) || str[i] == '_' || str[i] == '=') && i < len)
	{
		if (stresc("=", str, i))
		{
			cmd->assign = 1;
			if (store_localvar(str, i, len, sh_state) == 1)
				return (1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int			parse_localvar(t_cmd *cmd, t_sh_state *sh_state)
{
	int i;
	int start;
	int ret;

	i = 0;
	while (cmd->str[i])
	{
		while (cmd->str[i] && ft_isspace(cmd->str[i]))
			i++;
		start = i;
		while (cmd->str[i] && (!stresc(";|<>& \n", cmd->str, i) ||
		is_quoted(cmd->str, i)))
			i++;
		ret = handle_localvar(cmd, cmd->str + start, i - start, sh_state);
		if (ret == 1)
			continue ;
		else if (ret == -1)
			return (1);
		while (cmd->str[i] && !stresc(";|&", cmd->str, i))
			i++;
		cmd->str[i] ? i++ : 0;
	}
	return (0);
}
