#include <stdio.h>
#include <termios.h>
#define PASSWORD_LEN 8
void main(int argc,char *argv[])
{
   FILE *fp,*fp2;
   char ch;
   struct termios initialrsettings, newrsettings;
   char password[PASSWORD_LEN + 1];
   if ( argc < 4)
   {
      printf("\n+-------------------------------------------+");
      printf("\n|Usage: encdec <sourcefile> <outfile> D|E   |");
      printf("\n|Developed by : Sridhar K Reddy             |");
      printf("\n+-------------------------------------------+");
      exit(0);
   }

   if((fp = fopen(argv[1],"r")) == NULL)
   {
      printf("\n Source file not found..");
      exit(0);
   }
  if (strcmp(argv[1],argv[2]) == 0 )
  {
     printf("\n Cannot overwrite source file..");
     exit(0);
  }
  if((fp2 = fopen(argv[2],"w")) == NULL)
   {
      printf("\n Error in file open.\n");
      exit(0);
   }

   tcgetattr(fileno(stdin), &initialrsettings);
   newrsettings = initialrsettings;
   newrsettings.c_lflag &= ~ECHO;
   printf("Enter password: ");
   if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0)
      fprintf(stderr,"Could not set attributes\n");
   else {
      fgets(password, PASSWORD_LEN, stdin);
      tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
     /* fprintf(stdout, "\nYou entered %s\n", password); */
   }
  if ( atoi(password) == 7876 )
  {
   if ( strcmp(argv[3],"E") == 0)
   {
   while ( (ch = fgetc(fp)) != EOF)
   {
       ch = ch + 100; 
       fputc(ch, fp2);
   }
   }
   else
   while ( (ch = fgetc(fp)) != EOF)
   {
       ch = ch - 100;
       fputc(ch, fp2);
   }
  }
   else
   printf("\nInvalid Password.\n");
   fclose(fp);
}
