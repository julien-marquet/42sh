/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 16:53:52 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

// SH_GETENV HANDLE ERROR 'bad substitution' ON NOT ALPHANUM- CHAR

static int	expand_param(t_cmd *cmd, t_term *term, size_t i, size_t end)
{
	char	*new;
	char	*tmp;

	(void)term;
	if (cmd->str[i] == '{')
		tmp = ft_strndup(cmd->str + i + 1, end - i - 2);
	else
		tmp = ft_strndup(cmd->str + i, end - i);
	if (!tmp)
		return (1);
	new = sh_getenv(tmp, term);
	new = "";
	ft_strdel(&tmp);
	if (new)
	{
		if (!(tmp = strinsert(cmd->str, new, i - 1, end)))
			return (1);
		cmd->str = tmp;
		return (ft_strlen(new));
	}
	return (1);
}

static int	parse_param_cond(t_cmd *cmd, t_term *term, size_t i, size_t end)
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
		while (cmd->str[end] && !stresc(";|<>&$ \n", cmd->str, end))
			end++;
	}
	return (expand_param(cmd, term, i + 1, end));
}

static void	parse_param(t_cmd *cmd, t_term *term)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while (cmd->str[i])
	{
		while (cmd->str[i] && is_quoted(cmd->str, i) == 1)
			i++;
		if (cmd->str[i] && stresc("$", cmd->str, i))
			i += parse_param_cond(cmd, term, i, end);
		else
			cmd->str[i] ? i++ : 0;
	}
}

void		parse_expansion(t_cmd *cmd, t_term *term)
{
	parse_tilde(cmd, term);
	parse_param(cmd, term);
}
