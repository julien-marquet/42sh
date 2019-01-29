/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 05:53:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "sh.h"
#include "input.h"

int		main(void)
{
	t_sh_state	*sh_state;
	char		*input;

	sh_state = init_sh();
	while (sh_state->exit_sig == 0)
	{
		input = handle_input(sh_state);
		sh_state->exit_sig = 1;
	}
	exit_sh(0, sh_state);
	return (0);
}
