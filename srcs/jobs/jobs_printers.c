/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:26:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 23:55:24 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_printers.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	print_pos(t_pos_info p_info, char **str)
{
	char	*tmp;

	if ((*str = ft_memalloc(ft_numlen_i(p_info.index) + 3 + (p_info.attribute != 0))) == NULL)
		return (-1);
	(*str)[0] = '[';
	if ((tmp = ft_itoa(p_info.index)) == NULL)
	{
		ft_strdel(str);
		return (-1);
	}
	ft_strcpy(&(*str)[1], tmp);
	(*str)[1 + ft_strlen(tmp)] = ']';
	if (p_info.attribute != 0)
		(*str)[2 + ft_strlen(tmp)] = p_info.attribute == 1 ? '+' : '-';
	ft_strdel(&tmp);
	return (ft_numlen_i(p_info.index) + 2 + (p_info.attribute != 0));
}

static int		print_status(t_job_status status, int code, char **str)
{
	char	*joined;
	char	*tmp;
	char	*tmpcode;
	int		len;

	tmp = NULL;
	if (*str == NULL)
		return (0);
	if (status == running || status == continued)
		tmp = ft_strdup("Running");
	else if (status == exited && code == 0)
		tmp = ft_strdup("Done");
	else if (status == exited)
	{
		if ((tmpcode = ft_itoa(code)) == NULL)
			return (0);
		tmp = ft_strjoin("Exited: ", tmpcode);
		ft_strdel(&tmpcode);
	}
	else if (status == stopped)
		tmp = ft_strdup("Stopped");
	else if (status == signaled)
	{
		if ((tmpcode = ft_itoa(code)) == NULL)
			return (0);
		tmp = ft_strjoin("Terminated: ", tmpcode);
		ft_strdel(&tmpcode);
	}
	if (tmp == NULL)
		return (0);
	if ((joined = ft_strjoin(*str, tmp)) != NULL)
	{
		ft_strdel(str);
		len = ft_strlen(tmp);
		*str = joined;
	}
	else
		len = 0;
	ft_strdel(&tmp);
	return (len);
}

static void	print_spaces(int printed, int desired, char **str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	size_t	slen;

	if (*str == NULL)
		slen = 0;
	else
		slen = ft_strlen(*str);
	i = 0;
	if ((tmp = ft_memalloc(slen + desired - printed + 1)) == NULL)
		return ;
	if (*str != NULL)
		ft_strcpy(tmp, *str);
	tmp2 = &(tmp[slen]);
	ft_strnfill(&tmp2, ' ', desired - printed);
	ft_strdel(str);
	*str = tmp;
}

void	print_name(const char *name, char **str)
{
	char	*tmp;
	size_t	slen;
	size_t	nlen;

	if (*str == NULL || name == NULL)
		return ;
	slen = ft_strlen(*str);
	nlen = ft_strlen(name);
	if ((tmp = ft_memalloc(slen + nlen + 2)) == NULL)
		return ;
	ft_strcpy(tmp, *str);
	ft_strcpy(&tmp[slen], name);
	tmp[slen + nlen] = '\n';
	ft_strdel(str);
	*str = tmp;
}

int		print_pid(int pid, char **str)
{
	char	*tmp;
	size_t	slen;
	char	*num;
	int		numlen;

	if (*str != NULL)
		slen = ft_strlen(*str);
	else
		slen = 0;
	numlen = ft_numlen_i(pid);
	if ((tmp = ft_memalloc(slen + numlen + 1)) == NULL)
		return (0);
	if ((num = ft_itoa(pid)) != NULL)
	{
		if (*str != NULL)
			ft_strcpy(tmp, *str);
		ft_strcpy(&tmp[slen], num);
		ft_strdel(&num);
	}
	ft_strdel(str);
	*str = tmp;
	return (numlen);
}

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
	char	*tmp;
	t_list	*proc;
	int		i;

	proc = p_info.proc_grp->procs;
	i = 0;
	str = NULL;
	while (proc)
	{
		p_info.proc = (t_proc *)proc->content;
		printed = 0;
		if (i == 0)
			printed = print_pos(p_info, &str);
		print_spaces(printed, 8, &str);
		printed = print_pid(p_info.proc->pid, &str);
		print_spaces(printed, 8, &str);
		printed = print_status(p_info.proc->status, p_info.proc->code, &str);
		print_spaces(printed, 20, &str);
		print_name(p_info.proc->name, &str);
		i++;
		proc = proc->next;
	}
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
