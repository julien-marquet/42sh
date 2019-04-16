/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 16:00:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 19:57:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

static void		free_file(t_file *file)
{
	t_file *tmp;

	while (file)
	{
		ft_strdel(&file->file);
		ft_strdel(&file->here);
		free(file->type);
		tmp = file;
		file = file->next;
		free(tmp);
	}
	free(file);
}

static void		free_arg(char **arg)
{
	int i;

	i = 0;
	if (arg == NULL)
		return ;
	while (arg[i])
	{
		ft_strdel(&arg[i]);
		i++;
	}
	free(arg);
}

t_cmd			*parse_nextfree(t_cmd *cmd)
{
	t_cmd	*next;

	next = cmd->next;
	ft_strdel(&cmd->str);
	ft_strdel(&cmd->red);
	free_arg(cmd->arg);
	free_file(cmd->out);
	free_file(cmd->in);
	free(cmd);
	return (next);
}

void	free_executed_cmds(t_cmd *cmd_list, t_cmd *remaining)
{
	t_cmd	*prev;

	while (cmd_list != NULL && cmd_list != remaining)
	{
		dprintf(2, "freeing %s\n", cmd_list->str);
		ft_strdel(&cmd_list->str);
		ft_strdel(&cmd_list->red);
		free_arg(cmd_list->arg);
		free_file(cmd_list->out);
		free_file(cmd_list->in);
		prev = cmd_list;
		cmd_list = cmd_list->next;
		free(prev);
	}
}
