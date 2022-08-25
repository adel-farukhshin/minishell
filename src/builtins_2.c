#include "builtins.h"

void    cd_cmd(t_shell   *shell)
{
    (void) shell;
    char    old_pwd[PATH_MAX + 1];
    char    new_pwd[PATH_MAX + 1];
    
    (void)old_pwd;
    (void)new_pwd;

    chdir("..");
    // pwd_cmd();
}
