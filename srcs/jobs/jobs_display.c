/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:41:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 22:59:59 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_display.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

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

void		list_jobs(int mode, char **display)
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
		if (proc)
		{
			p_info.index = total - pos;
			p_info.attribute = get_control_attribute(pos, proc);
			p_info.proc = proc;
			p_info.proc_grp = ((t_proc_grp *)tmp->content);
			add_job_status(p_info, mode, display);
			pos++;
		}
		tmp = tmp->next;
	}
}

void	display_numed_job(int mode, const char *search,
char **display, const char *origin)
{
	t_proc_grp	*proc_grp;
	t_pos_info		p_info;
	t_proc			*last_proc;
	char			*err;
	int				num;

	num = ft_atoi(search);
	if ((proc_grp = find_active_proc_grp_by_num(num)) != NULL)
	{
		last_proc = get_last_proc(proc_grp);
		p_info.index = num;
		p_info.attribute = get_control_attribute(num, last_proc);
		p_info.proc = last_proc;
		p_info.proc_grp = proc_grp;
		add_job_status(p_info, mode, display);
	}
	else
	{
		err = ft_construct_str(2, search, ": no such job");
		print_error(origin, err, 2);
		ft_strdel(&err);
	}
}

void	list_matching_jobs(int mode, const char *search, char **display, const char *origin)
{
	t_list		*tmp;
	t_jobs		*jobs;
	int			index;
	t_proc		*proc;
	int			total;
	t_pos_info		p_info;

	index = 0;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	total = get_active_proc_grp_nb();
	while (tmp != NULL)
	{
		if ((proc = get_last_proc_all(((t_proc_grp *)tmp->content))) != NULL)
		{
			if (proc->status != exited && proc->status != signaled)
				index++;
			if (ft_strstr(((t_proc_grp *)tmp->content)->name, search) != NULL)
			{
				p_info.index = index;
				p_info.attribute = get_control_attribute(index, proc);
				p_info.proc = proc;
				p_info.proc_grp = ((t_proc_grp *)tmp->content);
				add_job_status(p_info, mode, display);
			}
		}
		tmp = tmp->next;
	}
}

void	jobs_handle_display(int mode, const char *search, const char *origin)
{
	char	*display;

	display = NULL;
	if (search != NULL)
	{
		if (str_is_digit(search))
			display_numed_job(mode, search, &display, origin);
		else
			list_matching_jobs(mode, search, &display, origin);
	}
	else
		list_jobs(mode, &display);
	if (display != NULL)
	{
		ft_putstr(display);
		ft_strdel(&display);
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
