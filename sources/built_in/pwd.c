#include "../../includes/minishell.h"

/* ==== PWD === */

//getcwd permet de recuperer le chemin du fichier donne donc exactement se pwd fait

void	built_in_pwd(void)
{
	char cwd[256];//taille random pouvant contenir tt le chemin...on verra en fonction de la longueur 
	
	if (getcwd(cwd, sizeof(cwd)) != NULL)//petite secu
		printf("%s\n", cwd);//pouf on affiche le chemin incroyable
	//else
		//il me semble qu'il affiche rien si pas de chemin ...a verifier
}