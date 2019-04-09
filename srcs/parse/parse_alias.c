/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_alias.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:03:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 22:19:19 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/alias.h"
/*
static char	*getfirst_word()
{
	int i;
	int start;

	(void)cmd;
	i = 0;
	char *name = ft_strdup("NAME");
	char *value = ft_strdup("value");
	while (cmd->str[i])
	{
		while (cmd->str[i] && ft_isspace(cmd->str[i]))
			i++;
		start = i;
		while (cmd->str[i] && !stresc(" ", cmd->str, i))
		{
			i++;
		}
		dprintf(2, "LOCAL '%.*s'\n", i - start,cmd->str + start);
		while (cmd->str[i] && !stresc(";|&", cmd->str, i))
		{
			i++;
		}
		cmd->str[i] ? i++ : 0;
	}
	add_entry_storage(&sh_state->internal_storage, name, value, 0);
	return (0);
}*/

char		*parse_alias(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
		{
			i++;
		}
		str[i] ? i++ : 0;
	}
}