/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:26:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 00:04:56 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_printers.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		print_status(t_job_status status, int code, char **str)
{
	char	*joined;
	char	*tmp;
	int		len;

	if (*str == NULL)
		return (0);
	tmp = get_status_value(status, code, 0);
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

int		print_detailed_status(t_job_status status, int code, char **str)
{
	char	*joined;
	char	*tmp;
	int		len;

	if (*str == NULL)
		return (0);
	tmp = get_status_value(status, code, 1);
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

void	print_spaces(int printed, int desired, char **str)
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
