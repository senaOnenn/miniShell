#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../LIBFT/libft.h"
# include "../../PRINTF/ft_printf.h"
# include "../../get_next_line/get_next_line.h"

/* ======================== TOKEN TÜRLERİ ======================== */
/* Lexer'ın ürettiği token türleri                                 */

typedef enum e_token_type
{
	TOKEN_WORD,		/* komut, argüman, dosya adı    */
	TOKEN_PIPE,		/* |                            */
	TOKEN_LESS,		/* <  → input redirection       */
	TOKEN_GREAT,	/* >  → output redirection      */
	TOKEN_DGREAT,	/* >> → append redirection      */
	TOKEN_DLESS,	/* << → heredoc                 */
}	t_token_type;

/* ======================== TOKEN ======================== */
/* Lexer'ın ürettiği linked list düğümü                   */

typedef struct s_token
{
	char			*value;		/* token'ın string değeri  */
	t_token_type	type;		/* token türü              */
	struct s_token	*next;		/* sonraki token           */
}	t_token;

/* ======================== REDİRECTİON TÜRLERİ ======================== */
/* Parser'ın t_redir listesinde kullandığı türler                        */

typedef enum e_redir_type
{
	REDIR_IN,		/* <  → dosyadan oku        */
	REDIR_OUT,		/* >  → dosyaya yaz         */
	REDIR_APPEND,	/* >> → dosyaya ekle        */
	REDIR_HEREDOC,	/* << → delimiter'a kadar   */
}	t_redir_type;

/* ======================== REDİRECTİON ======================== */
/* Her redirection için dosya adı ve türü tutar                   */

typedef struct s_redir
{
	char			*file;		/* dosya adı ya da heredoc delimiter */
	t_redir_type	type;		/* redirection türü                  */
	struct s_redir	*next;		/* sonraki redirection               */
}	t_redir;

/* ======================== KOMUT ======================== */
/* Parser çıktısı: tek bir komut birimi                    */

typedef struct s_cmd
{
	char	**args;		/* ["ls", "-l", NULL] şeklinde NULL sonlandırılmış */
	t_redir	*redirs;	/* bu komutun redirection listesi                  */
	int		input_fd;	/* varsayılan: 0 (STDIN)                           */
	int		output_fd;	/* varsayılan: 1 (STDOUT)                          */
	int		is_builtin;	/* 1: builtin, 0: external komut                   */
	int		(*builtin_func)(char **args, char ***env); /* builtin pointer  */
}	t_cmd;

/* ======================== ANA YAPI ======================== */
/* Shell'in tüm durumunu tutan ana struct                     */

typedef struct s_shell
{
	t_cmd	*cmds;			/* komut dizisi (pipe için birden fazla olabilir) */
	int		cmd_count;		/* toplam komut sayısı (pipe sayısı + 1)          */
	char	**env;			/* environment değişkenleri kopyası               */
	int		exit_status;	/* son çalışan komutun çıkış kodu ($?)            */
	int		signal_received;/* yakalanan sinyal numarası                      */
}	t_shell;

/* ======================== TEK GLOBAL ======================== */
/* Norm kuralı: sadece 1 global değişkene izin var             */

extern volatile sig_atomic_t	g_signal;

/* ======================== LEXER PROTOTİPLERİ ======================== */
/* lexer.c → ham string'i token listesine dönüştürür               */

t_token	*lexer(char *line);					/* ana lexer fonksiyonu        */
t_token	*new_token(char *value, t_token_type type);	/* yeni token oluştur  */
void	token_add_back(t_token **lst, t_token *new);	/* listeye ekle        */
void	free_tokens(t_token *lst);				/* token listesini serbest bırak */
void	print_tokens(t_token *lst);				/* debug: tokenları yazdır */

/* ======================== PARSER PROTOTİPLERİ ======================== */
/* parser.c → token listesini t_cmd yapısına dönüştürür            */

t_cmd	*parser(t_token *tokens, char **env);	/* ana parser fonksiyonu       */
t_cmd	*new_cmd(void);						/* boş t_cmd oluştur           */
t_redir	*new_redir(char *file, t_redir_type type);	/* yeni redir oluştur  */
void	redir_add_back(t_redir **lst, t_redir *new);	/* redir listeye ekle  */
void	free_cmds(t_cmd *cmds, int count);		/* komut dizisini serbest bırak */

/* ======================== EXPANSION PROTOTİPLERİ ======================== */
/* expand.c → $VAR ve $? genişletmesi                              */

char	*expand_line(char *line, char **env, int exit_status); /* tüm satırı genişlet */
char	*get_env_value(char *key, char **env);	/* env'den değer al    */

/* ======================== BUİLTİN PROTOTİPLERİ ======================== */
/* builtin.c → shell'in kendi içinde çalıştırdığı komutlar         */

int		builtin_echo(char **args, char ***env);		/* echo [-n]           */
int		builtin_cd(char **args, char ***env);		/* cd [path]           */
int		builtin_pwd(char **args, char ***env);		/* pwd                 */
int		builtin_env(char **args, char ***env);		/* env                 */
int		builtin_export(char **args, char ***env);	/* export KEY=VAL      */
int		builtin_unset(char **args, char ***env);	/* unset KEY           */
int		builtin_exit(char **args, char ***env);		/* exit [kod]          */
int		is_builtin(char *cmd);						/* builtin mi kontrol  */
void	set_builtin_func(t_cmd *cmd);				/* fonksiyon pointer'ı ata */

/* ======================== ENV PROTOTİPLERİ ======================== */
/* env_utils.c → environment yönetimi                              */

char	**env_copy(char **envp);					/* env dizisini kopyala    */
char	**env_update(char **env, char *key, char *value); /* ekle/güncelle   */
char	**env_remove(char **env, char *key);		/* env'den sil             */
int		env_size(char **env);					/* env eleman sayısı       */

/* ======================== GENEL YARDIMCILAR ======================== */

void	free_array(char **arr);					/* NULL sonlandırılmış diziyi sil */
char	*ft_strjoin_free(char *s1, char *s2);	/* join + s1'i free'le     */

#endif