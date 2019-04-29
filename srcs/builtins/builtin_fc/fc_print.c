/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_print.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 21:30:39 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 10:56:48 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static void	hist_print(t_fc_infos *fc_infos, size_t len, int flag_n, int fd)
{
	while (fc_infos->first && fc_infos->first != fc_infos->last)
	{
		if (fd == 1)
		{
			if (flag_n == 0)
				ft_putnbr_fd(len--, fd);
			ft_putchar_fd('\t', fd);
		}
		ft_putstr_fd(fc_infos->first->content, fd);
		ft_putchar_fd('\n', fd);
		fc_infos->first = fc_infos->first->next;
	}
}

static void	hist_print_rev(t_fc_infos *fc_infos, size_t len, int flag_n, int fd)
{
	t_list *tmp;

	if (fc_infos->first && fc_infos->first != fc_infos->last)
	{
		tmp = fc_infos->first;
		fc_infos->first = fc_infos->first->next;
		hist_print_rev(fc_infos, len - 1, flag_n, fd);
		fc_infos->first = tmp;
		if (fd == 1)
		{
			if (flag_n == 0)
				ft_putnbr_fd(len--, fd);
			ft_putchar_fd('\t', fd);
		}
		ft_putstr_fd(fc_infos->first->content, fd);
		ft_putchar_fd('\n', fd);
	}
}

int				fc_print(t_list *hist, t_fc_infos *fc_infos, int fd)
{
	int		flag_n;
	size_t	len;
	t_list	*tmp;

	hist = hist->next;
	len = get_hist_len(hist);
	flag_n = ft_strchr(fc_infos->opts, 'n') ? 1 : 0;
	if (fc_infos->first == NULL)
	{
		fc_infos->first = hist;
		fc_infos->last = get_history_index(hist, fd == 1 ? 16 : 1);
		if (ft_strchr(fc_infos->opts, 'r'))
			hist_print(fc_infos, len, flag_n, fd);
		else
			hist_print_rev(fc_infos, len, flag_n, fd);
	}
	else
	{
		tmp = fc_infos->last;
		fc_infos->last = fc_infos->first->next;
		fc_infos->first = tmp == NULL ? hist : tmp;
		len = get_hist_len(fc_infos->first);
		if (ft_strchr(fc_infos->opts, 'r'))
			hist_print(fc_infos, len, flag_n, fd);
		else
			hist_print_rev(fc_infos, len,flag_n, fd);
	}
	return (fd == 1 ? fc_exit(fc_infos, 0) : 0);
}
