#include "editing/input/input_completion.h"
#include "editing/input/input_action_handlers.h"

int		handle_completion(t_input_data *input)
{ 
	if (insert_dyn_buf("", input->active_buf, input->rel_cur_pos) == 1)
		return (1);
	
	/* if (insertn_chars(input, "", 1, 0) == 1) */
	return (0);
}
