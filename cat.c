#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{  
   gid_t egid = getegid();
   setregid(egid, egid);

   system("cat /etc/passwd");

   return 0;
}
