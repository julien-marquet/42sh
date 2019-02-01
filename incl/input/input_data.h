/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_data.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 05:09:58 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 01:38:58 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_DATA_H
# define INPUT_DATA_H

# include "common.h"
# include "utils/dyn_buf.h"

typedef struct	s_input_data
{
	t_dyn_buf	*input_buf;
	t_dyn_buf	*build_buf;
	size_t		rel_cur_pos;
}				t_input_data;

t_input_data	*init_input_data(void);

#endif
