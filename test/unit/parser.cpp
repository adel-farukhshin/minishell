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

// redir tests

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

// TEST(parser, pipe_with_cmd_with_redir_0)
// redir in first cmd
// TEST(parser, pipe_with_cmd_with_redir_1)
// in the second
// TEST(parser, pipe_with_cmd_with_redir_2)
// in the third

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

	t_node *cmd;
	cmd = parse(tok_list);
	ASSERT_EQ(pipe_node, cmd->type);
	// check redir
}

