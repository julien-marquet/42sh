/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_data.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 05:09:49 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 02:17:44 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/input_data.h"

t_input_data	*init_input_data(void)
{
	t_input_data	*input_data;

	if ((input_data = (t_input_data*)ft_memalloc(sizeof(t_input_data))) == NULL)
		return (NULL);
	if ((input_data->build_buf = init_dyn_buf()) == NULL ||
(input_data->active_buf = init_dyn_buf()) == NULL ||
(input_data->stored_buf = init_dyn_buf()) == NULL ||
(input_data->initial_buf = init_dyn_buf()) == NULL)
		return (NULL);
	if ((input_data->start_pos =
(t_cur_abs_pos*)malloc(sizeof(t_cur_abs_pos))) == NULL)
		return (NULL);
	return (input_data);
}

void			free_input_data(t_input_data **input_data)
{
	void (*del)(void *, size_t);
	del = free_lstnode;
	ft_lstdel(&((*input_data)->history_list), del);
	free_dyn_buf(&((*input_data)->active_buf));
	free_dyn_buf(&((*input_data)->build_buf));
	free_dyn_buf(&((*input_data)->stored_buf));
	free_dyn_buf(&((*input_data)->initial_buf));
	free((*input_data)->start_pos);
	ft_strdel(&(*input_data)->clipboard);
	free(*input_data);
}
