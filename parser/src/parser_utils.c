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

/* t_redir listesini serbest bırakır */
static void	free_redirs(t_redir *list)
{
	t_redir	*tmp;
 
	while (list)
	{
		tmp = list->next;
		free(list->file); /* new_redir'e ft_strdup ile geldi, free edilmeli */
		free(list);
		list = tmp;
	}
}

/* t_cmd dizisinin tamamını serbest bırakır */
void	free_cmds(t_cmd *cmds, int count)
{
	int	i;
 
	if (!cmds)
		return ;
	i = 0;
	while (i < count)
	{
		if (cmds[i].args != NULL)	
			free_array(cmds[i].args); /* NULL sonlandırılmış string dizisi */
		if(cmds[i].redir_lst != NULL)
			free_redirs(cmds[i].redir_lst);
		i++;
	}
	free(cmds);
}
 