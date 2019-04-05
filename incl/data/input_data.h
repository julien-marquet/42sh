/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_data.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:11:35 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:11:48 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_DATA_H
# define INPUT_DATA_H

# include "common.h"
# include "data/dyn_buf/dyn_buf.h"
# include "data/lst_utils.h"

t_input_data	*init_input_data(void);
void			free_input_data(t_input_data **input_data);

#endif
