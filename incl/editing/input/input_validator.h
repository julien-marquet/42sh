/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_validator.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:09:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:14:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_VALIDATOR_H
# define INPUT_VALIDATOR_H

# define QUOTE_NONE 0
# define QUOTE_SIMPLE 1
# define QUOTE_DOUBLE 2

# include "common.h"
# include "editing/input/input.h"

int		output_is_ready(t_dyn_buf *dyn_buf, char *here_doc);

#endif