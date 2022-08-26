#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "node.h"
}

TEST(cmd_node_new, base) {
	char	*val = strdup("cat");
	ASSERT_NE((void *)NULL, val);

	t_node *node = cmd_node_new(val);
	ASSERT_EQ(cmd_node, node->type);
	ASSERT_STREQ("cat", (char *)node->value.cmd_val.args->val);

	node_drop(node);
}

TEST(cmd_add_arg, base) {
	char	*val = strdup("cat");
	char	*arg = strdup("file");
	ASSERT_NE((void *)NULL, val);
	ASSERT_NE((void *)NULL, arg);

	t_node *node = cmd_node_new(val);
	ASSERT_EQ(cmd_node, node->type);
	ASSERT_STREQ("cat", (char *)node->value.cmd_val.args->val);

	int i = cmd_add_arg(node, arg);
	ASSERT_NE(-1, i);
	ASSERT_STREQ("file", (char *)node->value.cmd_val.args->next->val);

	node_drop(node);
}

TEST(cmd_change_cmdname, base) {
	char	*val = strdup("cat");
	char 	*n_name = strdup("/usr/bin/cat");
	ASSERT_NE((void *)NULL, val);

	t_node *node = cmd_node_new(val);
	ASSERT_EQ(cmd_node, node->type);
	ASSERT_STREQ("cat", (char *)node->value.cmd_val.args->val);

	cmd_change_cmdname(node, n_name);
	ASSERT_STREQ("/usr/bin/cat", (char *)node->value.cmd_val.args->val);

	node_drop(node);
}