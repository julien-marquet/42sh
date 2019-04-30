/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 20:40:51 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 18:12:51 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

size_t			fc_hist_to_num(t_list *find, t_list *hist)
{
	size_t	num;

	num = 0;
	while (hist && hist != find)
	{
		hist = hist->next;
		num++;
	}
	if (hist != NULL)
		return (num);
	return (0);
}

size_t			fc_hist_to_num_rev(t_list *find, t_list *hist)
{
	size_t	num;

	num = 0;
	while (hist && hist != find)
		hist = hist->next;
	while (hist)
	{
		num++;
		hist = hist->next;
	}
	return (num);
}

size_t			fc_get_hist_num(t_sh_state *sh_state, const char *str)
{
	size_t	i;
	int		is_alpha;
	int		neg;
	t_list	*find;

	i = 0;
	is_alpha = 0;
	neg = str[i] == '-' ? 1 : 0;
	while (str[neg + i] && is_alpha == 0)
		is_alpha += !ft_isdigit(str[neg + i++]);
	if (!is_alpha)
	{
		if (neg == 0)
			return (ft_atoi(str));
		else
		{
			find = get_history_index_rev(sh_state->history, ft_atoi(str + 1));
			return (fc_hist_to_num(find, sh_state->history));
		}
	}
	else
	{
		find = get_history_search(sh_state->history, (char *)str);
		return (fc_hist_to_num_rev(find, sh_state->history));
	}
}

size_t			get_hist_len(t_list *hist)
{
	size_t len;

	len = 0;
	while (hist)
	{
		len++;
		hist = hist->next;
	}
	return (len);
}