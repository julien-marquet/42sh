/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_env.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:26:37 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 01:58:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_ENV_H
# define STORAGE_ENV_H

# include "common.h"
# include "storage/storage_utils.h"

t_list	*init_env(const char **env);
void	print_env(t_list *internal_storage, int fd);

#endif
