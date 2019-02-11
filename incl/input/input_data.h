/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_data.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 05:09:58 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 17:19:46 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_DATA_H
# define INPUT_DATA_H

# include "common.h"
# include "utils/dyn_buf.h"

typedef struct	s_input_data
{
	t_dyn_buf		*input_buf;
	t_dyn_buf		*build_buf;
	t_dyn_buf		*stored_buf;
	char **			history;
	size_t			rel_cur_pos;
	size_t			processed_chars;
	t_cur_abs_pos	*start_pos;
}				t_input_data;

t_input_data	*init_input_data(void);

#endif
