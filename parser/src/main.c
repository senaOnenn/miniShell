#include "../include/minishell.h"
#include <stdio.h> // Sadece debug printf'leri için

/* Norm kuralı: Tek global değişken */
volatile sig_atomic_t	g_signal = 0;

/* BÜTÜN SİSTEMİN ÇIKTISINI EKRANA BASAN DEBUG FONKSİYONU */
static void	print_cmds_debug(t_shell *shell)
{
	int		i;
	int		j;
	t_redir	*redir;
	char	*r_types[] = {"< (IN)", "> (OUT)", ">> (APPEND)", "<< (HEREDOC)"};

	if (!shell->cmds)
		return ;
	printf("\n\033[1;32m--- PARSER ÇIKTISI (DEBUG) ---\033[0m\n");
	i = 0;
	while (i < shell->cmd_count)
	{
		printf("\033[1;36mKOMUT [%d]:\033[0m\n", i);
		
		/* Argümanları Bas */
		printf("  Argümanlar: ");
		j = 0;
		if (shell->cmds[i].args)
		{
			while (shell->cmds[i].args[j])
				printf("'%s' ", shell->cmds[i].args[j++]);
		}
		printf("\n");

		/* Yönlendirmeleri Bas */
		redir = shell->cmds[i].redir_lst;
		printf("  Yönlendirmeler: ");
		if (!redir)
			printf("Yok");
		while (redir)
		{
			printf("[%s %s] ", r_types[redir->type], redir->file);
			redir = redir->next;
		}
		printf("\n");

		/* Builtin Durumunu Bas */
		printf("  Builtin mi?: %s\n", shell->cmds[i].is_builtin ? "EVET" : "HAYIR");
		printf("------------------------------\n");
		i++;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_shell	shell;
	int		i;

	(void)argc;
	(void)argv;
	/* 1. Ortam değişkenlerini kopyala ve shell'i başlat */
	shell.env = env_copy(envp);
	shell.exit_status = 0;

	/* 2. Ana Okuma Döngüsü */
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ; /* Ctrl+D (EOF) gelirse döngüyü kır ve çık */
		}
		if (*line)
			add_history(line); /* Geçmişe ekle */

		/* 3. LEXER: Stringi parçala */
		tokens = lexer(line);
		if (tokens)
		{
			/* 4. PARSER: Tokenları komut paketlerine dönüştür */
			shell.cmd_count = count_cmds(tokens);
			shell.cmds = parser(tokens, shell.env);
			free_tokens(tokens); /* Tokenlarla işimiz bitti, temizle */

			if (shell.cmds)
			{
				/* 5. EXPAND: $USER, $? gibi değişkenleri aç */
				expand_cmds(&shell);

				/* 6. BUILTIN KONTROLÜ: Komut builtin ise pointer'ını ata */
				i = 0;
				while (i < shell.cmd_count)
				{
					set_builtin_func(&shell.cmds[i]);
					i++;
				}

				/* EKRANA BAS VE GÖR! */
				print_cmds_debug(&shell);

				/* İşimiz biten komutları hafızadan sil */
				free_cmds(shell.cmds, shell.cmd_count);
			}
		}
		free(line);
	}
	free_array(shell.env); /* Program biterken env'yi temizle */
	return (0);
}