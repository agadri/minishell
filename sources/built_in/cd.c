#include "../../includes/minishell.h"


/* ==== CD === */

void	built_in_cd(char *path)//chdir?? man
{
	if (chdir(path) == -1)//chdir permet de redefinir le chemin si path == ".." le chemin rendu recule
		printf("chdir()\n");
}
//SHLVL=1

