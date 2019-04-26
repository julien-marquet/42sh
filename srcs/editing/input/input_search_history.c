/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_search_history.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 04:24:25 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 05:08:48 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_search_history.h"

int		handle_search_input(t_input_data *input_data)
{
	char	*searched;
	const char	*tmp;
	size_t	len;

	searched = NULL;
	input_data->processed_chars = input_data->build_buf->len;
	if (is_capability(input_data->build_buf->buf) ||
input_data->build_buf->len > 1)
	{
		if (ft_strncmp(input_data->build_buf->buf, KEY_BS, 1) == 0 ||
ft_strncmp(input_data->build_buf->buf, KEY_BS2, 1) == 0)
		{
			tmp = get_searched();
			len = tmp == NULL ? 0 : ft_strlen(tmp);
			if (len > 0)
			{
				if ((searched = ft_strndup(tmp, len - 1)) == NULL)
					return (1);
			}
		}
	}
	else
	{
		tmp = get_searched();
		len = tmp == NULL ? 0 : ft_strlen(tmp);
		if ((searched = ft_memalloc(len + 2)) == NULL)
			return (1);
		if (tmp != NULL)
			ft_strcpy(searched, tmp);
		ft_strcpy(&(searched[len]), input_data->build_buf->buf);
	}
	if (searched != NULL)
	{
		// launch search
		set_searched(searched);
		print_anew(input_data->start_pos, input_data->active_buf,
	input_data->rel_cur_pos);
	}
	return (0);
}
