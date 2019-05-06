/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 17:38:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 17:39:01 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"

void			swap_words(char **pointer, char **current_word, char **word)
{
	if (**pointer == '\0')
	{
		ft_strdel(current_word);
		*current_word = *word;
	}
	else
		ft_strdel(word);
}

int				completion_exit(char **str, int ret)
{
	ft_strdel(str);
	return (ret);
}
