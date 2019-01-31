/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 23:30:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "sh.h"
#include "input/input.h"
#include "input/input_data.h"

int		main(void)
{
	t_sh_state		*sh_state;
	t_input_data	*input_data;

	sh_state = init_sh();
	input_data = init_input_data();
	while (sh_state->exit_sig == 0)
	{
		if (handle_input(sh_state, input_data) == 1)
		{
			sh_state->status = 1;
			break ;
		}
	}
	exit_sh(sh_state);
	return (0);
}
