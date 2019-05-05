/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_exec.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 16:22:42 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:20:33 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static int		init_exec(t_sh_state *sh_state, char *tmp, t_cmd *cmd,
t_fc_infos *fc_infos)
{
	char	*tmp_cmd;

	if (fc_infos->editor)
	{
		if (!(tmp_cmd = ft_construct_str(3, fc_infos->editor, " ", tmp)))
			return (-1);
		if (!(cmd->arg = parse_strsplit(tmp_cmd, ft_strlen(tmp_cmd))))
			return (-1);
		ft_strdel(&tmp_cmd);
	}
	else
	{
		if (!(cmd->arg = ft_memalloc(sizeof(char*) * 3)))
			return (-1);
		if (!(cmd->arg[0] = ft_strdup(EDITOR)))
			return (-1);
		if (!(cmd->arg[1] = tmp_file(sh_state)))
			return (-1);
	}
	return (0);
}

static int		fc_exec_cmd(t_sh_state *sh_state, t_list *list)
{
	t_list	*tmp;
	int		ret;

	tmp = list;
	while (list)
	{
		ft_putendl(list->content);
		if (add_to_history_list(&(sh_state->history), list->content, ft_strlen(list->content) + 1) == NULL)
		{
			free_list(tmp);
			return (-1);
		}
		ret = parse_exec(list->content, sh_state, sh_state->input_data);
		list = list->next;
	}
	free_list(tmp);
	return (ret);
}

int				fc_tmpfile_edit(t_sh_state *sh_state, char *tmp_file)
{
	t_dyn_buf	*dyn;
	char 		buf[READ_SIZE + 1];
	int			r;
	int			fd;
	t_list		*args;

	if ((dyn = init_dyn_buf()) == NULL)
		return (-1);
	if ((fd = open(tmp_file, O_RDONLY)) == -1)
		return (-1);
	while ((r = read(fd, buf, READ_SIZE)) != 0)
	{
		buf[r] = 0;
		if (insert_dyn_buf(buf, dyn, dyn->len) != 0)
			return (-1);
	}
	if (!(args = hist_str2list(dyn->buf)))
		return (0);
	free_dyn_buf(&dyn);
	if (fc_exec_cmd(sh_state, args) == -1)
		return (-1);
	return (0);
}

static int		fc_editor_exec(char *tmp, t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	t_cmd	*cmd;
	char	*job;
	int		fd;
	int		i;

	if (!(cmd = ft_memalloc(sizeof(t_cmd))))
		return (-1);
	if (init_exec(sh_state, tmp, cmd, fc_infos) == -1)
		return (-1);
	if ((fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, HIST_PERM)) == -1)
		return (-1);
	if (fc_print(sh_state->history, fc_infos, fd))
		return (-1);
	if (!(job = ft_strdup("fc -e")))
		return (-1);
	i = exec_cmd_list(sh_state, cmd, job, NULL);
	ft_strdel(&job);
	close(fd);
	return (0);
}

int				fc_exec(t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	int		ret;
	char	*tmp;
	t_list	*old;

	if (!(tmp = tmp_file(sh_state)))
		return (-1);
	if ((ret = fc_editor_exec(tmp, sh_state, fc_infos)) == -1)
		return (-1);
	old = sh_state->history;
	sh_state->history = sh_state->history->next;
	free(old->content);
	free(old);
	if (sh_state->status == 0)
		fc_tmpfile_edit(sh_state, tmp);
	unlink(tmp);
	ft_strdel(&tmp);
	if (sh_state->status != 0)
		return (-1);
	return (0);
}