/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_param.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 00:34:18 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"

static char		*expand_bytype(t_sh_state *sh_state, char *str)
{
	if (param_check_isspecial(str))
		return (get_special_parameter(sh_state, str));
	else
		return (get_stored(sh_state->internal_storage, str));
}

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

static int		expand_param(t_cmd *cmd, size_t i, size_t end,
t_sh_state *sh_state)
{
	char	*new;
	char	*tmp;

	if (cmd->str[i] == '{' && cmd->str[end - 1] != '}')
		return (expand_error_handler(0, NULL));
	if (cmd->str[i] == '{')
		tmp = ft_strndup(cmd->str + i + 1, end - i - 2);
	else
		tmp = ft_strndup(cmd->str + i, end - i);
	ft_memset(cmd->str + i, ' ', end - i);
	if (!tmp)
		return (1);
	if (expand_error_handler(1, tmp) == -1)
		return (-1);
	dprintf(1, "%s\n", get_special_parameter(sh_state, tmp));
	if (!(new = expand_bytype(sh_state, tmp)))
	{
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (expand_param_insert(cmd, new, i, end));
}

static int		param_len(char *str, int i, int type)
{
	if (type == '?' ||
	type == '$' ||
	type == '-' ||
	type == '!' ||
	type == '0')
		return (i + 1);
	if (type == '{')
	{
		while (str[i] && str[i - 1] != '}')
			i++;
	}
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	return (i);
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
			end = param_len(cmd->str, i + 1, cmd->str[i + 1]);
			ret = expand_param(cmd, i + 1, end, sh_state);
			if (ret < 0)
				return (1);
			i += ret;
		}
		else
			cmd->str[i] ? i++ : 0;
	}
	return (0);
}
