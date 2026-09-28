#include "libft.h"
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sign_of(int value)
{
	return ((value > 0) - (value < 0));
}

static void test_characters(void)
{
	for (int c = -1; c <= 255; c++)
	{
		assert(ft_isalpha(c) == !!isalpha(c));
		assert(ft_isdigit(c) == !!isdigit(c));
		assert(ft_isalnum(c) == !!isalnum(c));
		assert(ft_isascii(c) == (c >= 0 && c <= 127));
		assert(ft_isprint(c) == !!isprint(c));
		assert(ft_toupper(c) == toupper(c));
		assert(ft_tolower(c) == tolower(c));
	}
	puts("PASS: character checks and case conversion");
}

static void test_memory(void)
{
	unsigned char a[64], b[64], source[64];
	for (size_t i = 0; i < sizeof(source); i++)
		source[i] = (unsigned char)(i * 17);
	for (size_t n = 0; n <= sizeof(a); n++)
	{
		memset(a, 0x5a, sizeof(a));
		memset(b, 0x5a, sizeof(b));
		assert(ft_memset(a, 300, n) == a);
		memset(b, 300, n);
		assert(memcmp(a, b, sizeof(a)) == 0);
		ft_bzero(a, n);
		memset(b, 0, n);
		assert(memcmp(a, b, sizeof(a)) == 0);
		assert(ft_memcpy(a, source, n) == a);
		memcpy(b, source, n);
		assert(memcmp(a, b, sizeof(a)) == 0);
		for (int c = -1; c <= 256; c++)
			assert(ft_memchr(source, c, n) == memchr(source, c, n));
		assert(ft_memcmp(a, b, n) == 0);
		if (n)
		{
			b[n - 1] ^= 255;
			assert(sign_of(ft_memcmp(a, b, n)) == sign_of(memcmp(a, b, n)));
		}
	}
	for (size_t from = 0; from < 16; from++)
		for (size_t to = 0; to < 16; to++)
			for (size_t n = 0; n <= 32; n++)
			{
				memcpy(a, source, sizeof(a));
				memcpy(b, source, sizeof(b));
				assert(ft_memmove(a + to, a + from, n) == a + to);
				memmove(b + to, b + from, n);
				assert(memcmp(a, b, sizeof(a)) == 0);
			}
	puts("PASS: memory operations, including overlapping moves");
}

static void test_strings(void)
{
	const char *strings[] = {"", "a", "hello", "hello world", "aaaa", "\200\377"};
	for (size_t i = 0; i < sizeof(strings) / sizeof(*strings); i++)
	{
		const char *s = strings[i];
		assert(ft_strlen(s) == strlen(s));
		for (int c = -1; c <= 256; c++)
		{
			assert(ft_strchr(s, c) == strchr(s, c));
			assert(ft_strrchr(s, c) == strrchr(s, c));
		}
		for (size_t j = 0; j < sizeof(strings) / sizeof(*strings); j++)
			for (size_t n = 0; n < 16; n++)
				assert(sign_of(ft_strncmp(s, strings[j], n)) ==
					sign_of(strncmp(s, strings[j], n)));
		for (size_t capacity = 0; capacity < 16; capacity++)
		{
			char actual[32], expected[32];
			memset(actual, 'X', sizeof(actual));
			memset(expected, 'X', sizeof(expected));
			if (capacity)
			{
				size_t copied = strlen(s);
				if (copied >= capacity)
					copied = capacity - 1;
				memcpy(expected, s, copied);
				expected[copied] = '\0';
			}
			assert(ft_strlcpy(actual, s, capacity) == strlen(s));
			assert(memcmp(actual, expected, sizeof(actual)) == 0);
			for (size_t d = 0; d < 12; d++)
			{
				memset(actual, 'X', sizeof(actual));
				memset(expected, 'X', sizeof(expected));
				actual[d] = '\0';
				expected[d] = '\0';
				if (d < capacity)
				{
					size_t copied = strlen(s);
					if (copied > capacity - d - 1)
						copied = capacity - d - 1;
					memcpy(expected + d, s, copied);
					expected[d + copied] = '\0';
				}
				assert(ft_strlcat(actual, s, capacity) ==
					(d < capacity ? d : capacity) + strlen(s));
				assert(memcmp(actual, expected, sizeof(actual)) == 0);
			}
		}
		for (size_t j = 0; j < sizeof(strings) / sizeof(*strings); j++)
			for (size_t n = 0; n < 16; n++)
			{
				const char *expected = strstr(s, strings[j]);
				if (*strings[j] && expected &&
					(size_t)(expected - s) + strlen(strings[j]) > n)
					expected = NULL;
				assert(ft_strnstr(s, strings[j], n) == expected);
			}
	}
	char bounded[3] = {'a', 'b', 'c'};
	assert(ft_strnstr(bounded, "bc", 3) == bounded + 1);
	assert(ft_strnstr(bounded, "bcd", 3) == NULL);
	assert(ft_strnstr(bounded, "", 0) == bounded);
	puts("PASS: strings, truncation, terminators and bounded searches");
}

static void test_allocation_and_numbers(void)
{
	const char *inputs[] = {"", "0", "-0", "42", " \t\n\v\f\r-42tail", "+23",
		"+-2", "--2", "abc", "2147483647", "-2147483648", "0000123"};
	for (size_t i = 0; i < sizeof(inputs) / sizeof(*inputs); i++)
	{
		assert(ft_atoi(inputs[i]) == atoi(inputs[i]));
		char *copy = ft_strdup(inputs[i]);
		assert(copy && copy != inputs[i]);
		assert(strcmp(copy, inputs[i]) == 0);
		copy[0] = '\0';
		free(copy);
	}
	for (int n = -10000; n <= 10000; n++)
	{
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "%d", n);
		assert(ft_atoi(buffer) == n);
	}
	for (size_t count = 0; count < 20; count++)
		for (size_t size = 0; size < 20; size++)
		{
			unsigned char *memory = ft_calloc(count, size);
			assert(memory);
			for (size_t j = 0; j < count * size; j++)
				assert(memory[j] == 0);
			free(memory);
		}
	void *a = ft_calloc(0, 12);
	void *b = ft_calloc(12, 0);
	assert(a && b && a != b);
	free(a);
	free(b);
	assert(ft_calloc((size_t)-1, 2) == NULL);
	assert(ft_calloc(2, (size_t)-1) == NULL);
	puts("PASS: atoi, strdup, calloc and allocation-size overflow");
}

int main(void)
{
	test_characters();
	test_memory();
	test_strings();
	test_allocation_and_numbers();
	puts("All Part 1 tests passed.");
	return (0);
}
