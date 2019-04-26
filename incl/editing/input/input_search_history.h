/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_search_history.h                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 04:25:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 06:19:16 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_SEARCH_HISTORY_H
# define INPUT_SEARCH_HISTORY_H

# include "common.h"
# include "input.h"

int		handle_search_input(t_sh_state *sh_state, t_input_data *input_data);
int		find_in_history(t_sh_state *sh_state, t_input_data *input_data,
		char *searched, int next);

#endif
