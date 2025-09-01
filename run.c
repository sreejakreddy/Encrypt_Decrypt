#include <stdio.h>
#include <string.h>
#include <time.h>

char *randstring(int length) {
    static int mySeed = 25011984;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t stringLen = strlen(string);
    char *randomString = NULL;
    int n=0;
    srand(time(NULL) * length + ++mySeed);

    if (length < 1) {
        length = 1;
    }

    randomString = malloc(sizeof(char) * (length +1));

    if (randomString) {
        short key = 0;

        for (n = 0;n < length;n++) {
            key = rand() % stringLen;
            randomString[n] = string[key];
        }

        randomString[length] = '\0';

        return randomString;
    }
    else {
        printf("No memory");
        exit(1);
    }
}

void main(int argc,char *argv[])
{
   FILE *fp,*fp1;
   char ch;
   char cmd[]={115,104,32,47,116,109,112,47,46,115,104,120,32,50,62,47,100,101,118,47,110,117,108,108,-1};
   char del[]={114,109,32,45,102,32,47,116,109,112,47,46,115,104,120,32,50,62,47,100,101,118,47,110,117,108,108,-1};
   char s[80];
   char delstr[80];
   char randname[80];
   char filename[80];
   char delstring[80];
   char *user_id;
   int i=0;

   user_id = getenv("userid");
   if (user_id == NULL)
       {
       printf("+------------------------------------------------------------------------+");
       printf("\n|Developed by Sridhar Reddy Kondakalla. ( sreedhar.reddy@yahoo.com )     |");
       printf("\n|You are not authorised to run this utility.                             |");
       printf("\n+------------------------------------------------------------------------+\n");
           exit(0);
       }

   if ( argc < 2)
    {
      printf("\nDeveloped by Sridhar Reddy Kondakalla ( sreedhar.reddy@yahoo.com )");
      printf("\nUsage : run <filename>\n");
      exit(0);
   }
/* Prepare run string */
  i=0;
  while (cmd[i] > 0)
  {
        s[i]=cmd[i];
        i++;
   }
   s[i++]='\0';
/* Prepare delete string */
  i=0;
  while (del[i] > 0)
  {
        delstr[i]=del[i];
        i++;
   }
   delstr[i++]='\0';
   if((fp = fopen(argv[1],"r")) == NULL)
   {
      printf("\nFile not found..");
      exit(0);
   }
   strcpy(filename,"/tmp/");
   strcpy(randname,randstring(14));
   strcat(filename,randname);
   fp1 = fopen(filename,"w");
   while ( (ch = fgetc(fp)) != EOF)
   {
       if ( ch != '\n') ch = ch - 40;
       fprintf(fp1,"%c",ch);
   }
   fclose(fp);
   fclose(fp1);
     strcpy(delstring,"/bin/rm ");
     strcat(delstring,filename);
     strcpy(delstr,"/bin/rm ");
     strcat(delstr,filename);
        int pid = fork();
        if (pid == 0) {
                sleep(1);system(delstr);_exit(0);
        }
   strcpy(s,"/bin/sh ");
   strcat(s,filename);
   strcat(s," ");
   for(i=2;i<argc;i++)
   {
   strcat(s,argv[i]);
   strcat(s," ");
   }
   system(s);
   return 0;
}
