/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers2.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 23:02:53 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:02:54 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_printers.h"

void	print_only_pgid(t_pos_info p_info, char **display)
{
	char	*tmp;
	size_t	slen;

	print_pid(p_info.proc_grp->pgid, display);
	if (*display)
		slen = ft_strlen(*display);
	else
		slen = 0;
	if ((tmp = ft_memalloc(slen + 2)) == NULL)
		return ;
	ft_strcpy(tmp, *display);
	ft_strcpy(&tmp[slen], "\n");
	ft_strdel(display);
	*display = tmp;
}

void	print_classic(t_pos_info p_info, char **display)
{
	char	*str;
	int		printed;
	char	*tmp;

	str = NULL;
	printed = print_pos(p_info, &str);
	print_spaces(printed, 8, &str);
	printed = print_status(p_info.proc->status, p_info.proc->code, &str);
	print_spaces(printed, 20, &str);
	print_name(p_info.proc_grp->name, &str);
	if (*display == NULL)
		*display = str;
	else if (str != NULL)
	{
		if ((tmp = ft_strjoin(str, *display)) != NULL)
		{
			ft_strdel(display);
			*display = tmp;
		}
		ft_strdel(&str);
	}
}

void	print_detailed(t_pos_info p_info, char **display)
{
	char	*str;
	int		printed;
	t_list	*proc;
	int		i;

	proc = p_info.proc_grp->procs;
	i = 0;
	str = NULL;
	while (proc)
	{
		p_info.proc = (t_proc *)proc->content;
		printed = i == 0 ? print_pos(p_info, &str) : 0;
		print_spaces(printed, 8, &str);
		printed = print_pid(p_info.proc->pid, &str);
		print_spaces(printed, 8, &str);
		printed = print_detailed_status(p_info.proc->status,
	p_info.proc->code, &str);
		print_spaces(printed, 20, &str);
		print_name(p_info.proc->name, &str);
		i++;
		proc = proc->next;
	}
	assign_display(display, &str);
}

void	add_job_status(t_pos_info p_info, int mode, char **display)
{
	if (mode == 0)
		print_classic(p_info, display);
	else if (mode == 1)
		print_detailed(p_info, display);
	else
		print_only_pgid(p_info, display);
}

void	print_job_bpid(t_pos_info p_info, int bpid)
{
	write(1, "[", 1);
	ft_putnbr(p_info.index);
	write(1, "] ", 2);
	ft_putnbr(bpid);
	write(1, "\n", 1);
}
