/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   localvar.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:43:22 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 16:27:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/localvar.h"

static void	add_tmp_entry(t_cmd *cmd, char *name, char *value)
{
	t_list				*node;
	t_internal_storage	entry;

	if (is_valid_var_name(name) == 0)
		return ;
	if (fill_entry(&entry, name, value,
		ft_strlen(name) + ft_strlen(value) + 1) == 1)
		return ;
	if ((node = ft_lstnew(&entry, sizeof(t_internal_storage))) == NULL)
		return ;
	ft_lstprepend(&(cmd->env), node);
}

static int	store_localvar(char *str, int params[2],
t_sh_state *sh_state, t_cmd *cmd)
{
	char *name;
	char *value;

	if (!(name = ft_strndup(str, params[0]++)))
		return (-1);
	if (!(value = strndup_qr(str + params[0], params[1] - params[0])))
	{
		ft_strdel(&name);
		return (-1);
	}
	ft_memset(str, ' ', params[1]);
	if (name != NULL && value != NULL)
	{
		if (is_tmp(str + params[1]))
			add_tmp_entry(cmd, name, value);
		else
			add_entry_storage(sh_state, name, value, 2);
	}
	ft_strdel(&name);
	ft_strdel(&value);
	return (1);
}

static int	handle_localvar(t_cmd *cmd, char *str,
int len, t_sh_state *sh_state)
{
	int i;
	int	params[2];

	i = 0;
	while ((ft_isalnum(str[i]) || str[i] == '_' || str[i] == '=') && i < len)
	{
		if (stresc("=", str, i) && str[0] != '=')
		{
			cmd->env = NULL;
			cmd->assign = 1;
			params[0] = i;
			params[1] = len;
			if (store_localvar(str, params, sh_state, cmd) == 1)
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
