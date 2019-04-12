/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grp.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 21:18:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 20:38:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc_grp.h"
#include "term_state.h"
#include "errno.h"
#include "signal.h"
t_proc_grp	*find_by_gpid(int pgid)
{
	t_list	*tmp;
	t_jobs	*jobs;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if (((t_proc_grp *)tmp->content)->pgid == pgid)
			return ((t_proc_grp *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_proc_grp	*find_proc_grp_by_name(const char *name, int *nres)
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;

	*nres = 0;
	proc_grp = NULL;
	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_proc_grp *)tmp->content)->name, name) == 0)
		{
			(*nres)++;
			proc_grp = (t_proc_grp *)tmp->content;
		}
		tmp = tmp->next;
	}
	return (*nres > 1 ? NULL : proc_grp);
}

t_proc_grp	*get_first_proc_grp()
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;

	proc_grp = NULL;
	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	if (tmp != NULL)
		proc_grp = (t_proc_grp *)tmp->content;
	return (proc_grp);
}


t_proc_grp	*new_proc_grp(int pgid, const char *name)
{
	t_proc_grp	*proc_grp;

	if ((proc_grp = ft_memalloc(sizeof(t_proc_grp))) == NULL)
		return (NULL);
	proc_grp->pgid = pgid;
	proc_grp->name = ft_strdup(name);
	return (proc_grp);
}

int			add_proc_grp(t_proc_grp *proc_grp)
{
	t_list	*node;
	t_jobs	*jobs;

	if (proc_grp != NULL)
	{
		if ((node = ft_memalloc(sizeof(t_list))) == NULL)
			return (1);
		jobs = jobs_super_get();
		node->content_size = sizeof(t_proc_grp);
		node->content = proc_grp;
		node->next = NULL;
		ft_lstappend(&jobs->proc_grps, node);
		return (0);
	}
	else
		return (1);
}

t_proc *get_last_proc(t_proc_grp *proc_grp)
{
	t_list	*tmp;

	tmp = proc_grp->procs;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp == NULL ? NULL : (t_proc *)tmp->content);
}

int			send_to_fg(t_sh_state *sh_state, t_proc_grp *proc_grp)
{
	int		stat_loc;
	t_proc	*last_proc;

	stat_loc = 0;
	last_proc = get_last_proc(proc_grp);
	set_term_state_backup(sh_state);
	tcsetpgrp(0, proc_grp->pgid);
	waitpid(last_proc->pid, &stat_loc, WUNTRACED);
	tcsetpgrp(0, sh_state->shell_pid);
	set_term_state(sh_state);
	return (0);
}
