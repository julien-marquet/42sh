/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:47:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 04:14:09 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define PROMPT_SIMPLE_TXT "\e[1m42sh \e[92m$ \e[0m"
# define PROMPT_SIMPLE_DISPLAY_LEN 7
# define PROMPT_SIMPLE_BUF_LEN 20

# define PROMPT_MULTI_TXT "\e[1m> \e[0m"
# define PROMPT_MULTI_DISPLAY_LEN 2
# define PROMPT_MULTI_BUF_LEN 10

# define PROMPT_SEARCH_TXT "\e[1m(\e[0mSearch\e[1m)\e[0m "
# define PROMPT_SEARCH_DISPLAY_LEN 9
# define PROMPT_SEARCH_BUF_LEN 25

# define PROMPT_NO_SET 0
# define PROMPT_SIMPLE 1
# define PROMPT_MULTI 2
# define PROMPT_NO_PRINT 3

# include "common.h"
# include "editing/input/input_search_mode.h"

size_t		print_prompt(int mode_modifier);
size_t		get_prompt_len(void);

#endif
