/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:41:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 11:47:29 by jmarquet    ###    #+. /#+    ###.fr     */
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
	char			*status;
	int				total;
	t_pos_info		p_info;

	status = NULL;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	pos = 0;
	total = get_active_proc_grp_nb();
	while (tmp != NULL)
	{
		proc = get_last_proc((t_proc_grp *)tmp->content);
		if (proc_need_display((t_proc_grp *)tmp->content, proc))
		{
			p_info.index = total - pos;
			p_info.attribute = pos < 2 ? pos + 1 : 0;
			add_job_status(p_info, (const char *)((t_proc_grp *)tmp->content)->name, proc, &status);
			proc->updated = 0;
			pos++;
		}
		tmp = tmp->next;
	}
	if (status != NULL)
	{
		ft_putstr(status);
		ft_strdel(&status);
	}
}

void	list_jobs(void)
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc			*proc;
	int				pos;
	char			*status;
	int				total;
	t_pos_info		p_info;

	status = NULL;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	pos = 0;
	total = get_active_proc_grp_nb();
	while (tmp != NULL)
	{
		proc = get_last_proc((t_proc_grp *)tmp->content);
		if (proc)
		{
			p_info.index = total - pos;
			p_info.attribute = pos < 2 ? pos + 1 : 0;
			proc->updated = 0;
			add_job_status(p_info, (const char *)((t_proc_grp *)tmp->content)->name, proc, &status);
			pos++;
		}
		tmp = tmp->next;
	}
	if (status != NULL)
	{
		ft_putstr(status);
		ft_strdel(&status);
	}
}
