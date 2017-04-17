#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int c1,c2;
	c2 = 0;
   c1 = fork();      /* fork number 1 */
   if (c1 == 0)
      c2 = fork();   /* fork number 2 */
   fork();           /* fork number 3 */
   if (c2 > 0)
      fork();        /* fork number 4 */

   	while(1);
	return 0;
}

