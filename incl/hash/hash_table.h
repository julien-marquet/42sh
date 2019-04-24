/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_table.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 22:22:45 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:31:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include "common.h"
# include "storage/storage.h"

t_hash_table	*get_link(t_list **table, char *bin);
void			delete_table(t_list **table);
char			*append_bin(char *bin, t_list **table,
			t_list *internal_storage, size_t *error);
char			*get_bin_path(char **av, t_list **table,
			t_list *internal_storage, size_t *error);

#endif
