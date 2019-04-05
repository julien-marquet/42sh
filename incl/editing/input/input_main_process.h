/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_main_process.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:59:03 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_MAIN_PROCESS_H
# define INPUT_MAIN_PROCESS_H

#include "common.h"
#include "editing/input/input.h"

int		handle_input(t_sh_state *sh_state, t_input_data *input_data, char *here_doc);

#endif