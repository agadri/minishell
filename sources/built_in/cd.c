#include "../../includes/minishell.h"


/* ==== CD === */

void	built_in_cd(t_lexer *lexer, char *path)//chdir?? man
{
	lexer->command->oldpwd = ft_strdup(lexer->command->pwd);
	if (!path && lexer->command->home)
	{
		chdir(lexer->command->home);
	}
	else if (chdir(path) == -1)//chdir permet de redefinir le chemin si path == ".." le chemin rendu recule
		printf("chdir()\n	");
	//changer  le pwd (prend le chdir() et le old pwd(prend le pwd) de env swan t bo
}
//SHLVL=1

