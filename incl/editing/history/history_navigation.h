/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_navigation.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:22:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:13:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HISTORY_NAVIGATION_H
# define HISTORY_NAVIGATION_H

#include "common.h"
#include "editing/history/history.h"
#include "data/dyn_buf.h"

# define HIST_NEXT 0
# define HIST_PREV 1
# define HIST_RESET 2

t_list	*get_history_index(t_list *history, size_t index);
int		history_navigate(t_input_data *input_data, t_list *hist_copy, int action);

#endif