/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 22:21:27 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 22:21:28 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_display.h"

int			proc_need_display(t_proc_grp *proc_grp, t_proc *proc)
{
	if (proc != NULL && proc->updated == 1 && proc_grp->revived == 0)
		return (proc_grp->background == 1 || proc->status == stopped);
	return (0);
}

int			get_control_attribute(int pos, t_proc *last_proc)
{
	int		res;

	res = pos < 2 ? pos + 1 : 0;
	if (!last_proc || last_proc->status == exited)
		res = 0;
	return (res);
}

int			get_job_pos(t_proc_grp *proc_grp)
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

void		display_job_alert(t_proc_grp *proc_grp, t_proc *last_proc)
{
	int				total;
	int				pos;
	t_pos_info		p_info;
	char			*display;

	display = NULL;
	total = get_displayable_proc_grp_nb();
	pos = get_job_pos(proc_grp);
	p_info.index = total - pos;
	p_info.attribute = get_control_attribute(pos, last_proc);
	p_info.proc = last_proc;
	p_info.proc_grp = proc_grp;
	add_job_status(p_info, 0, &display);
	if (display != NULL)
	{
		ft_putstr(display);
		ft_strdel(&display);
	}
}

t_pos_info	fill_infos(int index, int attribute,
t_proc *proc, t_proc_grp *proc_grp)
{
	t_pos_info	p_info;

	p_info.index = index;
	p_info.attribute = attribute;
	p_info.proc = proc;
	p_info.proc_grp = proc_grp;
	return (p_info);
}
