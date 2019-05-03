/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_exec.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 16:22:42 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 02:04:40 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static int		init_exec(t_sh_state *sh_state, t_cmd *cmd, t_fc_infos *fc_infos)
{
	t_arg	*args;
	int		len;
	int		i;

	i = 0;
	if (fc_infos->editor)
	{
		if (!(args = parse_split_create(fc_infos->editor, ft_strlen(fc_infos->editor))))
			return (-1);
		len = parse_split_count(args);
		if (!(cmd->arg = ft_memalloc(sizeof(char*) * (len + 2))))
			return (-1);
		while (args)
		{
			cmd->arg[i++] = args->arg;
			args = args->next;
		}
		if (!(cmd->arg[i] = tmp_file(sh_state)))
			return (-1);
	}
	else
	{
		if (!(cmd->arg = ft_memalloc(sizeof(char*) * 3)))
			return (-1);
		if (!(cmd->arg[0] = ft_strdup(fc_infos->editor ? fc_infos->editor : EDITOR)))
			return (-1);
		if (!(cmd->arg[1] = tmp_file(sh_state)))
			return (-1);
	}
	return (0);
}

static int		fc_exec_cmd(t_sh_state *sh_state, t_list *cmd)
{
	t_list	*tmp;
	int		ret;

	tmp = cmd;
	while (cmd)
	{
		dprintf(1, "%s\n", cmd->content);
		dprintf(1, "EXEC:\n");
		ret = parse_exec(cmd->content, sh_state, sh_state->input_data);
		dprintf(1, "ret = %i\n", ret);
		cmd = cmd->next;
	}
	//TODO FREE CMD
	return (ret);
}

int				fc_file_exec(t_sh_state *sh_state, char *tmp_file)
{
	t_dyn_buf	*dyn;
	char 		*buf;
	int			r;
	int			fd;
	t_list		*cmd;

	if (!(buf = ft_strnew(READ_SIZE + 1)))
		return (-1);
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
	cmd = hist_str2list(dyn->buf);
	fc_exec_cmd(sh_state, cmd);
	free_dyn_buf(&dyn);
	return (0);
}

static int		fc_editor_exec(char *tmp, t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	t_cmd	*cmd;
	char	*job;
	int		fd;
	int		i;

	if (!(cmd = ft_memalloc(sizeof(t_cmd))))
		return (1);
	if (init_exec(sh_state, cmd, fc_infos) == -1)
		return (1);
	if ((fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, HIST_PERM)) == -1)
		return (1);
	if (fc_print(sh_state->history, fc_infos, fd))
		return (1);
	job = ft_strdup("fc -e");
	i = exec_cmd_list(sh_state, cmd, job, NULL);
	ft_strdel(&job);
	close(fd);
	return (0);
}

int				fc_exec(t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	char	*tmp;

	if (!(tmp = tmp_file(sh_state)))
		return (-1);
	if (fc_editor_exec(tmp, sh_state, fc_infos))
		return (-1);
	fc_file_exec(sh_state, tmp);
	unlink(tmp);
	ft_strdel(&tmp);
	if (sh_state->status != 0)
		return (-1);
	return (fc_exit(fc_infos, 0));
}