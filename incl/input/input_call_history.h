/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_call_history.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:03:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 20:11:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_CALL_HISTORY_H
# define INPUT_CALL_HISTORY_H

# include "common.h"
# include "input/input.h"

int		free_hist_copy(t_list **hist_copy, int res);
int		hist_move_up(t_input_data *input_data, t_list *hist_copy);
int		hist_move_down(t_input_data *input_data, t_list *hist_copy);
int		dup_history(t_input_data *input_data, t_list **hist_copy);

#endif