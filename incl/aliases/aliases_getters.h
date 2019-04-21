/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_getters.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 23:39:41 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 21:12:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIASES_GETTERS_H
# define ALIASES_GETTERS_H

# include "common.h"
# include "aliases/aliases_utils.h"

char	*get_alias(t_list *aliases, const char *var_name);
t_list			*duplicate_aliases(t_list *aliases);

#endif
