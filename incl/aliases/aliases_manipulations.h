/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_manipulations.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 20:03:20 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:51:16 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIASES_MANIPULATIONS_H
# define ALIASES_MANIPULATIONS_H

# include "common.h"
# include "utils/utils.h"
# include "aliases/aliases_utils.h"

int		add_alias(t_list **aliases, const char *name, const char *value);
void	print_aliases(t_list *aliases, int fd);
int		remove_alias(t_list **aliases, const char *name);

#endif
