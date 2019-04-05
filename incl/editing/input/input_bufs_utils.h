/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_bufs_utils.h                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:14:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_BUFS_UTILS_H
# define INPUT_BUFS_UTILS_H

# include "common.h"
# include "editing/input/input.h"

void	reset_input(t_input_data *input_data);
int		prepare_input(t_input_data *input_data);
int		merge_bufs(t_input_data *input_data, t_list *hist_copy, char *here_doc);

#endif