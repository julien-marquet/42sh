/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_data.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 05:09:49 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 13:40:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input_data.h"
#include "utils/dyn_buf.h"
#include "input/cursor.h"

t_input_data	*init_input_data(void)
{
	t_input_data	*input_data;

	if ((input_data = (t_input_data*)malloc(sizeof(t_input_data))) == NULL)
		return (NULL);
	if ((input_data->build_buf = init_dyn_buf()) == NULL ||
(input_data->input_buf = init_dyn_buf()) == NULL ||
(input_data->stored_buf = init_dyn_buf()) == NULL)
		return (NULL);
	if ((input_data->start_pos =
(t_cur_abs_pos*)malloc(sizeof(t_cur_abs_pos))) == NULL)
		return (NULL);
	input_data->rel_cur_pos = 0;
	input_data->processed_chars = 0;
	input_data->start_pos->col = 0;
	input_data->start_pos->row = 0;
	return (input_data);
}
