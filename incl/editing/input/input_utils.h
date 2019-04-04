/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_utils.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:13:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_UTILS_H
# define INPUT_UTILS_H

# include "common.h"
# include "editing/input/input.h"

int		count_escape_chars(char *str);
int		is_capability(char *s);
int		is_sig(char *s);
int		is_escaped(char *str, size_t i);

#endif
