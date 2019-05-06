/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers3.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 23:59:48 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:59:48 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_printers.h"

int			print_pos(t_pos_info p_info, char **str)
{
	char	*tmp;

	if ((*str =
ft_memalloc(ft_numlen_i(p_info.index) + 3 + (p_info.attribute != 0))) == NULL)
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

void		assign_display(char **display, char **str)
{
	char	*tmp;

	if (*display == NULL)
		*display = *str;
	else if (*str != NULL)
	{
		if ((tmp = ft_strjoin(*str, *display)) != NULL)
		{
			ft_strdel(display);
			*display = tmp;
		}
		ft_strdel(str);
	}
}

static char	*get_code(char *str, int code)
{
	char	*tmp;
	char	*tmpcode;

	if ((tmpcode = ft_itoa(code)) == NULL)
		return (NULL);
	tmp = ft_strjoin(str, tmpcode);
	free(tmpcode);
	return (tmp);
}

char		*get_status_value(t_job_status status, int code, size_t detailed)
{
	char	*tmp;

	tmp = NULL;
	if (status == running || status == continued)
		tmp = ft_strdup("Running");
	else if (status == exited && code == 0)
		tmp = ft_strdup("Done");
	else if (status == exited)
		tmp = get_code("Exited: ", code);
	else if (status == stopped)
	{
		if (detailed)
			tmp = get_code("Stopped: ", code);
		else
			tmp = ft_strdup("Stopped");
	}
	else if (status == signaled)
		tmp = get_code("Terminated: ", code);
	return (tmp);
}
