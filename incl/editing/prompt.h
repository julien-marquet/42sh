/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:47:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:14:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define PROMPT_SIMPLE_TXT "Prompt - "
# define PROMPT_SIMPLE_LEN 9
# define PROMPT_MULTI_TXT "> "
# define PROMPT_MULTI_LEN 2

# define PROMPT_NO_SET 0
# define PROMPT_SIMPLE 1
# define PROMPT_MULTI 2
# define PROMPT_NO_PRINT 3

# include "common.h"

size_t	print_prompt(int mode_modifier);
size_t	get_prompt_len(void);

#endif
