/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_utils.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:27:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:30:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_UTILS_H
# define STORAGE_UTILS_H

#include "common.h"

t_list	*find_node_by_name(t_list *env, const char *var_name);
char	*create_entry(const char *name, const char *value, const size_t size);
void	remove_node(t_list **alst, t_list **node, t_list *prev);

#endif