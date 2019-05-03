/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_call_history.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:03:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 23:30:38 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_CALL_HISTORY_H
# define INPUT_CALL_HISTORY_H

# include "common.h"
# include "editing/input/input.h"

int		free_hist_copy(t_list **hist_copy, int res);
int		hist_move_up(t_input_data *input_data, t_list *hist_copy);
int		hist_move_down(t_input_data *input_data, t_list *hist_copy);
int		dup_history(t_sh_state *sh_state, t_list **hist_copy);

#endif
