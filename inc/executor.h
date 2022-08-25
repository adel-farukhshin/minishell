#ifndef EXECUTOR_H
#define EXECUTIR_H
#include "minishell.h"
#include "node.h"

int    exec_node(t_node *cmd, t_context   *ctx, t_shell    *shell);
int    execute_cmd(t_node    *cmd, t_context *ctx, t_shell    *shell);
int    execute_pipe(t_node    *cmd, t_context *ctx, t_shell    *shell);
int    executor(t_node *cmd, t_shell    *shell);
#endif