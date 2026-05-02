#include "../include/minishell.h"


/* Yeni bir redirection düğümü oluşturur */
t_redir	*new_redir(char *file, t_redir_type type)
{
	t_redir	*redir;
 
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = file; /* file zaten ft_strdup ile gelecek, burada kopyalamıyoruz */
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

/* Redirection'ı listenin sonuna ekler */
void	redir_add_back(t_redir **list, t_redir *new)
{
	t_redir	*temp;
 
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}


 