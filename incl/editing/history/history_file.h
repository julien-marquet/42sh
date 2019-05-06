/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_file.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 15:53:49 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 16:06:31 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HISTORY_FILE_H
# define HISTORY_FILE_H

# include "common.h"
# include "builtins/builtins_utils.h"
# include "history.h"

t_list		*hist_list_add(t_list *args, char *str, size_t len);
t_list		*hist_str2list(char *str);

#endif
