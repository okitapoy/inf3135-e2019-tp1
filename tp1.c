#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ARG_CODE_P  "-c"
#define ARG_ENCRYPT "-e"
#define ARG_DECRYPT "-d"
#define ARG_CLE "-k"

#define ARG_ENTREE "-i"
#define ARG_SORTIE "-o"
#define ARG_FIC_ALPHA "-a"


//fonction qui verifie si un argument obligatoire  est present

int verifierArgPresent(char *tab[],int tailleTab,char argument[],int codeErreur){
  int i = 1;
  int codeRetour = -1;

  for(i; i < tailleTab; i++){
     if(strcmp(argument,tab[i]) == 0){
       codeRetour = i;
     }
  }

  if(codeRetour ==  -1){
  printf("arg non trouver eeeerrruurr erreur : %d \n",codeErreur);//-------- ligne a retire
   exit(codeErreur);
  }

  printf("l'argument : %s, a ete trouver a lindice %d\n",argument,codeRetour);

  return codeRetour;

}




int main(int argc,char * argv[]) {

  //indice d'ou se trouve les args dans le tableau
  int indiceCodeP;
  int indiceCryptage;
  int indiceCle;

  if(argc == 1){
    exit(1);
  }else{
   indiceCodeP =  verifierArgPresent(argv,argc,ARG_CODE_P,1) + 1;

   if(indiceCodeP < argc && strlen(argv[indiceCodeP]) != 12){
     exit(1); //message erreur a mettre
   }else if(indiceCodeP > argc){
     exit(1);
   }
  }
















//  test = verifierArgPresent(argv,argc,ARG_ENTREE,5);



printf("\nFIN NORMALE DU PROGRAMME\n");

   /* test.
    int chiffre = 55;
    int deux = 2;
    printf("premeier = %d et deuxieme = %d et la somme = %d ",chiffre,deux,chiffre + deux);
    */

    return 0;
}
