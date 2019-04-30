/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_validator.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:09:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:08:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_VALIDATOR_H
# define INPUT_VALIDATOR_H

# include "common.h"
# include "editing/input/input.h"

int		output_is_ready(t_dyn_buf *dyn_buf, int valid_here_doc);
int		here_doc_is_closed(t_dyn_buf *dyn_buf, char *here_doc);

#endif