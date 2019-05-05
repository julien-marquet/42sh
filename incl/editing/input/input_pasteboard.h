/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_pasteboard.h                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 18:16:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:32:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_PASTEBOARD_H
# define INPUT_PASTEBOARD_H

# include "common.h"
# include "data/dyn_buf/dyn_buf.h"
# include "editing/input/input.h"

int		pasteboard_handle_capabilities(t_input_data *input_data);

#endif
