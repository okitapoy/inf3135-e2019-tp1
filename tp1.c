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
#define ALPHA "alphabet.txt"
#define ALPHA_SLASH "/alphabet.txt"

int nbrSautLigne(char *tablo){
   int nombre = 0;

   for(int i = 0; i < strlen(tablo); i++){

     if(tablo[i] == '\n'){
     nombre++;
    }

   }
printf("nombre saut ligne = %d\n",nombre);


   return nombre;
}


//cryptage du texte
void cryptage(char *leTexte,char *alphabet,long lePas){

     int nombreSaut = nbrSautLigne(alphabet);
    //char alphabet[] = "qbcefghijzklnodprstuvawxym";
    long alphaLength = strlen(alphabet) - nombreSaut;
   printf("alpha length=== %d\n",alphaLength);

   // long lePas = 117;

    //char leTexte[] = "zoe est partie a la fois sais-tu valz"; //
    long textLength = strlen(leTexte);

    if(lePas > alphaLength){
        lePas = lePas % alphaLength;
    }else if(lePas < 0 && (lePas * -1) > alphaLength){
        lePas = ((lePas * -1) % alphaLength) * -1;
    }



    for(int i = 0; i < textLength; i++){


      if(isalpha(leTexte[i])){

            for(int n = 0; n < alphaLength;n++){
                if(leTexte[i] == alphabet[n]){
                  // printf("alpha num : %d, lettre : %c, alpha length : %d\n",n,leTexte[i],alphaLength);//---
                    if(n + lePas < alphaLength && n + lePas >= 0 ){
                      //  printf("\non est dans le tablo");
                        leTexte[i] =  alphabet[n + lePas];
                    }else{
                       // printf("\nerreur on deborde");
                        if(lePas > 0){

                            long difference = (alphaLength) - n;
                            long cleDeborde = lePas - difference;
                            leTexte[i] = alphabet[cleDeborde];

                        }else if(lePas < 0){
                            long differenceNeg = (alphaLength) + n;
                            long cleDebordeNeg = lePas + differenceNeg;
                            leTexte[i] = alphabet[cleDebordeNeg];

                        }
                    }

                    break;
                }
            }

       }
    }




}




//lit le fichier entree et cree une varabile de la chaine avec pointeur
void lireFichier(char *pointeur, const char fichierEntree[],int taille,int erreur){
     char *p;

  FILE *fichierIn = NULL;
  char caractere;
  int indice = 0;
  fichierIn = fopen(fichierEntree,"r");

  if(fichierIn != NULL){
    do{


       caractere = fgetc(fichierIn);

printf("%c",caractere);
       if(indice < taille && caractere != EOF){
       pointeur[indice] = caractere;
       indice++;

       }

   }while(caractere != EOF);
  fclose(fichierIn);

 }else{
   printf("Erreur de fichier");
   exit(erreur);
 }

printf("\n");

}




//retourne la longueur du  texte en entier, nombre de caractere
int longueurFichier(const char fichierEntree[]){


  FILE *fichierIn = NULL;
  int caractere;
  int sizeFichierEntree = 0;
  fichierIn = fopen(fichierEntree,"r");

  if(fichierIn != NULL){
    do{

       caractere = fgetc(fichierIn);
       sizeFichierEntree++;

   }while(caractere != EOF);
  fclose(fichierIn);

 }
  return sizeFichierEntree;
}


//fonction qui verifier l'arg -o ou -i, fichier entrant et sortant
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
  int indiceFichierAlpha;

  long cle;
  char fichierEntree[100];
  char fichierSortie[100];
  char fichierAlpha[100];

  //int sizeFichierEntree = 0;


  char  *pointeurEntree = NULL;
  char  *pointeurAlpha = NULL;



  if(argc == 1){
    exit(1);
  }else{
   indiceCodeP =  verifierArgPresent(argv,argc,ARG_CODE_P,1) + 1;
  }

   if(indiceCodeP < argc && strlen(argv[indiceCodeP]) != 12){
    printf("la valeur de -c doit etre de 12 caracteres\n");
     exit(1); //message erreur a mettre
   }else if(indiceCodeP >= argc){
     exit(1);
   }





  indiceCryptage = verfierArgCryptage(argv,argc);
  indiceNombreSaut  =  verifierArgPresent(argv,argc,ARG_CLE,7) + 1;


//valider la cle et transformenr en string
  if(indiceNombreSaut >= argc){
    printf("largument de -k est invalide");
    exit(7);
  }else{
    veriferChiffre(argv,indiceNombreSaut);
    cle = strtol(argv[indiceNombreSaut],NULL,10);
printf("larg de -k est VALIDE = %ld\n",cle);//--------------------- a enlever
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

     int sizeFichierEntree = longueurFichier(fichierEntree);
     char chaineEntree[sizeFichierEntree];

    pointeurEntree = (char*) malloc(sizeFichierEntree * sizeof(char));
   lireFichier(pointeurEntree,fichierEntree,sizeFichierEntree,5);

    }

  }else{
    pointeurEntree = (char*) malloc(1000 * sizeof(char));
    printf("Veillez entrer le texte :  ");
   fgets(pointeurEntree,1000,stdin);
  }


printf("pointeur string entree :  %s \n",pointeurEntree);//----------------------





//fichier alpha
  indiceFichierAlpha = verifierArgFichier(argv,argc,ARG_FIC_ALPHA) + 1;
  if(indiceFichierAlpha != 0){
    if(indiceFichierAlpha >= argc){
      printf("l'argument -a n'a pas de valeur\n");
      exit(8);
    }else{
      strcpy(fichierAlpha,argv[indiceFichierAlpha]);

      if(fichierAlpha[strlen(fichierAlpha)-1] == '/'){
       printf("ca fini avec le  slaashhhh");
       strcat(fichierAlpha,ALPHA);
      }else{
      strcat(fichierAlpha,ALPHA_SLASH);

      }

printf("le nom du fichier est : %s\n",fichierAlpha);//-------------------a enlever

    }

  }else{
      strcpy(fichierAlpha,ALPHA);
  printf("larg -a pas present, remplacer par default alphabet.txt\n");

  }
   int sizeFichierAlpha = longueurFichier(fichierAlpha);
   char chaineAlpha[sizeFichierAlpha];

   pointeurAlpha = (char*) malloc(sizeFichierAlpha * sizeof(char));
   lireFichier(pointeurAlpha,fichierAlpha,sizeFichierAlpha,8);
printf("la chaine alpha : %s\n",pointeurAlpha);



cryptage(pointeurEntree,pointeurAlpha,cle);
printf("nouveau apres cryptage : %s\n",pointeurEntree);



//fichier en sortie 
  indiceFichierSortie = verifierArgFichier(argv,argc,ARG_SORTIE) + 1;
  if(indiceFichierSortie != 0){
    if(indiceFichierSortie >= argc){
      printf("l'argument -o n'a pas de valeur\n");
      exit(6);
    }else{
      strcpy(fichierSortie,argv[indiceFichierSortie]);
printf("le nom du fichier est : %s\n",fichierSortie);//-------------------a enlever

    FILE *fichierOut = NULL;
    fichierOut = fopen(fichierSortie,"w");
   if(fichierOut != NULL){
   fputs(pointeurEntree,fichierOut);
   fclose(fichierOut);

   }else{
   printf("erreur avec le fichier sortie");
   exit(6);
   }

    }

  }else{
   fputs(pointeurEntree,stdout);

  }







printf("\nFIN NORMALE DU PROGRAMME\n");


    return 0;
}
