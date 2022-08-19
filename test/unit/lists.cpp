#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "lists.h"
}

TEST(lists_str_to_char, base) {
	t_list	*head = NULL;
	t_list	*node;
	char	*value;

	value = strdup("cat");
	node = lst_new(value);
	ASSERT_NE((void *)NULL, node);
	lst_add_back(&head, node);
	
	char	**rv = lst_to_char(&head);
	ASSERT_NE((void *)NULL, rv);
	ASSERT_EQ((void *)NULL, head);
	
	ASSERT_EQ(value, *rv);
	ASSERT_STREQ("cat", rv[0]);

	ASSERT_EQ((void *)NULL, rv[1]);

	for (int i = 0; i < 2; i++)
		free(rv[i]);
	free(rv);
}

TEST(lists_str_to_char, null_head) {
	t_list	*head = NULL;
	char	**rv = lst_to_char(&head);
	ASSERT_EQ((void *)NULL, rv);
	ASSERT_EQ((void *)NULL, head);
}

TEST(lists_str_to_char, two_vals) {
	t_list	*head = NULL;
	t_list	*node;
	char	*value;

	value = strdup("cat");
	node = lst_new(value);
	ASSERT_NE((void *)NULL, node);
	lst_add_back(&head, node);
	value = strdup("file");
	node = lst_new(value);
	ASSERT_NE((void *)NULL, node);
	lst_add_back(&head, node);

	char	**rv = lst_to_char(&head);
	ASSERT_NE((void *)NULL, rv);
	ASSERT_EQ((void *)NULL, head);

	ASSERT_STREQ("cat", rv[0]);
	ASSERT_STREQ("file", rv[1]);
	ASSERT_EQ((void *)NULL, rv[2]);

	for (int i = 0; i < 3; i++)
		free(rv[i]);
	free(rv);
}