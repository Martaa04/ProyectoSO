#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	char input[100];
	
	strcpy(input,"maria/ana/juan/otto/sara");
		
	char *p=strtok(input,"/");
	char nombre [20];
	while (p!=NULL)
	{
		strcpy(nombre,p);
		
		int i=0;
		int found=1;
		while (i<(strlen(nombre)/2) && found)
		{
			if (nombre[i]!= nombre[strlen(nombre)-1-i])
				found= 0;	
			i++;
		}
		
		if (!found)
			printf("%s no es palindromo\n",nombre);
			
		else
			printf("%s es palindromo\n",nombre);
		
		p=strtok(NULL, "/");
	}

}

