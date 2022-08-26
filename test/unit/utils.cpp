#include <gtest/gtest.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "minishell.h"
#include "utils.h"
}

// void	ft_strncpy(char *dst, const char *src, long len)

TEST(strncpy, copy_base) {
	const char	*src = "cat";
	char		*dst = (char *)malloc(strlen((src) + 1));
	ft_strncpy(dst, src, (long)strlen(src));
	ASSERT_STREQ("cat", dst);
	free(dst);
}

TEST(strncpy, copy_len_zero) {
	const char	*src = "";
	char		*dst = (char *)malloc(strlen((src) + 1));
	ft_strncpy(dst, src, (long)strlen(src));
	ASSERT_STREQ("", dst);
	free(dst);
}

TEST(free_strs, base) {
	char	**strs = (char **) malloc(sizeof(char *) * 3);
	ASSERT_NE((void*)NULL, (void *) strs);
	strs[0] = strdup("cat");
	ASSERT_NE((void*)NULL, (void *) strs[0]);
	strs[1] = strdup("file");
	ASSERT_NE((void*)NULL, (void *) strs[1]);
	strs[2] = NULL;

	char	*tmp = strs[0];
	free_strs(&strs);
	ASSERT_EQ(NULL, strs);
}