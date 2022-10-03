#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>


char queryn[100];
char txt[5];
int admin;

void password(char str[]) {

    int i = 0;
    char c;
    do {
      c = getch();
      if(c>=30)
      {
        printf("*");
        str[i]=c;
        i++;
      }
      else
      {
        if(c=='\b' && i>0)
        {
          printf("\b \b");
          i--;
        } 

      }

    }while(c != 13);

    str[i]='\0';

}

void addclient () {

  char name[75];
  char pass[75];
  char permission[100];
  char line[100];
  char *token;
  char tmp[100];
  int kick = 0 ;

  system("cls");
  printf("\033[1;32m");
  printf("\nDigitare il nome del cliente: ");
  printf("\033[0m");
  scanf("%s", name);

  FILE *pt;
  pt = fopen("Credenziali.txt","r+");
  while ((fgets(line, sizeof(line), pt) != NULL)){
      strcpy(tmp,line);
      token = strtok(line, ":");
      if ( strcmp(token, name) == 0){
            kick = 1;
            break;
          }
      token=strtok(NULL, ":");
      token=strtok(NULL, ":");
    }

  

  if(kick) {
    fclose(pt);
    printf("\033[1;31m");
    puts("\n\nAccount gia' esistente ");
    printf("\033[0m");
    puts("\n\nPremere un qualsiasi tasto per registrare nuovo utente");  
    getch();
    system("cls");
    addclient();
  }

  else {
    printf("\033[1;32m");
    printf("Password: ");
    printf("\033[0m");
    password(pass);
    printf("\033[1;32m");
    printf("\nPermessi (admin/user): ");
    printf("\033[0m");
    scanf("%s", permission);
    fprintf(pt,"%s:%s:%s\n",name , pass, permission);
    fclose(pt);
  
    printf("\033[0;32m");
    puts("\n\nAccount aggiunto correttamente!");
    printf("\033[0m");
    puts("\n\nPremere un qualsiasi tasto per tornare al menu principale...");  
    getch();
    system("cls");
  }

}


void add () {

  char email[100];
  char  passw[150];
  char  sito[100];
  system("cls");
  printf("\033[1;32m");
  puts("\n\t\tDigitare il nome del sito/applicazione: ");
  printf("\033[0m");
  scanf("%s", sito);
  printf("\033[1;32m");
  puts("Email/Username: ");
  printf("\033[0m");
  scanf("%s", email);
  printf("\033[1;32m");
  puts("Password: ");
  printf("\033[0m");
  scanf("%s", passw);

  FILE *pt;
  pt = fopen(queryn,"a");
  fprintf(pt,"%s:%s:%s\n",sito , email, passw);
  fclose(pt);
  
  printf("\033[0;32m");
  puts("\n\nCredenziali aggiunte correttamente!");
  printf("\033[0m");
  puts("\n\nPremere un qualsiasi tasto per tornare al menu principale...");  
  getch();
  system("cls");

}

void modify(){
  char query[100];
  char creds[250];
  char temp[250];
  char newSito[50];
  char newEmail[50];
  char newPassw[150];
  bool risposta;
  char *token;
  int sesso;
  int trovato=0;

  system("cls");
  printf("\033[1;33m");
  puts("\n\t\tNome del login da modificare? ");
  printf("\033[0m");
  scanf("%s", query);
  puts("\n");
  FILE *pt, *ptemp;
  pt= fopen(queryn, "r");
  ptemp= fopen("AccountTemporaneo.txt", "w");
  while ( (fgets(creds, sizeof(creds), pt) != NULL)){
      strcpy(temp,creds);
      token = strtok(creds, ":");
      if ( strcmp(token, query) == 0){
            trovato=1;
            strcpy(newSito, token);
            system("cls");
            printf("\033[1;32m");
            printf("Sito: ");
            printf("\033[0m");
            printf("%s  ",newSito);
            printf("\033[1;32m");
            token = strtok(NULL, ":");
            strcpy(newEmail, token);
            printf("Username/Email: ");
            printf("\033[0m");
            printf("%s  ",newEmail);
            printf("\033[1;32m");
            token = strtok(NULL, ":");
            strcpy(newPassw, token);
            printf("Password: ");
            printf("\033[0m");
            printf("%s \n\n",newPassw);
            printf("\033[1;31m");
            puts("Vuoi modificarlo? 0=>SI, 1=>NO");
            printf("\033[0m");
            scanf("%d", &sesso);
            risposta=sesso;
            if (risposta == 0)
                {
                  system("cls");
                  printf("\033[1;32m");
                  puts("Nuovo nome del Sito: ");
                  printf("\033[0m");
                  scanf("%s", newSito);
                  printf("\033[1;32m");
                  puts("Nuovo Email/Username: ");
                  printf("\033[0m");
                  scanf("%s", newEmail);
                  printf("\033[1;32m");
                  puts("Nuova Password: ");
                  printf("\033[0m");
                  scanf("%s", newPassw);
                  fprintf(ptemp, "%s:%s:%s\n", newSito,newEmail,newPassw);
                }
            else
                fprintf(ptemp, "%s",temp );
      }
      else 
        fprintf(ptemp, "%s",temp );      
      }
 if (trovato==1 && risposta == 0){
      printf("\033[0;32m");
      puts("\n\nCredenziali sostituite correttamente!");
      printf("\033[0m");
  }
  else if ((fgets(creds, sizeof(creds), pt) == NULL)){
      printf("\033[1;31m");
      puts("\nNessuna corrispondenza trovata! ");
      printf("\033[0m");
  }
  puts("\n\nPremere un qualsiasi tasto per tornare al menu principale...");  
  getch();
  system("cls");

  fclose(pt);
  fclose(ptemp);
  remove(queryn);
  rename("AccountTemporaneo.txt", queryn);
  
  
  
}

void delete(){
  char query[100];
  char creds[250];
  char temp[250];
  char newSito[50];
  char newEmail[50];
  char newPassw[150];
  bool risposta;
  char *token;
  int sesso;
  int trovato=0;
  int skip=0;

  system("cls");
  printf("\033[1;31m");
  puts("\n\t\tNome del login da rimuovere? ");
  printf("\033[0m");
  scanf("%s", query);
  puts("\n");

  FILE *pt, *ptemp;
  pt= fopen(queryn, "r");
  ptemp= fopen("AccountTemporaneo.txt", "w");

  while ( (fgets(creds, sizeof(creds), pt) != NULL)){
      strcpy(temp,creds);
      token = strtok(creds, ":");
      if ( strcmp(token, query) == 0){
            trovato=1;

            strcpy(newSito, token);
            system("cls");
            printf("\033[1;32m");
            printf("Sito: ");
            printf("\033[0m");
            printf("%s  ",newSito);
            printf("\033[1;32m");
            token = strtok(NULL, ":");
            strcpy(newEmail, token);
            printf("Username/Email: ");
            printf("\033[0m");
            printf("%s  ",newEmail);
            printf("\033[1;32m");
            token = strtok(NULL, ":");
            strcpy(newPassw, token);
            printf("Password: ");
            printf("\033[0m");
            printf("%s \n\n",newPassw);

            printf("\033[1;31m");
            puts("Vuoi rimuoverlo? 0=>SI, 1=>NO");
            printf("\033[0m");
            scanf("%d", &sesso);
            risposta=sesso;

            if (risposta == 0)
                  fprintf(ptemp, "");
                
            else  
                 fprintf(ptemp, "%s:%s:%s", newSito,newEmail,newPassw);

            skip = 0;
      }
      else
       fprintf(ptemp, "%s", temp );      
      }

 if (trovato==1 && risposta == 0){
      printf("\033[0;32m");
      puts("\n\nCredenziali eliminate correttamente!");
      printf("\033[0m");
  }
  else if ((fgets(creds, sizeof(creds), pt) == NULL)){
      printf("\033[1;31m");
      puts("\nNessuna corrispondenza trovata! ");
      printf("\033[0m");
  }
  puts("\n\nPremere un qualsiasi tasto per tornare al menu principale...");  
  getch();
  system("cls");

  fclose(pt);
  fclose(ptemp);
  remove(queryn);
  rename("AccountTemporaneo.txt", queryn);
  

}

void deleteacc(){
  char acc[100];
  char creds[250];
  char temp[250];
  char newAcc[50];
  char newPass[50];
  char newPwr[50];
  bool risposta;
  char *token;
  int sesso;
  int trovato=0;
  int skip=0;

  system("cls");
  printf("\033[1;31m");
  puts("\n\t\tNome del login da rimuovere? ");
  printf("\033[0m");
  scanf("%s", acc);
  puts("\n");

  FILE *pt, *ptemp;
  pt= fopen("Credenziali.txt", "r");
  ptemp= fopen("AccountTemporaneo.txt", "w");

  while ( (fgets(creds, sizeof(creds), pt) != NULL)){
      strcpy(temp,creds);
      token = strtok(creds, ":");
      if ( strcmp(token, acc) == 0){
            trovato=1;

            strcpy(newAcc, token);
            system("cls");
            printf("\033[1;32m");
            printf("Utente: ");
            printf("\033[0m");
            printf("%s  ",newAcc);
            printf("\033[1;32m");
            token = strtok(NULL, ":");
            strcpy(newPass, token);
       /*   printf("Password: ");
            printf("\033[0m");
            printf("%s  ",newPass);
          */printf("\033[1;32m");
            token = strtok(NULL, ":");
            strcpy(newPwr, token);
            printf("Privilegi: ");
            printf("\033[0m");
            printf("%s \n\n",newPwr);

            printf("\033[1;31m");
            puts("Vuoi rimuoverlo? 0=>SI, 1=>NO");
            printf("\033[0m");
            scanf("%d", &sesso);
            risposta=sesso;

            if (risposta == 0)
                  fprintf(ptemp, "");
                
            else  
                 fprintf(ptemp, "%s:%s:%s", newAcc,newPass,newPwr);

            skip = 0;
      }
      else
       fprintf(ptemp, "%s", temp );      
      }

 if (trovato==1 && risposta == 0){
      printf("\033[0;32m");
      puts("\n\nAccount eliminato correttamente!");
      printf("\033[0m");
  }
  else if ((fgets(creds, sizeof(creds), pt) == NULL)){
      printf("\033[1;31m");
      puts("\nNessun account trovata! ");
      printf("\033[0m");
  }
  puts("\n\nPremere un qualsiasi tasto per tornare al menu principale...");  
  getch();
  system("cls");

  fclose(pt);
  fclose(ptemp);
  remove("Credenziali.txt");
  rename("AccountTemporaneo.txt", "Credenziali.txt");
  

}

void search(){
  char query[100];
  char creds[250];
  char * token;
  int trovato=0;
  char newSito[50];
  char newEmail[50];
  char newPassw[150];

  printf("\033[01;33m");
  puts("\n\t\tNome del login da visualizzare? ");
  printf("\033[0m");
  scanf("%s", query);
  system("cls");

  printf("\033[01;33m");
  puts("\n\t\tRisultati della ricerca\n ");
  printf("\033[0m");
  FILE *pt;
  pt= fopen(queryn, "r+");
  while ( (fgets(creds, sizeof(creds), pt) != NULL)){
      token=strtok(creds, ":");
      if ( strcmp(token, query) == 0){
          strcpy(newSito,token);
          token=strtok(NULL, ":");
          strcpy(newEmail,token);
          token=strtok(NULL, ":");
          strcpy(newPassw,token);
          printf("\033[1;32m");
          printf("Sito: ");
          printf("\033[0m");
          printf("%s  ",newSito);
          printf("\033[1;32m");
          printf("Username/Email: ");
          printf("\033[0m");
          printf("%s  ",newEmail);
          printf("\033[1;32m");
          printf("Password: ");
          printf("\033[0m");
          printf("%s",newPassw);
          trovato=1;
      }
      
  }
  puts("\n");
  fclose(pt);

  if (trovato == 0){
      printf("\033[1;31m");
      puts("Nessuna credenziale trovata! \n\n");
      printf("\033[0m");
  }

  puts("\n\nPremere un qualsiasi tasto per tornare al menu principale...");  
  getch();
  system("cls");
}


void view(){
  char creds[250];
  char * token;
  char newSito[50];

  system("cls");
  printf("\033[01;33m");
  puts("\n\t\tSiti registrati\n");
  printf("\033[0m");
  FILE *pt;
  pt= fopen(queryn, "r+");

    while ((fgets(creds, sizeof(creds), pt) != NULL)){

      token=strtok(creds, ":");
      strcpy(newSito,token);
      token=strtok(NULL, ":");
      token=strtok(NULL, ":");
      printf("\033[1;32m");
      printf("\tSito: ");
      printf("\033[0m");
      printf("%s\n  ",newSito);
    
    }


  puts("\n\nPremere un qualsiasi tasto per tornare al menu principale...");  
  getch();
  system("cls");
  

  puts("\n");
  fclose(pt);
}

void verify() {

  char queryp[100];
  char test[100];
  char power[10] = "admin\n";
  char * token;
  FILE *key;
  int check = 0;

  system("cls");
  printf("\033[1;32m");
  puts("\t\t\t _    ____ ____ _ _  _ ");
  puts("\t\t\t |    |  | | __ | |\\ | ");
  puts("\t\t\t |___ |__| |__] | | \\| ");
  printf("\033[0m");     
  puts("                                                                                               \n\n ");

  printf("\033[01;33m");
  printf("\t\tUtente: ");
  printf("\033[0m");
  printf("\033[1;32m");
  scanf("%s", queryn);
  printf("\033[0m");
  printf("\033[01;33m");
  printf("\n\t\tPassword: ");
  printf("\033[0m");
  printf("\033[1;32m");
  password(queryp);
  printf("\033[0m");
  system("cls");

  key = fopen("Credenziali.txt", "r");

  //char name[100];
  //char pass[100];

 
  while ( (fgets(test, sizeof(test), key) != NULL)){
      token=strtok(test, ":");
    
      if ( strcmp(token, queryn) == 0){
          //strcpy(name,token);
          token=strtok(NULL, ":");
         
          if(strcmp(token, queryp) == 0) {
             // strcpy(pass,token);
              token=strtok(NULL, ":");

             if(strcmp(token, power) == 0) 
                check=2;
                      
             else
                check=1;
              
          }
      }
      
  }
 
  fclose(key);

  if (check == 0){
      printf("\033[1;31m");
      puts("      ____ ____ ____ ____ ____   ");
      puts("      |___ |__/ |__/ |  | |__/   ");
      puts("      |___ |  \\ |  \\ |__| |  \\ ");
                         
      printf("\033[0m"); 
      getch();
      exit(EXIT_SUCCESS);
      system("cls");
  }

  
  else if(check == 2) {
      admin = 1;
      printf("\033[1;33m");
      puts("      _  _ _  _ _    ____ ____ _  _ ____ ___  ");
      puts("      |  | |\\ | |    |  | |    |_/  |___ |  \\ ");
      puts("      |__| | \\| |___ |__| |___ | \\_ |___ |__/ ");
      puts("              ____ ___  _  _ _ _  _ ");
      puts("              |__| |  \\ |\\/| | |\\ | ");
      puts("              |  | |__/ |  | | | \\| ");
                                                          
      printf("\033[0m"); 

      puts("\n\nPremi un tasto per accedere al menu principale"); 
      getch();
      system("cls");
    
  }

  else{
      printf("\033[1;32m");
      puts("      _  _ _  _ _    ____ ____ _  _ ____ ___  ");
      puts("      |  | |\\ | |    |  | |    |_/  |___ |  \\ ");
      puts("      |__| | \\| |___ |__| |___ | \\_ |___ |__/ ");
                                          
      printf("\033[0m"); 

      puts("\n\nPremi un tasto per accedere al menu principale"); 
      getch();
      system("cls");
  }

  
}




int main () {
    size_t scelta;
    FILE *pt;
    char creds[250];

    strcpy(txt,".txt");

    verify();

    strncat(queryn,txt,20);
    

    while (1)
    {   pt = fopen(queryn, "r+");
  
        switch(admin)
        {
        case 1:
            do{
        system("cls");
        printf("\033[1;32m");
        puts("___  ____ ____ ____ _ _ _ ____ ____ ___     _  _ ____ _  _ ____ ____ ____ ____         ____     ");
        puts("|__] |__| [__  [__  | | | |  | |__/ |  \\    |\\/| |__| |\\ | |__| | __ |___ |__/     |   |  |     ");
        puts("|    |  | ___] ___] |_|_| |__| |  \\ |__/    |  | |  | | \\| |  | |__] |___ |  \\     | . |__|     ");
        printf("\033[0m");

        if(!fgets(creds, sizeof(creds), pt)) {
          printf("\033[1;31m");                     
          puts(" \n\t\t                   NESSUNA CREDENZIALE INSERITA                                                                          ");
          puts(" \t\t\t                   DIGITARE 1                                                                          \n\n ");
          printf("\033[0m");
        }

        else 
          puts("                                                                                               \n\n ");
        

        fclose(pt);

        pt = fopen(queryn, "r+");
        if(!fgets(creds, sizeof(creds), pt)) {
          do{
            scanf("%d", &scelta);
          }while(scelta!=1);
        }
        
        else{
          printf("%c 1 - Aggiungere una credenziale\n", 201);
          printf("%c 2 - Modificare una credenziale\n", 204);
          printf("%c 3 - Visualizzare una credenziale\n", 204);
          printf("%c 4 - Elimina una credenziale \n", 204);
          printf("%c 5 - Visualizzare i siti registrati\n", 204);
          printf("\033[1;33m");
          printf("%c 6 - Aggiungere un account\n", 204);
          printf("\033[0m");
          printf("\033[1;33m");
          printf("%c 7 - Eliminare un account\n", 204);
          printf("\033[0m");
          printf("%c 8 - Esci\n\n? ", 200);
          scanf("%d", &scelta);
        }
        fclose(pt);
        }while (scelta < 0 || scelta > 8);
        switch (scelta)
        {


        case 1:
          system("cls");
          add();  
          break;

        case 2:
          system("cls");
          modify();
          break;

        case 3:
          system("cls");
          search();
          break;

        case 4:
          system("cls");
          delete();
          break;

        case 5:
          system("cls");
          view();
          break;

        case 6:
          system("cls");
          addclient();  
          break;

         case 7:
          system("cls");
          deleteacc();  
          break;

        case 8:
          system("cls");
          printf("\n\n\n\t\t\tCC 2020 - P0WEX Creative Commons Lincenses ");
          sleep(1);
          system("cls");
          exit(EXIT_SUCCESS);
          break;

        

        }
        break;

        case 0:
  
        do{
        system("cls");
        printf("\033[1;32m");
        puts("___  ____ ____ ____ _ _ _ ____ ____ ___     _  _ ____ _  _ ____ ____ ____ ____         ____     ");
        puts("|__] |__| [__  [__  | | | |  | |__/ |  \\    |\\/| |__| |\\ | |__| | __ |___ |__/     |   |  |     ");
        puts("|    |  | ___] ___] |_|_| |__| |  \\ |__/    |  | |  | | \\| |  | |__] |___ |  \\     | . |__|     ");
        printf("\033[0m");

        if(!fgets(creds, sizeof(creds), pt)) {
          printf("\033[1;31m");                     
          puts(" \n\t\t                   NESSUNA CREDENZIALE INSERITA                                                                          ");
          puts(" \t\t\t                   DIGITARE 1                                                                          \n\n ");
          printf("\033[0m");
        }

        else 
          puts("                                                                                               \n\n ");
        

        fclose(pt);

        pt = fopen(queryn, "r+");
        if(!fgets(creds, sizeof(creds), pt)) {
          do{
            scanf("%d", &scelta);
          }while(scelta!=1);
        }
        
        else{
          printf("%c 1 - Aggiungere una credenziale\n", 201);
          printf("%c 2 - Modificare una credenziale\n", 204);
          printf("%c 3 - Visualizzare una credenziale\n", 204);
          printf("%c 4 - Elimina una credenziale \n", 204);
          printf("%c 5 - Visualizzare i siti registrati\n", 204);
          printf("%c 6 - Esci\n\n? ", 200);
          scanf("%d", &scelta);
        }
        fclose(pt);
        }while (scelta < 0 || scelta > 6);
        switch (scelta)
        {

        case 1:
          system("cls");
          add();  
          break;

        case 2:
          system("cls");
          modify();
          break;

        case 3:
          system("cls");
          search();
          break;

        case 4:
          system("cls");
          delete();
          break;

        case 5:
          system("cls");
          view();
          break;

        case 6:
          system("cls");
          printf("\n\n\n\t\t\tCC 2020 - P0WEX Creative Commons Lincenses ");
          sleep(1);
          system("cls");
          exit(EXIT_SUCCESS);
          break;
        }
        }
    }
    return 0;
}
