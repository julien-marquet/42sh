/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   localvar.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:43:22 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 15:44:42 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/localvar.h"

static void	forward(char *str, size_t *i)
{
	if (str[*i] == '"' && stresc(str, str, *i) != NULL)
	{
		*i += 1;
		while (str[*i] != '"')
			*i += 1;
	}
	if (str[*i] == '\'' && stresc(str, str, *i) != NULL)
	{
		*i += 1;
		while (str[*i] != '\'')
			*i += 1;
	}
}

static int	is_var(char *str)
{
	char	**arr;

	if ((arr = ft_strsplit(str, '=')) == NULL)
		return (-1);
	if (*arr == NULL || *(arr + 1) == NULL)
	{
		ft_freetab(&arr);
		return (0);
	}
	if (ft_strchr(*arr, '"') == NULL && ft_strchr(*arr, '\'') == NULL)
	{
		ft_freetab(&arr);
		return (1);
	}
	ft_freetab(&arr);
	return (0);
}

static int	is_tmp(char *str)
{
	size_t	i;
	int		ret;
	size_t	is_tmp;

	i = 0;
	is_tmp = 0;
	while (str[i])
	{
		forward(str, &i);
		if (is_stopping(str[i]) && str[i] != ' ' &&
	(i == 0 || (i > 0 && stresc(str, str, i) != NULL)))
			return (is_tmp);
		if (str[i] != ' ' && str[i] != '\n')
		{
			if ((ret = is_var(&(str[i]))) == -1)
				return (-1);
			return (!ret);
		}
		i += 1;
	}
	return (is_tmp);
}

static void	add_tmp_entry(t_cmd *cmd, char *name, char *value)
{
	t_list				*node;
	t_internal_storage	entry;

	if (is_valid_var_name(name) == 0)
		return ;
	if (fill_entry(&entry, name, value, ft_strlen(name) + ft_strlen(value) + 1) == 1)
		return ;
	if ((node = ft_lstnew(&entry, sizeof(t_internal_storage))) == NULL)
		return ;
	ft_lstprepend(&(cmd->env), node);
}

static int	store_localvar(char *str, int i, int len, t_sh_state *sh_state, t_cmd *cmd)
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
	{
		if (is_tmp(str + len))
			add_tmp_entry(cmd, name, value);
		else
			add_entry_storage(sh_state, name, value, 0);
	}
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
		if (stresc("=", str, i) && str[0] != '=')
		{
			cmd->env = NULL;
			cmd->assign = 1;
			if (store_localvar(str, i, len, sh_state, cmd) == 1)
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
