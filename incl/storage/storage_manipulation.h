/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulation.h                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:33:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:34:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_MANIPULATION_H
# define STORAGE_MANIPULATION_H

#include "common.h"
#include "storage/storage_utils.h"

char	*get_stored(t_list *storage, const char *var_name);
int		add_entry_storage(t_list **storage, const char *name, const char *value);
void	debug_dump_storage(t_list *storage);
int		remove_entry_storage(t_list **storage, char *name);

#endif