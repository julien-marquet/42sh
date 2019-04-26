/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 16:00:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 01:01:44 by jmarquet    ###    #+. /#+    ###.fr     */
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

void	free_executed_cmds(t_cmd *acmd, t_cmd *remaining, t_cmd *cmd)
{
	t_cmd	*prev;
	t_cmd	*end;

	if (remaining != NULL)
		end = remaining;
	else
		end = cmd;
	while (acmd != NULL && acmd != end)
	{
		ft_strdel(&acmd->str);
		ft_strdel(&acmd->red);
		free_arg(acmd->arg);
		free_file(acmd->out);
		free_file(acmd->in);
		prev = acmd;
		acmd = acmd->next;
		free(prev);
	}
}

void	free_cmds(t_cmd *acmd)
{
	t_cmd	*prev;

	while (acmd != NULL)
	{
		ft_strdel(&acmd->str);
		ft_strdel(&acmd->red);
		free_arg(acmd->arg);
		free_file(acmd->out);
		free_file(acmd->in);
		prev = acmd;
		acmd = acmd->next;
		free(prev);
	}
}
