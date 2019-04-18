/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_navigation.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:22:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 19:38:39 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HISTORY_NAVIGATION_H
# define HISTORY_NAVIGATION_H

# include "common.h"
# include "editing/history/history.h"
# include "data/dyn_buf/dyn_buf.h"

# define HIST_NEXT 0
# define HIST_PREV 1
# define HIST_RESET 2

t_list	*get_history_index(t_list *history, size_t index);
t_list	*get_history_index_rev(t_list *history, size_t index);
int		history_navigate(t_input_data *input_data,
		t_list *hist_copy, int action);

#endif
