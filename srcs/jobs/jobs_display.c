/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:41:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:39:06 by jmarquet    ###    #+. /#+    ###.fr     */
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

int		get_control_attribute(int pos, t_proc *last_proc)
{
	int		res;

	res = pos < 2 ? pos + 1 : 0;
	if (!last_proc || last_proc->status == exited)
		res = 0;
	return (res);
}

int		get_job_pos(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	int				pos;

	tmp = jobs_super_get(NULL)->proc_grps;
	pos = 0;
	while (tmp != NULL)
	{
		if ((t_proc_grp *)tmp->content == proc_grp)
			break ;
		if (get_last_proc((t_proc_grp *)tmp->content) != NULL)
			pos++;
		tmp = tmp->next;
	}
	return (pos);
}

void	display_job_alert(t_proc_grp *proc_grp, t_proc *last_proc)
{
	int				total;
	int				pos;
	t_pos_info		p_info;
	char			*status;

	status = NULL;
	total = get_displayable_proc_grp_nb();
	pos = get_job_pos(proc_grp);
	p_info.index = total - pos;
	p_info.attribute = get_control_attribute(pos, last_proc);
	add_job_status(p_info, (const char *)proc_grp->name, last_proc, &status);
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
	total = get_displayable_proc_grp_nb();
	while (tmp != NULL)
	{
		proc = get_last_proc((t_proc_grp *)tmp->content);
		if (proc)
		{
			p_info.index = total - pos;
			p_info.attribute = get_control_attribute(pos, proc);
			add_job_status(p_info,
		(const char *)((t_proc_grp *)tmp->content)->name, proc, &status);
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

void	display_last_bpgid(int bpid, t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc			*proc;
	int				pos;
	int				total;
	t_pos_info		p_info;

	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	pos = 0;
	total = get_displayable_proc_grp_nb();
	while (tmp != NULL)
	{
		proc = get_last_proc((t_proc_grp *)tmp->content);
		if ((t_proc_grp *)tmp->content == proc_grp)
		{
			p_info.index = total - pos;
			p_info.attribute = get_control_attribute(pos, proc);
			print_job_bpid(p_info, bpid);
			break ;
		}
		if (proc)
			pos++;
		tmp = tmp->next;
	}
}
