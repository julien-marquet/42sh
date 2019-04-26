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

#ifndef STORAGE_UTILS_H
# define STORAGE_UTILS_H

# include "common.h"
# include "data/data_utils/data_utils.h"

t_list	*find_node_by_name(t_list *env, const char *var_name);
int		fill_entry(t_internal_storage *entry, const char *name,
		const char *value, const size_t size);
void	remove_storage_node(t_list **alst, t_list **node, t_list *prev);
int		update_existing_node(t_list **hash_table, t_list *node,
		const char *name, const char *value, size_t len);

#endif
