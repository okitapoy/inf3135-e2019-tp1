#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ARG_CODE_P  "-c"
#define ARG_ENCRYPT "-e"
#define ARG_DECRYPT "-d"
#define ARG_CLE "-k"

#define ARG_ENTREE "-i"
#define ARG_SORTIE "-o"
#define ARG_FIC_ALPHA "-a"




//fonction qui verifier larg -o ou -i, fichier entrant et sortant
int verifierArgFichier(char *tab[],int tailleTab,char argument[]){
  int i = 1;
  int codeRetour = -1;


  for(i; i < tailleTab; i++){
     if(strcmp(argument,tab[i]) == 0){
        codeRetour = i;
     }

  }

  return codeRetour;

}




//fonction qui verifier si -e ou -d est present retourne 0  pour crypter et  1 pour decrypter
int verfierArgCryptage(char *tab[],int tailleTab){
  int i = 1;
  int codeRetour = -1;
  int cryptage = 0;
  int decryptage = 1;

  for(i; i < tailleTab; i++){
     if(strcmp(ARG_ENCRYPT,tab[i]) == 0){
       codeRetour = cryptage;
     }else if(strcmp(ARG_DECRYPT,tab[i]) == 0){
       codeRetour = decryptage;
     }
  }

  if(codeRetour == -1){
    printf("argument -e ou -d nest pas present\n");
    exit(4);
  }

  return codeRetour;

}


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


//fonction qui verifie si un String a juste des chiffre ou non

void veriferChiffre(char *tab[],int indiceFixe){

  int i = 0;
  int taille = strlen(tab[indiceFixe]);

  if(tab[indiceFixe][0] == '-'){
    i = 1;
  }

  for(i; i < taille; i++){
    char c = tab[indiceFixe][i];
    if(!isdigit(c)){
      printf("valeur de -k est non conforme\n");//--------- a retirer
      exit(7);
    }
  }
}



int main(int argc,char * argv[]) {

  //indice d'ou se trouve les args dans le tableau
  int indiceCodeP;
  int indiceCryptage;
  int indiceCle;
  int indiceNombreSaut;
  int indiceFichierEntree;
  int indiceFichierSortie;

  long cle;
  char fichierEntree[100];
  char fichierSortie[100];

  if(argc == 1){
    exit(1);
  }else{
   indiceCodeP =  verifierArgPresent(argv,argc,ARG_CODE_P,1) + 1;
  }

/*si  -c   a revoir
   if(indiceCodeP < argc && strlen(argv[indiceCodeP]) != 12){
     exit(1); //message erreur a mettre
   }else if(indiceCodeP >= argc){
     exit(1);
   }
  }
*/



  indiceCryptage = verfierArgCryptage(argv,argc);
  indiceNombreSaut  =  verifierArgPresent(argv,argc,ARG_CLE,7) + 1;

//char *test[] = argv[indiceNombreSaut];
//printf("le cara est : %s\n",argv[indiceNombreSaut]); 
//printf("%d\n",strlen(argv[indiceNombreSaut]));

//valider la cle et transformenr en string
  if(indiceNombreSaut >= argc){
    printf("largument de -k est invalide");
    exit(7);
  }else{
    veriferChiffre(argv,indiceNombreSaut);
    cle = strtol(argv[indiceNombreSaut],NULL,10);
printf("larg de -k est VALIDE = %ld",cle);//--------------------- a enlever
  }


//fichier en entree 
  indiceFichierEntree = verifierArgFichier(argv,argc,ARG_ENTREE) + 1;
  if(indiceFichierEntree != 0){
    if(indiceFichierEntree >= argc){
      printf("l'argument -i n'a pas de valeur\n");
      exit(5);
    }else{
      strcpy(fichierEntree,argv[indiceFichierEntree]);
printf("le nom du fichier est : %s\n",fichierEntree);//-------------------a enlever
    }

  }


//fichier en sortie 
  indiceFichierEntree = verifierArgFichier(argv,argc,ARG_SORTIE) + 1;










//  test = verifierArgPresent(argv,argc,ARG_ENTREE,5);



printf("\nFIN NORMALE DU PROGRAMME\n");

   /* test.
    int chiffre = 55;
    int deux = 2;
    printf("premeier = %d et deuxieme = %d et la somme = %d ",chiffre,deux,chiffre + deux);
    */

    return 0;
}
