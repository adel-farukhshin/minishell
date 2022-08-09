#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "scanner.h"
}

TEST(scanner, return_dest) {
	t_src	src;
	src.s = "cat > greeks";
	src.curpos = 0;
	src.len = strlen(src.s);
	void	*rv = tokenize(&src);
	ASSERT_NE(rv, &src);
	ASSERT_NE(rv, (void *)NULL);
}

TEST(scanner, tok_sep_space) {
	t_src	src;
	src.s = " ";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(1, *(char *)r->key);
}

TEST(scanner, tok_sep_tab) {
	t_src	src;
	src.s = "	";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(1, *(char *)r->key);
}

TEST(scanner, tok_sep_sp_and_tab) {
	t_src	src;
	src.s = " 	";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(1, *(char *)r->key);
}

TEST(scanner, tok_word) {
	t_src	src;
	src.s = "word";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(2, *(char *)r->key);
	ASSERT_STREQ("word", (char *)r->val);
}

TEST(scanner, tok_field) {
	t_src	src;
	src.s = "\'field\'";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(3, *(char *)r->key);
	ASSERT_STREQ("field", (char *)r->val);
}

TEST(scanner, tok_field_with_sp) {
	t_src	src;
	src.s = "\'fie ld\'";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(3, *(char *)r->key);
	ASSERT_STREQ("fie ld", (char *)r->val);
}

TEST(scanner, tok_ext_field) {
	t_src	src;
	src.s = "\"ext_field\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("ext_field", (char *)r->val);
}

TEST(scanner, tok_ext_field_with_sp) {
	t_src	src;
	src.s = "\"ext_fie ld\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("ext_fie ld", (char *)r->val);
}

TEST(scanner, tok_ext_field_with_ext_p) {
	t_src	src;
	src.s = "\"$$\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("$$", (char *)r->val);
}

TEST(scanner, tok_ext_field_with_ext_e) {
	t_src	src;
	src.s = "\"$?\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("$?", (char *)r->val);
}

TEST(scanner, tok_ext_field_with_ext_v) {
	t_src	src;
	src.s = "\"$a\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("$a", (char *)r->val);
}

TEST(scanner, tok_ext_field_with_ext_and_ch_p) {
	t_src	src;
	src.s = "\"a$$\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("a$$", (char *)r->val);
}

TEST(scanner, tok_ext_field_with_ext_and_ch_e) {
	t_src	src;
	src.s = "\"a$?\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("a$?", (char *)r->val);
}

TEST(scanner, tok_ext_field_with_ext_and_ch_v) {
	t_src	src;
	src.s = "\"a$a\"";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(4, *(char *)r->key);
	ASSERT_STREQ("a$a", (char *)r->val);
}


TEST(scanner, tok_pipe) {
	t_src	src;
	src.s = "|";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(5, *(char *)r->key);
}

TEST(scanner, tok_redir_out) {
	t_src	src;
	src.s = ">";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(6, *(char *)r->key);
}

TEST(scanner, tok_redir_in) {
	t_src	src;
	src.s = "<";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(7, *(char *)r->key);
}

TEST(scanner, tok_redir_append) {
	t_src	src;
	src.s = ">>";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(8, *(char *)r->key);
}

TEST(scanner, tok_redir_insource) {
	t_src	src;
	src.s = "<<";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r;
	r = tokenize(&src);
	ASSERT_EQ(9, *(char *)r->key);
}

TEST(scanner, cmd) {
	t_src	src;
	src.s = "cat file";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r, *r1, *r2;
	r = tokenize(&src);
	ASSERT_EQ(2, *(char *)r->key);
	ASSERT_STREQ("cat", (char *)r->val);
	
	r1 = r->next;
	ASSERT_NE((void *)NULL, r1);
	ASSERT_EQ(1, *(char *)r1->key);

	r2 = r1->next;
	ASSERT_NE((void *)NULL, r2);
	ASSERT_EQ(2, *(char *)r2->key);
	ASSERT_STREQ("file", (char *)r2->val);
}

TEST(scanner, cmd_pipe_with_cmd) {
	t_src	src;
	src.s = "cat | echo";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r, *r1, *r2, *r3, *r4;
	r = tokenize(&src);
	ASSERT_EQ(2, *(char *)r->key);
	ASSERT_STREQ("cat", (char *)r->val);
	
	r1 = r->next;
	ASSERT_NE((void *)NULL, r1);
	ASSERT_EQ(1, *(char *)r1->key);

	r2 = r1->next;
	ASSERT_NE((void *)NULL, r2);
	ASSERT_EQ(5, *(char *)r2->key);
	
	r3 = r2->next;
	ASSERT_NE((void *)NULL, r3);
	ASSERT_EQ(1, *(char *)r3->key);
	
	r4 = r3->next;
	ASSERT_NE((void *)NULL, r4);
	ASSERT_EQ(2, *(char *)r4->key);
	ASSERT_STREQ("echo", (char *)r4->val);
}

TEST(scanner, cmd_pipe_without_cmd) {
	t_src	src;
	src.s = "cat |";
	src.curpos = 0;
	src.len = strlen(src.s);
	t_token	*r, *r1, *r2;
	r = tokenize(&src);
	ASSERT_EQ(2, *(char *)r->key);
	ASSERT_STREQ("cat", (char *)r->val);
	
	r1 = r->next;
	ASSERT_NE((void *)NULL, r1);
	ASSERT_EQ(1, *(char *)r1->key);

	r2 = r1->next;
	ASSERT_NE((void *)NULL, r2);
	ASSERT_EQ(5, *(char *)r2->key);
}

// "\"a$?\" \"$$\""