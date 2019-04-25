/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_utils.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 22:22:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 05:44:07 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_UTILS_H
# define HASH_UTILS_H

# include "common.h"

void		handle_bin_error(int error, char *path);
int			test_bin(char *bin_path);
char		*create_path(const char *path, const char *bin);
char		*add_path(char *path, t_list **table, const char *bin, size_t inc_hits);
int			not_found(char *bin);

#endif
