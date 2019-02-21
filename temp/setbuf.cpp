 #include <stdio.h>
    int main ()
    {
        FILE * p;
        int c;
        int n = 0;
        p = fopen ("myfile.txt", "r");
        if (p == NULL) 
            perror ("Error opening file");
        else
        {
            do {
                c = getc (p);
                if (c == '$') 
                    n++;
            } while (c != EOF);
            fclose (p);
            printf ("%d\n", n);
        }
        return 0;
    }
