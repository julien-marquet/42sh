/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo_utils.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 02:52:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 02:55:29 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_ECHO_UTILS_H
# define BUILTIN_ECHO_UTILS_H

# include "common.h"

int		get_octal_chars_nb(const char *str);
int		convert_to_decimal(int octal);

#endif
