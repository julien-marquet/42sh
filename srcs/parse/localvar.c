/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   localvar.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:43:22 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 23:33:49 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/localvar.h"

static	int	store_localvar(char *str, int len, t_sh_state *sh_state)
{
	int i;
	int	valid;

	i = 0;
	valid = 0;
	while (str[i] && i < len)
	{
		ft_putchar_fd(str[i], 2);
		if (stresc("=", str, i))
			valid++;
		i++;
	}
	dprintf(2, "\n");
	add_entry_storage(&sh_state->internal_storage, "TEST", NULL, 0);
	return (valid);
}

int			parse_localvar(t_cmd *cmd, t_sh_state *sh_state)
{
	int i;
	int start;

	i = 0;
	while (cmd->str[i])
	{
		while (cmd->str[i] && ft_isspace(cmd->str[i]))
			i++;
		start = i;
		while (cmd->str[i] && !ft_isspace(cmd->str[i]))
		{
			while (cmd->str[i] && is_quoted(cmd->str, i))
				i++;
			cmd->str[i] ? i++ : 0;
		}
		if (store_localvar(cmd->str + start, i - start, sh_state) == 1)
		{
			while (cmd->str[i] && !ft_isspace(cmd->str[i]))
			{
				dprintf(2, "%c\n", cmd->str[i]);
				i++;
			}
			continue ;
		}


		//dprintf(2, "LOCAL '%.*s'\n", i - start,cmd->str + start);
		while (cmd->str[i] && !stresc(";|&", cmd->str, i))
			i++;
		cmd->str[i] ? i++ : 0;
	}
	return (0);
}