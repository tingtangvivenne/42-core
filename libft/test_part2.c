#include "libft.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* This test program is separate from the library and its Norm rules. */
#ifdef TEST_ALLOC_FAILURE
static int fail_after = -1;
static int live_allocations;
void *__real_malloc(size_t size);
void __real_free(void *ptr);

void *__wrap_malloc(size_t size)
{
	void *ptr;
	if (fail_after == 0)
		return (NULL);
	if (fail_after > 0)
		fail_after--;
	ptr = __real_malloc(size);
	if (ptr)
		live_allocations++;
	return (ptr);
}

void __wrap_free(void *ptr)
{
	if (ptr)
		live_allocations--;
	__real_free(ptr);
}
#endif

static void expect_string(char *actual, const char *expected)
{
	assert(actual != NULL);
	assert(strcmp(actual, expected) == 0);
	free(actual);
}

static char map_char(unsigned int index, char c)
{
	return ((char)(c + index));
}

static void edit_char(unsigned int index, char *c)
{
	*c = map_char(index, *c);
}

static char erase_char(unsigned int index, char c)
{
	(void)c;
	if (index == 0)
		return ('\0');
	return ('x');
}

static void erase_in_place(unsigned int index, char *c)
{
	*c = erase_char(index, *c);
}

static void test_strings(void)
{
	expect_string(ft_substr("hello", 1, 3), "ell");
	expect_string(ft_substr("hello", 2, (size_t)-1), "llo");
	expect_string(ft_substr("hello", 5, 2), "");
	expect_string(ft_substr("hello", UINT_MAX, 2), "");
	expect_string(ft_substr("hello", 0, 0), "");
	expect_string(ft_substr("", 0, 10), "");
	expect_string(ft_strjoin("hello", " world"), "hello world");
	expect_string(ft_strjoin("", "world"), "world");
	expect_string(ft_strjoin("hello", ""), "hello");
	expect_string(ft_strjoin("", ""), "");
	expect_string(ft_strtrim("--hello--", "-"), "hello");
	expect_string(ft_strtrim("xyhello yx", "xy"), "hello ");
	expect_string(ft_strtrim("---", "-"), "");
	expect_string(ft_strtrim("", "-"), "");
	expect_string(ft_strtrim("a-b", ""), "a-b");
	expect_string(ft_strtrim("-a-b-", "-"), "a-b");
	char original[] = "aaa";
	expect_string(ft_strmapi(original, map_char), "abc");
	assert(strcmp(original, "aaa") == 0);
	ft_striteri(original, edit_char);
	assert(strcmp(original, "abc") == 0);
	expect_string(ft_strmapi("", map_char), "");
	char empty[] = "";
	ft_striteri(empty, edit_char);
	assert(empty[0] == '\0');
	char *mapped = ft_strmapi("abc", erase_char);
	assert(mapped && memcmp(mapped, "\0xx", 4) == 0);
	free(mapped);
	ft_striteri(original, erase_in_place);
	assert(memcmp(original, "\0xx", 4) == 0);
	puts("PASS: substring, join, trim and callbacks");
}

static void expect_split(const char *s, char delimiter,
	const char **expected, size_t count)
{
	char **words = ft_split(s, delimiter);
	assert(words);
	for (size_t i = 0; i < count; i++)
	{
		assert(words[i] && strcmp(words[i], expected[i]) == 0);
		free(words[i]);
	}
	assert(words[count] == NULL);
	free(words);
}

static void test_split(void)
{
	const char *three[] = {"one", "two", "three"};
	const char *one[] = {"one,two"};
	expect_split(",one,,two,three,,", ',', three, 3);
	expect_split("one,two", '\0', one, 1);
	expect_split("one,two", 'x', one, 1);
	expect_split("", ',', NULL, 0);
	expect_split(",,,,", ',', NULL, 0);
	expect_split("", '\0', NULL, 0);
	puts("PASS: split, repeated delimiters and empty input");
}

static void test_numbers_and_output(void)
{
	int numbers[] = {INT_MIN, INT_MAX, -100, -10, -1, 0, 1, 10, 100};
	char expected[64], actual[64];
	for (int n = -10000; n <= 10000; n++)
	{
		snprintf(expected, sizeof(expected), "%d", n);
		expect_string(ft_itoa(n), expected);
	}
	for (size_t i = 0; i < sizeof(numbers) / sizeof(*numbers); i++)
	{
		int fds[2];
		int length = snprintf(expected, sizeof(expected), "Xhello\n%d", numbers[i]);
		assert(pipe(fds) == 0);
		ft_putchar_fd('X', fds[1]);
		ft_putstr_fd("hel", fds[1]);
		ft_putstr_fd("", fds[1]);
		ft_putendl_fd("lo", fds[1]);
		ft_putnbr_fd(numbers[i], fds[1]);
		assert(close(fds[1]) == 0);
		ssize_t total = 0, got;
		while ((got = read(fds[0], actual + total, sizeof(actual) - total)) > 0)
			total += got;
		assert(got == 0 && total == length);
		assert(memcmp(actual, expected, (size_t)length) == 0);
		assert(close(fds[0]) == 0);
		snprintf(expected, sizeof(expected), "%d", numbers[i]);
		expect_string(ft_itoa(numbers[i]), expected);
	}
	int fds[2];
	assert(pipe(fds) == 0);
	ft_putchar_fd('\0', fds[1]);
	ft_putendl_fd("", fds[1]);
	close(fds[1]);
	assert(read(fds[0], actual, sizeof(actual)) == 2);
	assert(actual[0] == '\0' && actual[1] == '\n');
	close(fds[0]);
	puts("PASS: itoa and output, including INT_MIN and INT_MAX");
}

#ifdef TEST_ALLOC_FAILURE
static void test_failure(void)
{
	fail_after = 0;
	assert(ft_substr("hello", 1, 3) == NULL);
	assert(ft_substr("hello", 99, 3) == NULL);
	assert(ft_strjoin("a", "b") == NULL);
	assert(ft_strtrim("-a-", "-") == NULL);
	assert(ft_strtrim("---", "-") == NULL);
	assert(ft_itoa(INT_MIN) == NULL);
	assert(ft_strmapi("hello", map_char) == NULL);
	assert(ft_split("", ',') == NULL);
	for (int i = 0; i < 4; i++)
	{
		fail_after = i;
		assert(ft_split("one,two,three", ',') == NULL);
		assert(live_allocations == 0);
	}
	fail_after = -1;
	assert(live_allocations == 0);
	puts("PASS: allocation failure and split cleanup at every allocation");
}
#endif

int main(void)
{
	test_strings();
	test_split();
	test_numbers_and_output();
#ifdef TEST_ALLOC_FAILURE
	test_failure();
#endif
	puts("All Part 2 tests passed.");
	return (0);
}
