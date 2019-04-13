/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:41:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 03:15:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_display.h"

int		print_pos(int pos)
{
	write(1, "[", 1);
	ft_putnbr(pos);
	write(1, "]", 1);
	return (ft_numlen_i(pos) + 2);
}

int		print_status(t_job_status status, int code)
{
	if (status == running || status == continued)
	{
		write(1, "Running", 7);
		return (7);
	}
	else if (status == exited)
	{
		write(1, "Done", 4);
		return (4);
	}
	else if (status == stopped)
	{
		write(1, "Stopped", 7);
		return (7);
	}
	else if (status == signaled)
	{
		write(1, "Terminated: ", 12);
		ft_putnbr(code);
		return (ft_numlen_i(code) + 12);
	}
	return (0);
}

void	print_spaces(int printed, int desired)
{
	int		i;

	i = 0;
	while (i < desired - printed)
	{
		write(1, " ", 1);
		i++;
	}
}

int		print_job_status(int pos, const char *name, t_job_status status, int code)
{
	int		printed;

	printed = print_pos(pos);
	print_spaces(printed, 10);
	printed = print_status(status, code);
	print_spaces(printed, 20);
	ft_putstr(name);
	ft_putchar('\n');
	return (0);
}

void	display_jobs_alert()
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc			*proc;
	int				pos;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	pos = 1;
	while (tmp != NULL)
	{
		proc = get_last_proc((t_proc_grp *)tmp->content);
		if (proc && proc->updated == 1)
		{
			print_job_status(pos, (const char *)((t_proc_grp *)tmp->content)->name,
		proc->status, proc->code);
			proc->updated = 0;
		}
		pos++;
		tmp = tmp->next;
	}
}

void	list_jobs()
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc			*proc;
	int				pos;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	pos = 1;
	while (tmp != NULL)
	{
		
		proc = get_last_proc((t_proc_grp *)tmp->content);
		if (proc)
		{
			print_job_status(pos, (const char *)((t_proc_grp *)tmp->content)->name,
		proc->status, proc->code);
		}
		pos++;
		tmp = tmp->next;
	}
}
