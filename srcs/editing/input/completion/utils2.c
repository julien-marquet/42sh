#include "editing/input/completion/completion.h"
#include "editing/input/input_action_handlers.h"

int		delete_completed(t_input_data *input)
{
	char *pointer;

	pointer = input->active_buf->buf + input->rel_cur_pos - 1;
	while (pointer != input->active_buf->buf)
	{
		if ((*pointer == '/') || (is_stopping(*pointer) && *(pointer - 1) != '\\'))
			break ;
		if ((*pointer == '$' && (is_stopping(*(pointer - 1)) && *(pointer - 2) != '\\')))
			break ;
		if (delete_prev_char(input) == 1)
			return (1);
		if (*(pointer - 1) == '$' && pointer - 1 == input->active_buf->buf)
			break ;
		pointer -= 1;
	}
	if (pointer == input->active_buf->buf && *pointer != '/')
		return (delete_prev_char(input));
	return (0);
}

size_t	is_path(const char *word)
{
	char	*pointer;

	pointer = (char *)word;
	while (*pointer)
	{
		if (*pointer == '/' &&
			(pointer == word || *(pointer - 1) != '\\'))
			return (1);
		pointer += 1;
	}
	return (0);
}
