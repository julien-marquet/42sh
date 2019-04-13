/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 19:39:05 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 19:43:18 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"

char			*stresc(const char *find, char *str, int i);
char			*strndup_qr(char *str, size_t len);
char			*strinsert(char *dst, char *new, size_t i, size_t end);
int				is_quoted(char *str, int i);

#endif
