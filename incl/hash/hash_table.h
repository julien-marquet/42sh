/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_table.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 22:22:45 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 05:40:32 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include "common.h"
# include "storage/storage.h"

t_hash_table	*get_link(t_list **table, char *bin);
void			delete_table(t_list **table);
char			*append_bin(const char *bin, t_list **table,
			t_list *internal_storage, int *error);
char			*get_bin_path(const char **av, t_list **table,
			t_list *internal_storage, int *error);

#endif
