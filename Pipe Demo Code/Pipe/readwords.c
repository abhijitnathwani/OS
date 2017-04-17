#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { MAXLINES = 30 };

int main(void)
{
    int i = 0;
    char lines[MAXLINES][BUFSIZ];
    FILE *fp = fopen("input.txt", "r");

    if (fp == 0)
    {
        fprintf(stderr, "failed to open input.txt\n");
        exit(1);
    }
    while (i < MAXLINES && fgets(lines[i], sizeof(lines[0]), fp))
    {
        lines[i][strlen(lines[i])-1] = '\0';
        i = i + 1;
    }
    fclose(fp);
    printf("%d\n", i);
    srand(time(0));
    int j = rand() % i;
    int k = (j+1) % i;
    for(i=0;i<20;i++)
	printf("%s\n",lines[i]);
//    printf("%s %s\n", lines[j], lines[k]); 
    return 0;
}
