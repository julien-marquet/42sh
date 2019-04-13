/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_param.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 19:23:51 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"

static int		expand_param_insert(t_cmd *cmd, char *new, size_t i, size_t end)
{
	char	*tmp;
	size_t	len;

	if (new)
	{
		len = ft_strlen(new);
		if (!(tmp = strinsert(cmd->str, new, i - 1, end)))
		{
			ft_strdel(&new);
			return (1);
		}
		cmd->str = tmp;
		ft_strdel(&new);
		return (len);
	}
	return (1);
}

static int		expand_check_sub(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd(SH_NAME, 2);
			ft_putstr_fd(": $", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": bad substitution", 2);
			ft_strdel(&str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		expand_param(t_cmd *cmd, size_t i, size_t end,
t_sh_state *sh_state)
{
	char	*new;
	char	*tmp;

	if (cmd->str[i] == '{')
		tmp = ft_strndup(cmd->str + i + 1, end - i - 2);
	else
		tmp = ft_strndup(cmd->str + i, end - i);
	ft_memset(cmd->str + i, ' ', end - i);
	if (!tmp)
		return (1);
	if (expand_check_sub(tmp))
		return (1);
	if (!(new = get_stored(sh_state->internal_storage, tmp)))
	{
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (expand_param_insert(cmd, new, i, end));
}

static size_t	parse_param_cond(t_cmd *cmd, t_sh_state *sh_state,
size_t i, size_t end)
{
	if (stresc("{", cmd->str, i))
	{
		end = i + 1;
		while (cmd->str && !stresc("}", cmd->str, i))
			i++;
	}
	else
	{
		end = i + 1;
		while (cmd->str[end] && !stresc(";|<>&$'\" \n", cmd->str, end))
			end++;
	}
	return (expand_param(cmd, i + 1, end, sh_state));
}

void			parse_param(t_cmd *cmd, t_sh_state *sh_state)
{
	size_t	i;
	size_t	end;
	size_t	ret;

	i = 0;
	end = 0;
	while (cmd->str[i])
	{
		while (cmd->str[i] && is_quoted(cmd->str, i) == 1)
			i++;
		if (cmd->str[i] && stresc("$", cmd->str, i))
		{
			cmd->str[i] = ' ';
			ret = parse_param_cond(cmd, sh_state, i, end);
			i += ret;
		}
		else
			cmd->str[i] ? i++ : 0;
	}
}
