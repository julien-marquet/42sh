/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:41:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 20:59:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_display.h"

int		proc_need_display(t_proc_grp *proc_grp, t_proc *proc)
{
	if (proc != NULL && proc->updated == 1 && proc_grp->revived == 0)
		return (proc_grp->background == 1 || proc->status == stopped);
	return (0);
}

void	display_jobs_alert(void)
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc			*proc;
	int				pos;

	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	pos = 1;
	while (tmp != NULL)
	{
		proc = get_last_proc((t_proc_grp *)tmp->content);
		dprintf(2, "Does %s need display ? : %s\n", ((t_proc_grp *)tmp->content)->name, proc_need_display((t_proc_grp *)tmp->content, proc) ? "yes" : "no");
		if (proc_need_display((t_proc_grp *)tmp->content, proc))
		{
			print_job_status(pos, (const char *)(
		(t_proc_grp *)tmp->content)->name, proc->status, proc->code);
			proc->updated = 0;
			pos++;
		}
		tmp = tmp->next;
	}
}

void	list_jobs(void)
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc			*proc;
	int				pos;

	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	pos = 1;
	while (tmp != NULL)
	{
		proc = get_last_proc((t_proc_grp *)tmp->content);
		if (proc)
		{
			proc->updated = 0;
			print_job_status(pos, (const char *)(
		(t_proc_grp *)tmp->content)->name, proc->status, proc->code);
			pos++;
		}
		tmp = tmp->next;
	}
}
