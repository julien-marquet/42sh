#include "editing/input/input_completion.h"
#include "editing/input/input_action_handlers.h"

char	*get_current_word(t_input_data *input)
{
	size_t	i;
	char	*word;
	char	*pointer;

	i = 0;
	pointer = input->active_buf->buf + input->rel_cur_pos;
	while (pointer != input->active_buf->buf)
	{
		if (*pointer == ' ' && *(pointer - 1) != '\\')
		{
			i -= 1;
			break ;
		}
		i += 1;
		pointer -= 1;
	}
	if ((word = malloc(i + 1)) == NULL)
		return (NULL);
	ft_strncpy(word, input->active_buf->buf + input->rel_cur_pos - i, i);
	word[i] = '\0';
	return (word);
}

int		handle_completion(t_input_data *input)
{ 
	char	*currentWord;

	if (insert_dyn_buf("", input->active_buf, input->rel_cur_pos) == 1)
		return (1);
	if ((currentWord = get_current_word(input)) == NULL)
		return (1);
	dprintf(2, "CurrentWord: |%s|\n", currentWord);
	free(currentWord);
	return (0);
}
