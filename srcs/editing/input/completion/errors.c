/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   errors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 21:34:30 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 21:34:31 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"

int		free_exit(t_list *files, char *str)
{
	lstfree(files);
	if (str != NULL)
		free(str);
	return (1);
}