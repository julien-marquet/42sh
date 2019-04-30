/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 23:52:44 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

int				fc_exit(t_fc_infos *fc_infos, int ret)
{
	ft_strdel(&fc_infos->opts);
	ft_strdel(&fc_infos->editor);
	free(fc_infos);
	return (ret);
}

static char		*tmp_file(t_sh_state *sh_state)
{
	char	*tmp;
	char	*ret;

	if ((tmp = get_stored(sh_state->internal_storage, "TMPDIR")) == NULL)
		if (!(tmp = ft_strdup("/var/tmp/")))
			return (NULL);
	ret = ft_construct_str(2, tmp, "/42sh-fc");
	free(tmp);
	return (ret);

}

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
			dprintf(1, "%i = '%s'\n", i, args->arg);
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

t_list	*add_to_list(t_list *args, char *str, int start, int i)
{
	char	*tmp;
	t_list	*new;

	if (!(tmp = ft_strndup(str + start, i - start)))
		return (NULL);
	dprintf(1, "TMP = |%s| %zu\n", tmp, ft_strlen(tmp));
	if (!(new = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
		return (NULL);
	if (args == NULL)
		return (new);
	ft_lstadd(&args, new);
	return (args);
}

int		splitchar(char *str, int i, char *split)
{
	while (i > 0 && ft_isspace(str[i]))
		i--;
	dprintf(1, "SPLIT = %c = '%s'\n", str[i], stresc(split, str, i));
	return (stresc(split, str, i) != NULL);
}

t_list	*split(char *str)
{
	t_list	*args;
	int		start;
	int		i;

	i = 0;
	args = NULL;
	while (str[i])
	{
		start = i;
		while (str[i] && is_quoted(str, i))
			i++;
		while (str[i] && splitchar(str, i, "|&\\"))
			i++;
		if (str[i] == '\n')
			args = add_to_list(args, str, start, i);
		str[i] ? i++ : 0;
	}
	return (args);
}

int				fc_file_exec(t_sh_state *sh_state, char *tmp_file)
{
	(void)sh_state;
	t_dyn_buf	*dyn;
	char 		*buf;
	int			r;
	int			fd;
	t_list		*args;

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
	dprintf(1, "DYN = %s", dyn->buf);		
	args = split(dyn->buf);
	while (args)
	{
		dprintf(1, "%s\n", args->content);
		args = args->next;
	}
	//parse_exec(dyn->buf, sh_state, sh_state->input_data);
	return (0);
}

int				fc_exec(t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	char	*tmp;
	char	*job;
	t_cmd	*cmd;
	int		i;
	int		fd;

	if (!(cmd = ft_memalloc(sizeof(t_cmd))))
		return (-1);
	if (init_exec(sh_state, cmd, fc_infos) == -1)
		return (-1);
	if (!(tmp = tmp_file(sh_state)))
		return (-1);
	if ((fd = open(tmp, O_CREAT | O_WRONLY, HIST_PERM)) == -1)
		return (-1);
	if (fc_print(sh_state->history, fc_infos, fd))
		return (-1);
	job = ft_strdup("fc -e");
	i = exec_cmd_list(sh_state, cmd, job, NULL);
	ft_strdel(&job);
	close(fd);
	fc_file_exec(sh_state, tmp);
	unlink(tmp);
	ft_strdel(&tmp);
	if (i == -1 || sh_state->status != 0)
		return (-1);
	return (fc_exit(fc_infos, 0));
}


static int		fc_dispatch(t_sh_state *sh_state, const char **av, t_fc_infos *fc_infos, t_builtin_context *context)
{
	int i;

	i = 0;
	if (av[0])
	{
		fc_infos->first = get_history_index_rev(sh_state->history, fc_get_hist_num(sh_state, av[0]));
		if (av[1])
		{
			if (fc_get_hist_num(sh_state, av[0]) > fc_get_hist_num(sh_state, av[1]))
			{
				add_valid(fc_infos, 'r');
				fc_infos->last = fc_infos->first;
				fc_infos->first = get_history_index_rev(sh_state->history, fc_get_hist_num(sh_state, av[1]));
			}
			else
				fc_infos->last = get_history_index_rev(sh_state->history, fc_get_hist_num(sh_state, av[1]));
		}
	}
	// TODO CHECK IF MORE THAN HISTSIZE
	if (!sh_state->history || !sh_state->history->next)
	{
		free(fc_infos);
		print_error(context->origin, "history specification out of range", 2);
		return (1);
	}
	if (fc_infos->opts != NULL && ft_strchr(fc_infos->opts, 'l') != NULL)
		return (fc_print(sh_state->history, fc_infos, 1));
	else
		return (fc_exec(sh_state, fc_infos));
	return (0);
}

int				builtin_fc(t_sh_state *sh_state, int ac, const char **av, t_builtin_context *context)
{
	t_fc_infos	*fc_infos;
	int			args_i;

	(void)ac;
	// FIX DE MERDE
	sh_state->history = sh_state->input_data->history_list;
	add_origin(&context->origin, "fc");
	fc_infos = ft_memalloc(sizeof(t_fc_infos));
	if (!(fc_infos->opts = ft_strnew(5)))
		return (-1);
	if ((args_i = fc_options(av, fc_infos, context)) == -1)
		return (1);
	else if (args_i == 0)
	{
		print_error(context->origin, "usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]", 2);
		return (1);
	}
	else
		return (fc_dispatch(sh_state, av + args_i, fc_infos, context));
}
