/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_envutils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 06:21:00 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 06:21:00 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_env.h"

t_proc_grp	*register_special_job(int pid, const char **av)
{
	t_proc_grp	*proc_grp;
	t_proc		*proc;
	char		*job_name;

	if ((proc = new_proc(pid, av[0], 1)) == NULL)
		return (NULL);
	job_name = create_job_name_from_arr(av);
	if ((proc_grp = new_proc_grp(0, job_name)) == NULL)
	{
		ft_strdel(&proc->name);
		free(proc);
		ft_strdel(&job_name);
		return (NULL);
	}
	ft_strdel(&job_name);
	proc_grp->pgid = pid;
	add_proc(proc, proc_grp);
	add_proc_grp(proc_grp);
	return (proc_grp);
}

int			send_special_to_fg(t_sh_state *sh_state, t_proc_grp *proc_grp)
{
	set_term_state_backup(sh_state);
	tcsetpgrp(0, proc_grp->pgid);
	wake_all_processes(proc_grp);
	wait_for_grp(sh_state, proc_grp);
	tcsetpgrp(0, getpid());
	set_term_state(sh_state);
	return (0);
}

int			count_pairs(const char **av, int *start, char *origin)
{
	int		cpt;
	int		i;
	char	*tmp;
	char	*err;

	cpt = 0;
	while (av[*start])
	{
		if ((i = ft_strstr_i(av[*start], "=")) == -1)
			break ;
		if (is_valid_var_name((tmp = ft_strndup(av[*start], i))) == 0)
		{
			err = ft_construct_str(2, tmp, ": invalid variable name");
			print_error(origin, err, 2);
			ft_strdel(&err);
			ft_strdel(&tmp);
			return (-1);
		}
		ft_strdel(&tmp);
		cpt++;
		*start += 1;
	}
	return (cpt);
}

char		*find_utility(t_sh_state *sh_state, const char **av,
t_builtin_context *context)
{
	int				res;
	int				err;
	char			*path;

	res = 0;
	path = NULL;
	if (av && is_absolute_path(av[0]))
	{
		if ((res = test_bin(av[0])) == 0)
			path = ft_strdup(av[0]);
		else if (res != -1)
			res--;
	}
	else
	{
		if (av[0] == NULL)
			return (NULL);
		if ((path = get_bin_path(av, &sh_state->hash_table,
	sh_state->internal_storage, &err)) == NULL)
			res = err;
	}
	if (path == NULL)
		handle_path_exec_error(context->origin, av[0], res);
	return (path);
}

void		env_error(char *origin, int *res)
{
	*res = 1;
	print_error(origin,
"usage: env [-i] [name=value]... [utility [argument...]]", 2);
}
