/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_param.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 18:12:48 by mmoya       ###    #+. /#+    ###.fr     */
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

static int		expand_check_sub(char *str, int err)
{
	int i;

	i = 0;
	while (str[i] && err == 0)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			err = 1;
		i++;
	}
	if (err != 0)
	{
		ft_putstr_fd(SH_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": bad substitution", 2);
		if (err != -1)
			ft_strdel(&str);
		return (-1);
	}
	return (0);
}

static int		expand_param(t_cmd *cmd, size_t i, size_t end,
t_sh_state *sh_state)
{
	char	*new;
	char	*tmp;

	if (cmd->str[i] == '{' && cmd->str[end - 1] != '}')
		return (expand_check_sub(cmd->str + i, -1));
	if (cmd->str[i] == '{')
		tmp = ft_strndup(cmd->str + i + 1, end - i - 2);
	else
		tmp = ft_strndup(cmd->str + i, end - i);
	ft_memset(cmd->str + i, ' ', end - i);
	if (!tmp)
		return (1);
	if (expand_check_sub(tmp, 0) == -1)
		return (-1);
	if (!(new = get_stored(sh_state->internal_storage, tmp)))
	{
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (expand_param_insert(cmd, new, i, end));
}

int				parse_param(t_cmd *cmd, t_sh_state *sh_state)
{
	size_t	i;
	size_t	end;
	int		ret;

	i = 0;
	while (cmd->str[i])
	{
		while (cmd->str[i] && is_quoted(cmd->str, i) == 1)
			i++;
		if (cmd->str[i] && stresc("$", cmd->str, i))
		{
			cmd->str[i] = ' ';
			end = i + 1;
			while ((cmd->str[end] && ft_isalnum(cmd->str[end]) &&
			cmd->str[end] != '_') || (cmd->str[end] &&
			cmd->str[i + 1] == '{' && cmd->str[end - 1] != '}'))
				end++;
			if (!(ret = expand_param(cmd, i + 1, end, sh_state)) || ret < 0)
				return (1);
			i += ret;
		}
		else
			cmd->str[i] ? i++ : 0;
	}
	return (0);
}
