/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_utils.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 21:52:17 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 22:14:28 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIASES_UTILS_H
# define ALIASES_UTILS_H

# include "common.h"
# include "utils/utils.h"

t_list	*find_alias_by_name(t_list *aliases, const char *var_name);
int		update_existing_alias(t_list *node, const char *name,
		const char *value, size_t len);

#endif
