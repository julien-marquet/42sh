/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/19 22:35:37 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 15:47:02 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

static void		parse_cmdpush(t_cmd **cmd, t_cmd *new)
{
	t_cmd *tmp;

	tmp = *cmd;
	if (cmd != NULL && new != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int		parse_charhandle(char *str, int i, char chr)
{
	if (chr == '&' || chr == '|')
	{
		while (str[i] && str[i] == chr)
			i++;
		return (i);
	}
	return (i + 1);
}

static int		parse_emptycmd(char *str)
{
	char	*tmp;
	int		len;

	tmp = ft_strtrim(str);
	len = ft_strlen(tmp);
	ft_strdel(&tmp);
	return (len == 0);
}

t_cmd			*parse_cmdcreate(char *str, int len, t_cmd *cmd, int type)
{
	t_cmd	*new;

	if (!(new = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	if (parse_emptycmd(str))
		return (cmd);
	new->str = ft_strndup(str, len);
	new->type = type;
	if (!cmd)
		return (new);
	parse_cmdpush(&cmd, new);
	return (cmd);
}

int				parse_tokenize(char *str, t_cmd **cmd)
{
	char	*chr;
	int		len;

	len = 0;
	chr = 0;
	while (str[len] && !(chr = stresc(";|&", str, len)))
	{
		while (str[len] && is_quoted(str, len))
			len++;
		str[len] ? len++ : 0;
	}
	if (chr)
		len = parse_charhandle(str, len, *chr);
	*cmd = parse_cmdcreate(str, len, *cmd, (chr ? *chr : 0));
	return (len);
}
