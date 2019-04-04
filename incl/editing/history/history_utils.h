/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_utils.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:23:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:13:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HISTORY_UTILS_H
# define HISTORY_UTILS_H

#include "common.h"
#include "editing/history/history.h"

int		navigate(t_input_data *input_data, t_list *hist_copy, int index, int old_i);

#endif