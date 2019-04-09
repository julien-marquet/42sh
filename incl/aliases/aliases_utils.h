/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_utils.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 21:52:17 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 03:00:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIASES_UTILS_H
# define ALIASES_UTILS_H

# include "common.h"
# include "data/data_utils/data_utils.h"

t_list	*find_alias_by_name(t_list *aliases, const char *var_name);
int		update_existing_alias(t_list *node, const char *name,
		const char *value, size_t len);
void	remove_alias_node(t_list **alst, t_list **node, t_list *prev);

#endif
