/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_utils.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 22:22:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:24:56 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_UTILS_H
# define HASH_UTILS_H

# include "common.h"

int			test_bin(char *bin_path);
char		*create_path(char *path, char *bin);
char		*add_path(char *path, t_list **table, char *bin, size_t inc_hits);
char		*permission_denied(char *path);
int			not_found(char *bin);

#endif