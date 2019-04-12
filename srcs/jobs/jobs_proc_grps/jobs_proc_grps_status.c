/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_status.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 22:20:15 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 22:21:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc_grps/jobs_proc_grps_status.h"

int		get_proc_grp_status(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_proc			*proc;
	t_job_status	status;
	t_list			*prev;

	status = -1;
	prev = NULL;
	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		if (proc->updated == 1)
			status = proc->status;
		if (tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (status);
}
