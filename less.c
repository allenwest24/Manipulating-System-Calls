// Copyright iSecLab -- www.iseclab.org

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

   FILE *file = fopen("/etc/passwd","r");
   if (file==NULL)
   {
      printf("Oh no, first open failed!\n");
      system("less /usr/local/share/error.txt");
      /* Mayday mayday! Bailing out */
      exit(1);
   }
   FILE *file2 = fopen("/etc/passwd","r");
   if (file2==NULL)
   {
      fclose(file);
      printf("Oh no, second open failed!\n");
      system("less /usr/local/share/error.txt");
      /* Mayday mayday! Bailing out */
      exit(1);
   }
   FILE *file3 = fopen("/etc/passwd","r");
   if (file3==NULL)
   {
      fclose(file);
      fclose(file2);
      printf("Oh no, third open failed!\n");
      system("less /usr/local/share/error.txt");
      /* Mayday mayday! Bailing out */
      exit(1);
   }
   FILE *file4 = fopen("/etc/passwd","r");
   if (file4==NULL)
   {
      fclose(file);
      fclose(file2);
      fclose(file3);
      printf("Oh no, fourth open failed!\n");
      system("less /usr/local/share/error.txt");
      /* Mayday mayday! Bailing out */
      exit(1);
   }

   /* Imagine we are doing something very important and useful here... */

   printf("I managed to successfully open the /etc/passwd file 4 times! I am the king yeahaaaa!\n\n");
   printf("Never think you've seen the last of anything. Eudora Welty\n\n");

   return 0;
}
