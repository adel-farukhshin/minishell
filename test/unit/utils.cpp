#include <gtest/gtest.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "minishell.h"
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