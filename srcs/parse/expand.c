/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 15:09:01 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

static int	expand_param(t_cmd *cmd, t_term *term, size_t i, size_t end)
{
	char	*new;
	char	*tmp;

	(void)term;
	new = sh_getenvn(cmd->str + i, term->env, end - i);
	if (new)
	{
		if (!(tmp = strinsert(cmd->str, new, i - 1, end)))
			return (1);
		cmd->str = tmp;
		return (ft_strlen(new));
	}
	return (1);
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
		{
			end = i + 1;
			while (cmd->str[end] && !stresc(";|<>&$ ", cmd->str, end))
				end++;
			i += expand_param(cmd, term, i + 1, end);
		}
		else
			cmd->str[i] ? i++ : 0;
	}
}

void		parse_expansion(t_cmd *cmd, t_term *term)
{
	parse_tilde(cmd, term);
	parse_param(cmd, term);
}
