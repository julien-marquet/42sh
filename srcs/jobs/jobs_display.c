/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:41:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 19:45:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_display.h"

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
		if (proc && proc->updated == 1)
		{
			print_job_status(pos, (const char *)(
		(t_proc_grp *)tmp->content)->name, proc->status, proc->code);
			proc->updated = 0;
		}
		pos++;
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
			print_job_status(pos, (const char *)(
		(t_proc_grp *)tmp->content)->name, proc->status, proc->code);
		}
		pos++;
		tmp = tmp->next;
	}
}
