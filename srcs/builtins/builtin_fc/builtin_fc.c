/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 10:24:26 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"
/*
void	print_test(t_list *hist, t_list *end, t_fc_infos *fc_infos)
{
	while (hist && (end == NULL || hist != end->next))
	{
		//num--;
		// if (flag_n == 0)
			// ft_putnbr_fd(len--, 1);
		ft_putchar_fd('\t', 1);
		ft_putstr_fd(hist->content, 1);
		ft_putchar_fd('\n', 1);
		hist = hist->next;
	}
}*/

static char		*tmp_file(t_sh_state *sh_state)
{
	char	*tmp;

	if ((tmp = get_stored(sh_state->internal_storage, "TMPDIR")) == NULL)
		tmp = ft_strdup("/var/tmp/");
	return (ft_construct_str(2, tmp, "/42sh-fc"));

}

static int		init_exec(t_sh_state *sh_state, t_cmd *cmd, t_fc_infos *fc_infos)
{
	if (!(cmd->arg = ft_memalloc(sizeof(char*) * 3)))
		return (-1);
	cmd->arg[0] = ft_strdup(fc_infos->editor ? fc_infos->editor : EDITOR);
	cmd->arg[1] = tmp_file(sh_state);
	if (cmd->arg[0] == NULL || cmd->arg[1] == NULL)
		return (-1);
	return (0);
}

int				fc_exec(t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	char	*job;
	t_cmd	*cmd;
	int		i;
	int		fd;

	if (!(cmd = ft_memalloc(sizeof(t_cmd))))
		return (-1);
	if (init_exec(sh_state, cmd, fc_infos) == -1)
		return (-1);
	if (!(job = ft_construct_str(3, cmd->arg[0], " ", cmd->arg[1])))
		return (-1);
	if (!(fd = open(cmd->arg[1], O_CREAT | O_RDWR, CHEV_PERM)))
		return (-1);
	if (fc_print(sh_state->history, fc_infos, fd))
		return (-1);
	i = exec_cmd_list(sh_state, cmd, job, NULL);
	close(fd);
	unlink(tmp_file(sh_state));
	if (i == -1 || sh_state->status != 0)
		return (-1);
	return (0);
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
	if (!sh_state->history->next)
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
	add_origin(&context->origin, "fc");
	fc_infos = ft_memalloc(sizeof(t_fc_infos));
	if (!(fc_infos->opts = ft_strnew(5)))
		return (-1);
	//fc_infos->first = -1;
	//fc_infos->last = -1;
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
