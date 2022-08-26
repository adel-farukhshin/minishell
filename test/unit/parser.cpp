#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "scanner.h"
#include "parser.h"
#include "linked_lists.h"
}

TEST(parser, cmd_without_args) {
	t_src	src;
	src.s = "cat";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	
	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
}

TEST(parser, cmd_with_args) {
	t_src	src;
	src.s = "cat file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	ASSERT_STREQ("file", (char *)cmd->value.cmd_val.args->next->val);
}

TEST(parser, cmd_with_ext_0) {
	t_src	src;
	src.s = "cat $$";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("$$", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	ASSERT_STRNE("$$", (char *)cmd->value.cmd_val.args->next->val);	
}

TEST(parser, cmd_with_ext_1) {
	t_src	src;
	src.s = "cat $?";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("$?", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	ASSERT_STRNE("$?", (char *)cmd->value.cmd_val.args->next->val);	
}

TEST(parser, cmd_with_ext_2) {
	t_src	src;
	src.s = "cat $SHELL";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("$SHELL", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	ASSERT_STREQ("/bin/bash", (char *)cmd->value.cmd_val.args->next->val);	
}

TEST(parser, cmd_with_r_out) {
	t_src	src;
	src.s = "cat > file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(6, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	
	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	ASSERT_EQ(6, *(char *)cmd->value.cmd_val.redirs->key);
	ASSERT_STREQ("file", (char *)cmd->value.cmd_val.redirs->val);
}

TEST(parser, cmd_with_redirs) {
	t_src	src;
	src.s = "cat > file < file >> file << file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(6, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(7, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(8, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(9, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);

	
	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(6, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
	r = r->next;
	ASSERT_EQ(7, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
	r = r->next;
	ASSERT_EQ(8, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
	r = r->next;
	ASSERT_EQ(9,*(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}


// redir tests
TEST(parser, redir_out_without_cmdname_with_sep) {
	t_src	src;
	src.s = "> file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_EQ(6, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(6, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}

TEST(parser, redir_out_without_cmdname_without_sep) {
	t_src	src;
	src.s = ">file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_EQ(6, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(6, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}

TEST(parser, redir_out_without_cmdname_without_fname) {
	t_src	src;
	src.s = ">";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_EQ(6, *(char *)tl->key);
	
	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(error_node, cmd->type);
}

TEST(parser, redir_in_without_cmdname_with_sep) {
	t_src	src;
	src.s = "< file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_EQ(7, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(7, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}

TEST(parser, redir_app_without_cmdname_with_sep) {
	t_src	src;
	src.s = ">> file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_EQ(8, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(8, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}

TEST(parser, redir_ins_without_cmdname_with_sep) {
	t_src	src;
	src.s = "<< file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_EQ(9, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(cmd_node, cmd->type);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(9, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}


TEST(parser, pipe_with_cmd) {
	t_src	src;
	src.s = "cat | grep";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(5, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("grep", (char *)tl->val);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(pipe_node, cmd->type);
}

// redir in the first cmd
TEST(parser, pipe_wit_cmd_with_redir_0) {
	t_src	src;
	src.s = "cat < file | grep";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(7, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(5, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("grep", (char *)tl->val);
	
	t_node *pipe;
	pipe = parse(tok_list);
	ASSERT_EQ(pipe_node, pipe->type);
	t_node *cmd;
	cmd = pipe->value.pipe_val.left;
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(7, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
	cmd = pipe->value.pipe_val.right;
	ASSERT_STREQ("grep", (char *)cmd->value.cmd_val.args->val);
}

// redir in the second cmd
TEST(parser, pipe_with_cmd_with_redir_1)
{
	t_src	src;
	src.s = "cat | grep < file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(5, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("grep", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(7, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	
	t_node *pipe;
	pipe = parse(tok_list);
	ASSERT_EQ(pipe_node, pipe->type);
	t_node *cmd;
	cmd = pipe->value.pipe_val.left;
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	cmd = pipe->value.pipe_val.right;
	ASSERT_STREQ("grep", (char *)cmd->value.cmd_val.args->val);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(7, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}

// redir in both cmds
TEST(parser, pipe_with_cmd_with_redir_2)
{
	t_src	src;
	src.s = "cat < file | grep < file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(7, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(5, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("grep", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(7, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("file", (char *)tl->val);
	
	t_node *pipe;
	pipe = parse(tok_list);
	ASSERT_EQ(pipe_node, pipe->type);
	t_node *cmd;
	cmd = pipe->value.pipe_val.left;
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(7, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);

	cmd = pipe->value.pipe_val.right;
	ASSERT_STREQ("grep", (char *)cmd->value.cmd_val.args->val);
	r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(7, *(char *)r->key);
	ASSERT_STREQ("file", (char *)r->val);
}

TEST(parser, cmd_full_null) {
	t_src	src;
	src.s = " ";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_EQ(1, *(char *)tl->key);

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(error_node, cmd->type);	
}

TEST(parser, pipe_without_cmd_with_redir) {
	t_src	src;
	src.s = "cat | > greeks";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token		*tl = tokenize(&src);
	t_l_list	*tok_list = ll_new((t_blist *)tl);

	// check tl
	ASSERT_STREQ("cat", (char *)tl->val);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(5, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(6, *(char *)tl->key);
	tl = tl->next;
	ASSERT_EQ(1, *(char *)tl->key);
	tl = tl->next;
	ASSERT_STREQ("greeks", (char *)tl->val);

	t_node *pipe;
	pipe = parse(tok_list);
	ASSERT_EQ(pipe_node, pipe->type);

	t_node *cmd;
	cmd = pipe->value.pipe_val.left;
	ASSERT_STREQ("cat", (char *)cmd->value.cmd_val.args->val);

	cmd = pipe->value.pipe_val.right;
	t_blist *r = cmd->value.cmd_val.redirs;
	ASSERT_EQ(6, *(char *)r->key);
	ASSERT_STREQ("greeks", (char *)r->val);
	// check redir
}

