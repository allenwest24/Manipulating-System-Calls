#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

char cmdbuf[128] = "echo interrupt signal caught, terminating ";
char *progname;

void handle_signal(int sig)
{
   int len = sizeof(cmdbuf) - (strlen(cmdbuf) + 1);
   if (strlen(progname) > len)
      progname[len] = '\0';
   strcat(cmdbuf, progname);

   system(cmdbuf);
   exit(1);
}

void usage()
{
   printf("%s <n> where 0 < n <= 1000\n", progname);
   exit(1);
}

/* 
 * The program takes one argument line parameter n (which has to be a
 * positive integer input parameter) and then prints out the first n
 * prime numbers.
 */
int main(int argc, char **argv)
{
   struct sigaction sa;
   int cnt, N, found;
   unsigned long candidate, divisor;

   gid_t egid = getegid();
   setregid(egid, egid);

   /* set up signal handling */
   memset(&sa, sizeof(struct sigaction), 0);
   sa.sa_handler = handle_signal;
   sigaction(SIGALRM, &sa, NULL);

   /* process argument */
   progname = argv[0];
   if (argc != 2)
      usage();
   N = strtol(argv[1], NULL, 10);
   if ((N <= 0) || (N > 1000))
      usage();


   /* calculate prime numbers -- simple sieve */
   candidate = 1;
   for (cnt = 0; cnt < N; ++cnt) {

      for (;;) {
         found = 1;
         divisor = 2;
         candidate += 1;

         while (divisor <= candidate/2) {
            if ((candidate % divisor) == 0) {
               found = 0;
               break;
            }
            else
               ++divisor;
         }
         if (found)
            break;
      }
      printf("%ld\n", candidate);
   }

   return 0;
}
