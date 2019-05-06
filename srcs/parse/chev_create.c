/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chev_create.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 16:44:52 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 10:00:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"
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

static int		parse_exit(char *file, t_file *new, int *type, int ret)
{
	ft_strdel(&file);
	free(new);
	free(type);
	return (ret);
}

int				parse_chevcreate(char *file, t_cmd *cmd, int *type,
void *sh_info[2])
{
	t_file	*new;

	if (!(new = ft_memalloc(sizeof(t_file))))
		exit_sh(sh_info[0], sh_info[1]);
	if (type[C_TYPE] == '<' && type[C_LEN] == 2)
	{
		reset_dyn_buf(((t_input_data*)sh_info[1])->active_buf);
		if (handle_input(sh_info[0], ((t_input_data*)sh_info[1]), file))
			exit_sh(sh_info[0], sh_info[1]);
		if (((t_input_data*)sh_info[1])->sig_call == 1)
			return (parse_exit(file, new, type, 1));
		if (!(new->here = get_expand_str(
			((t_input_data*)sh_info[1])->active_buf->buf, sh_info[0])))
			new->here = ft_strdup("");
		ft_strdel(&file);
	}
	else
		new->file = file;
	new->type = type;
	if (type[C_OUT] == -2 || type[C_TYPE] == '>')
		!cmd->out ? cmd->out = new : parse_chevpush(&cmd->out, new);
	else if (type[C_TYPE] == '<')
		!cmd->in ? cmd->in = new : parse_chevpush(&cmd->in, new);
	return (0);
}
