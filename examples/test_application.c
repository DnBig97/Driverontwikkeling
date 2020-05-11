#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c[1000], i[1000];
    FILE *f, *p;

    if ((p = fopen("/dev/hello_driver", "w")) == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    else
    {
        const char *text = "Tekst of text";
        fprintf(p, "Some text: %s\n", text);
        fclose(p);
    }

    if((f = fopen("/dev/hello_driver", "r")) == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }
    else
    {
        fscanf(f, "%[^/n]", c);
        printf("Data from file:\n%s", c);
        fclose(f);
    }

    return 0;
    
}
