/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_print.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 21:30:39 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 21:38:04 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static void		hist_print(t_list *hist, size_t len, int num)
{
	while (hist && num > 0)
	{
		num--;
		dprintf(1, "%zu\t%s\n", len--, hist->content);
		hist = hist->next;
	}
}

static void		hist_print_rev(t_list *hist, size_t len, int num)
{
	if (hist && num > 0)
	{
		hist_print_rev(hist->next, len - 1, num - 1);
		dprintf(1, "%zu\t%s\n", len, hist->content);
	}
}

int				fc_print(t_list *hist, t_fc_infos *fc_infos)
{
	hist = hist->next;
	if (fc_infos->first == -1)
	{
		if (ft_strchr(fc_infos->opts, 'r'))
			hist_print(hist, get_hist_len(hist), 16);
		else
			hist_print_rev(hist, get_hist_len(hist), 16);
	}
	else
	{
		if (fc_infos->last != -1)
		{
			if (fc_infos->first > fc_infos->last)
			{
				int num = fc_infos->first;
				fc_infos->first = fc_infos->last;
				fc_infos->last = num;
				add_valid(fc_infos, 'r');
			}
			hist = get_history_index_rev(hist, fc_infos->last);
		}
		else
			hist = get_history_index_rev(hist, fc_infos->first);
		if (ft_strchr(fc_infos->opts, 'r'))
			hist_print(hist, get_hist_len(hist), get_hist_len(hist) - fc_infos->first + 1);
		else
			hist_print_rev(hist, get_hist_len(hist), get_hist_len(hist) - fc_infos->first + 1);
	}
	return (0);
}
