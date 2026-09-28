#include "libft.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standalone test program; not part of the library. */
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

static unsigned int deleted;
static unsigned int visited;

static void delete_content(void *content)
{
	deleted++;
	free(content);
}

static void visit(void *content)
{
	visited++;
	if (content)
		((char *)content)[0] = (char)ft_toupper(((char *)content)[0]);
}

static void *copy_upper(void *content)
{
	char *copy = ft_strdup(content);
	assert(copy);
	for (size_t i = 0; copy[i]; i++)
		copy[i] = (char)ft_toupper(copy[i]);
	return (copy);
}

static void *null_content(void *content)
{
	(void)content;
	return (NULL);
}

static t_list *new_word(const char *text)
{
	char *word = ft_strdup(text);
	assert(word);
	t_list *node = ft_lstnew(word);
	assert(node);
	assert(node->content == word && node->next == NULL);
	return (node);
}

static void test_basics(void)
{
	t_list *list = NULL;
	assert(ft_lstsize(list) == 0);
	assert(ft_lstlast(list) == NULL);
	assert(ft_lstmap(list, copy_upper, delete_content) == NULL);
	ft_lstiter(list, visit);
	assert(visited == 0);
	ft_lstclear(&list, delete_content);
	assert(list == NULL && deleted == 0);
	t_list *middle = new_word("two");
	ft_lstadd_back(&list, middle);
	assert(list == middle && ft_lstlast(list) == middle);
	t_list *first = new_word("one");
	ft_lstadd_front(&list, first);
	t_list *last = new_word("three");
	ft_lstadd_back(&list, last);
	assert(list == first && first->next == middle && middle->next == last);
	assert(ft_lstsize(list) == 3 && ft_lstlast(list) == last);
	ft_lstiter(list, visit);
	assert(visited == 3);
	assert(strcmp(first->content, "One") == 0);
	assert(strcmp(middle->content, "Two") == 0);
	assert(strcmp(last->content, "Three") == 0);
	/* Detach the deleted node; lstdelone does not repair list links. */
	first->next = last;
	ft_lstdelone(middle, delete_content);
	assert(deleted == 1 && strcmp(last->content, "Three") == 0);
	assert(ft_lstsize(list) == 2);
	ft_lstclear(&list, delete_content);
	assert(list == NULL && deleted == 3);
	ft_lstclear(&list, delete_content);
	assert(deleted == 3);
	list = ft_lstnew(NULL);
	assert(list && list->content == NULL && list->next == NULL);
	ft_lstclear(&list, delete_content);
	assert(list == NULL && deleted == 4);
	/* Front insertion also works on an empty list. */
	first = new_word("first");
	ft_lstadd_front(&list, first);
	assert(list == first && list->next == NULL);
	ft_lstclear(&list, delete_content);
	puts("PASS: creation, insertion, size, last, iteration and deletion");
}

static void test_map(void)
{
	t_list *list = new_word("one");
	ft_lstadd_back(&list, new_word("two"));
	ft_lstadd_back(&list, new_word("three"));
	t_list *mapped = ft_lstmap(list, copy_upper, delete_content);
	assert(mapped && ft_lstsize(mapped) == 3);
	t_list *src = list;
	t_list *dst = mapped;
	const char *expected[] = {"ONE", "TWO", "THREE"};
	for (size_t i = 0; i < 3; i++)
	{
		assert(src != dst && src->content != dst->content);
		assert(strcmp(dst->content, expected[i]) == 0);
		assert(((char *)src->content)[0] >= 'a');
		src = src->next;
		dst = dst->next;
	}
	assert(src == NULL && dst == NULL);
	ft_lstclear(&mapped, delete_content);
	assert(ft_lstsize(list) == 3);
	mapped = ft_lstmap(list, null_content, delete_content);
	assert(ft_lstsize(mapped) == 3);
	for (dst = mapped; dst; dst = dst->next)
		assert(dst->content == NULL);
	ft_lstclear(&mapped, delete_content);
#ifdef TEST_ALLOC_FAILURE
	int baseline = live_allocations;
	for (int i = 0; i < 3; i++)
	{
		/* Each callback allocation succeeds; the following node fails. */
		unsigned int before = deleted;
		fail_after = 2 * i + 1;
		assert(ft_lstmap(list, copy_upper, delete_content) == NULL);
		assert(live_allocations == baseline);
		assert(deleted - before == (unsigned int)i + 1);
		assert(ft_lstsize(list) == 3);
		assert(strcmp(list->content, "one") == 0);
		fail_after = -1;
	}
	fail_after = 0;
	assert(ft_lstnew(list->content) == NULL);
	assert(live_allocations == baseline);
	fail_after = -1;
	puts("PASS: failed node allocations clean all new content and nodes");
#endif
	ft_lstclear(&list, delete_content);
	puts("PASS: independent mapped list, source preservation and NULL content");
}

int main(void)
{
	test_basics();
	test_map();
#ifdef TEST_ALLOC_FAILURE
	assert(live_allocations == 0);
#endif
	puts("All Part 3 tests passed.");
	return (0);
}
