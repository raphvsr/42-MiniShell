

// ◦ pwd with no options

#include "../minishell.h"
#include <stdlib.h>

int b_pwd()
{
    char curr_path[PATH_MAX]; // a changer ? 4096 ?

    if (getcwd(curr_path, sizeof(curr_path)))
    {
        
    }

}
