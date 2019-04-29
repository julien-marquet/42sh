/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:26:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 13:12:34 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_printers.h"

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
	else if (status == exited)
		tmp = ft_strdup("Done");
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

	if (*str == NULL)
		return ;
	i = 0;
	if ((tmp = ft_memalloc(ft_strlen(*str) + desired - printed + 1)) == NULL)
		return ;
	ft_strcpy(tmp, *str);
	tmp2 = &(tmp[ft_strlen(*str)]);
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

int		add_job_status(t_pos_info p_info, const char *name,
t_proc *proc, char **job_status)
{
	char	*str;
	int		printed;
	char	*tmp;

	str = NULL;
	printed = print_pos(p_info, &str);
	print_spaces(printed, 8, &str);
	printed = print_status(proc->status, proc->code, &str);
	print_spaces(printed, 25, &str);
	print_name(name, &str);
	if (*job_status == NULL)
		*job_status = str;
	else if (str != NULL)
	{
		if ((tmp = ft_strjoin(str, *job_status)) != NULL)
		{
			ft_strdel(job_status);
			*job_status = tmp;
		}
		ft_strdel(&str);
	}
	return (0);
}

void	print_job_bpid(t_pos_info p_info, int bpid)
{
	write(1, "[", 1);
	ft_putnbr(p_info.index);
	write(1, "] [", 3);
	ft_putnbr(bpid);
	write(1, "]\n", 2);
}
