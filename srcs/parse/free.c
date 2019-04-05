/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 16:00:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 14:59:34 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

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
	ft_strdel(&cmd->red);
	free_arg(cmd->arg);
	free_file(cmd->out);
	free_file(cmd->in);
	free(cmd);
	return (next);
}
