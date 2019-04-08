/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chev_create.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 16:44:52 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 16:47:24 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"
#include "editing/input/input_main_process.h"

static void		parse_chevpush(t_file **file, t_file *new)
{
	t_file *tmp;

	tmp = *file;
	if (file != NULL && new != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
** TODO: Expand heredoc result
*/

t_cmd			*parse_chevcreate(char *file, t_cmd *cmd, int *type, t_sh_state *sh_state, t_input_data *input_data)
{
	t_file	*new;

	if (!(new = ft_memalloc(sizeof(t_file))))
		return (NULL);
	if (type[C_TYPE] == '<' && type[C_LEN] == 2)
	{
		reset_dyn_buf(input_data->active_buf);
		handle_input(sh_state, input_data, file);
		new->here = ft_strdup(input_data->active_buf->buf);
		// new->here = ft_strndup(input_data->active_buf->buf,
		// ft_strlen(input_data->active_buf->buf) - ft_strlen(file));
		ft_strdel(&file);
	}
	else
		new->file = file;
	new->type = type;
	if (type[C_TYPE] == '<')
		!cmd->in ? cmd->in = new : parse_chevpush(&cmd->in, new);
	else if (type[C_TYPE] == '>')
		!cmd->out ? cmd->out = new : parse_chevpush(&cmd->out, new);
	return (cmd);
}
