/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:51:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:43:42 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define READ_SIZE 1024

# include "editing/input/input_action_handlers.h"
# include "editing/input/input_bufs_utils.h"
# include "editing/input/input_call_history.h"
# include "editing/input/input_capabilities_dispatchers.h"
# include "editing/input/input_control.h"
# include "editing/input/input_handlers.h"
# include "editing/input/input_keycodes.h"
# include "editing/input/input_main_process.h"
# include "editing/input/input_utils.h"
# include "editing/input/input_validator.h"
# include "editing/input/completion/completion.h"
# include "editing/input/input_selection.h"
# include "editing/input/input_search_mode.h"
# include "editing/input/input_search_history.h"
# include "editing/input/input_eof.h"
# include "editing/input/input_pasteboard.h"
# include "editing/input/input_sig_handlers.h"

#endif
