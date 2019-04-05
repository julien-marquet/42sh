/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:33:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:05:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_MANIPULATION_H
# define STORAGE_MANIPULATION_H

# include "common.h"
# include "storage/storage_utils.h"

int		add_entry_storage(t_list **storage, const char *name,
		const char *value);
void	debug_dump_storage(t_list *storage);
int		remove_entry_storage(t_list **storage, char *name);
#endif