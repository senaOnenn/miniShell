#include "../include/minishell.h"

/* 
 * İstediğin hata mesajını STDERR'e (2) yazar ve 
 * fonksiyonların hata durumu olarak 1 dönmesini sağlar.
 */
int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}