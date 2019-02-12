/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 10:51:17 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 13:42:14 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define HIST_NEXT 0
# define HIST_PREV 1
# define HIST_RESET 2

# include "common.h"
# include "input/input_data.h"

t_list		*init_history_list(void);
t_list		*get_history_index(t_list *history, size_t index);
t_list		*add_to_history_list(t_list **history, const char *buf, size_t len);
int			history_navigate(t_input_data *input_data, int action);

#endif
