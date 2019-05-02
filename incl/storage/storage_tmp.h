/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_utils.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:27:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 03:00:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_TMP_H
# define STORAGE_TMP_H

# include "common.h"

void		remove_tmp_env(t_list **storage);
char		**update_env(char **env, t_list *tmp);
int			update_builtin_env(t_list **storage, t_list *vars);

#endif
