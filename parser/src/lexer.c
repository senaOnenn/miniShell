#include "../include/minishell.h"

t_token	*lexer(char *line)
{
	t_token	*list;

	if (!line) /* Gelen string NULL ise hiç uğraşma, direkt dön */
		return (NULL);

	list = NULL;
	while (*line)
	{
		skip_spaces(&line);
		if (!*line)
			break ;
		if (*line == '|' || *line == '<' || *line == '>')
		{
			if (handle_operator(&line, &list) != 0)
			{
				free_tokens(list);
				return (NULL);
			}
		}
		else
		{
			if (handle_word(&line, &list) != 0)
			{
				free_tokens(list);
				return (NULL);
			}
		}
	}
	return (list);
}