/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_getters.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 23:39:41 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 23:45:39 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIASES_GETTERS_H
# define ALIASES_GETTERS_H

# include "common.h"
# include "aliases/aliases_utils.h"

char	*get_alias(t_list *aliases, const char *var_name);

#endif
