

#include <unistd.h>

int main(int c, char **v)
{
    int i = 0;
    while (v[1][i] == ' ')
        i++;
    while (v[1][i])
    {
        while (v[1][i] != ' ') {
            write(1, &v[1][i], 1);
            i++;
        }
        if (v[1][i] == ' ') {
            while (v[1][i] == ' ' && v[1][i]) 
                i++;
            write(1, " ", 1);
        }
    }
}