*This project has been created as part of the 42 curriculum by ttang.*

## Description

Libft is a reusable C library. All 43 functions from subject version 19.3 are
implemented: 23 in Part 1, 11 in Part 2, and 9 linked-list functions in Part 3.
This learning layout still needs flattening before submission.

## File guide: Parts 1, 2 and 3

Source files are grouped into part1/, part2/ and part3/ for learning. Shared files and
local test programs stay at the root. The Makefile builds all three folders into
libft.a; run all commands below from the project root.

Before submission, move the .c files back to the root as required by the
subject, change SRCS in the Makefile to $(PART1_SRCS) $(PART2_SRCS) $(PART3_SRCS), and update
the paths in these instructions. Run make fclean before changing the layout.

```text
part1/       23 libc function implementations
part2/       11 additional function implementations
part3/       9 linked-list function implementations
libft.h      shared declarations
Makefile     builds all three parts
main.c       simple test program
test_part1.c Part 1 tests
test_part2.c Part 2 tests
test_part3.c Part 3 tests
```

### Part 1 - Libc functions (23)

- [ft_isalpha.c](part1/ft_isalpha.c)
- [ft_isdigit.c](part1/ft_isdigit.c)
- [ft_isalnum.c](part1/ft_isalnum.c)
- [ft_isascii.c](part1/ft_isascii.c)
- [ft_isprint.c](part1/ft_isprint.c)
- [ft_strlen.c](part1/ft_strlen.c)
- [ft_memset.c](part1/ft_memset.c)
- [ft_bzero.c](part1/ft_bzero.c)
- [ft_memcpy.c](part1/ft_memcpy.c)
- [ft_memmove.c](part1/ft_memmove.c)
- [ft_strlcpy.c](part1/ft_strlcpy.c)
- [ft_strlcat.c](part1/ft_strlcat.c)
- [ft_toupper.c](part1/ft_toupper.c)
- [ft_tolower.c](part1/ft_tolower.c)
- [ft_strchr.c](part1/ft_strchr.c)
- [ft_strrchr.c](part1/ft_strrchr.c)
- [ft_strncmp.c](part1/ft_strncmp.c)
- [ft_memchr.c](part1/ft_memchr.c)
- [ft_memcmp.c](part1/ft_memcmp.c)
- [ft_strnstr.c](part1/ft_strnstr.c)
- [ft_atoi.c](part1/ft_atoi.c)
- [ft_calloc.c](part1/ft_calloc.c)
- [ft_strdup.c](part1/ft_strdup.c)

### Part 2 - Additional functions (11)

- [ft_substr.c](part2/ft_substr.c)
- [ft_strjoin.c](part2/ft_strjoin.c)
- [ft_strtrim.c](part2/ft_strtrim.c)
- [ft_split.c](part2/ft_split.c)
- [ft_itoa.c](part2/ft_itoa.c)
- [ft_strmapi.c](part2/ft_strmapi.c)
- [ft_striteri.c](part2/ft_striteri.c)
- [ft_putchar_fd.c](part2/ft_putchar_fd.c)
- [ft_putstr_fd.c](part2/ft_putstr_fd.c)
- [ft_putendl_fd.c](part2/ft_putendl_fd.c)
- [ft_putnbr_fd.c](part2/ft_putnbr_fd.c)

### Part 3 - Linked lists (9)

- [ft_lstnew.c](part3/ft_lstnew.c)
- [ft_lstadd_front.c](part3/ft_lstadd_front.c)
- [ft_lstsize.c](part3/ft_lstsize.c)
- [ft_lstlast.c](part3/ft_lstlast.c)
- [ft_lstadd_back.c](part3/ft_lstadd_back.c)
- [ft_lstdelone.c](part3/ft_lstdelone.c)
- [ft_lstclear.c](part3/ft_lstclear.c)
- [ft_lstiter.c](part3/ft_lstiter.c)
- [ft_lstmap.c](part3/ft_lstmap.c)

### Shared files and tests

- [libft.h](libft.h): declarations for all three parts, labeled by part.
- [Makefile](Makefile): builds all three parts into the same libft.a library.
- [main.c](main.c): a simple ft_strlen demonstration (Part 1).
- [test_part1.c](test_part1.c): tests the Part 1 functions.
- [test_part2.c](test_part2.c): tests the Part 2 functions.
- [test_part3.c](test_part3.c): tests linked lists, ownership, and cleanup.

## Instructions

From the project directory, build the library:

```sh
make
```

Run your original, simple string-length demonstration:

```sh
cc -Wall -Wextra -Werror main.c libft.a -o test_libft
./test_libft
```

Run the more extensive Part 1 checks (the program stops if an assertion fails):

```sh
cc -Wall -Wextra -Werror test_part1.c libft.a -o test_part1
./test_part1
```

Run Part 2 tests:

```sh
cc -Wall -Wextra -Werror test_part2.c libft.a -o test_part2
./test_part2
```

Run Part 3 tests:

```sh
cc -Wall -Wextra -Werror test_part3.c libft.a -o test_part3
./test_part3
```

For memory checks, instrument both the tests and all library sources:

```sh
cc -Wall -Wextra -Werror -I. -g -fsanitize=address,undefined test_part1.c part1/ft_*.c part2/ft_*.c part3/ft_*.c -o test_part1_san
./test_part1_san
```

Run each command on its own line. After changing a library function, run make
and recompile your test executable. The Makefile keeps test programs out of
libft.a. main.c and test_part1.c/test_part2.c/test_part3.c are local test files; exclude them
and generated test binaries from your final submission.

`make clean` removes library object files. `make fclean` also removes libft.a.
`make re` rebuilds the library. These commands do not delete test executables.
An unchanged second make does not rebuild. Check library style with:

```sh
norminette part1/ft_*.c part2/ft_*.c part3/ft_*.c libft.h
```

## Library functions

| Group | Functions (all use the ft_ prefix) | Purpose |
| --- | --- | --- |
| Character checks | isalpha, isdigit, isalnum, isascii, isprint | Return exactly 1 or 0 |
| Case conversion | toupper, tolower | Convert ASCII letters; preserve other inputs |
| Length | strlen | Count bytes before the null terminator |
| Memory | memset, bzero | Fill bytes or set them to zero |
| Copying | memcpy, memmove | Copy bytes; memmove supports overlapping regions |
| Memory search/comparison | memchr, memcmp | Search or compare raw bytes |
| String copying | strlcpy, strlcat | Copy/append with a destination-size limit; return attempted length |
| String searching | strchr, strrchr, strnstr | Find characters or a bounded substring |
| String comparison | strncmp | Compare up to n bytes, stopping at a terminator |
| Number conversion | atoi | Read initial whitespace, optional sign, and decimal digits |
| Allocation | calloc, strdup | Allocate zeroed memory or an independent string copy |

Start reading ft_isdigit.c and ft_isalpha.c, then ft_isalnum.c, which reuses
both. Continue with case conversion, memory functions, string functions,
atoi, then allocation. The prototypes in libft.h describe each interface.

Strings need a terminating zero byte. Memory functions instead use an explicit
byte count and can handle embedded zero bytes. Callers must supply valid memory
and sufficient buffer space; arbitrary NULL inputs are not generally valid.
memcpy does not support overlap. atoi requires a result representable as int;
out-of-range input has no portable result. Character classification follows
the ASCII/C-locale behavior used by this project.

calloc checks multiplication overflow. A zero-sized allocation still requests
one byte, giving a freeable non-NULL pointer when allocation succeeds.
calloc and strdup return NULL if malloc fails; the caller owns successful
allocations and must free them. Only these two functions call malloc; other
Part 1 functions use their own logic or other ft_ functions.

## Part 2: what to learn next

| Function | Purpose | Example result |
| --- | --- | --- |
| ft_substr | Allocate a substring from an index | ("hello", 1, 3) becomes "ell" |
| ft_strjoin | Allocate two strings joined together | ("hello", " world") becomes "hello world" |
| ft_strtrim | Remove characters from a set at both ends | ("--hi--", "-") becomes "hi" |
| ft_split | Allocate a NULL-terminated array of words | ("a,,b", ',') becomes {"a", "b", NULL} |
| ft_itoa | Allocate the decimal representation of an int | -42 becomes "-42" |
| ft_strmapi | Apply a callback to each index/character in a new string | Leaves the original string unchanged |
| ft_striteri | Apply a callback to each index/character address | Can change the original string |
| ft_putchar_fd | Write one character | fd 1 writes to standard output |
| ft_putstr_fd | Write a string | Does not add a newline |
| ft_putendl_fd | Write a string followed by a newline | Useful for complete lines |
| ft_putnbr_fd | Write an integer, including INT_MIN | Does not allocate memory |

Read ft_substr first: measure the available text, limit the requested length,
allocate length + 1 bytes, copy the characters, then add the zero terminator.
Next read ft_strjoin and ft_strtrim. Leave ft_split until you understand malloc
and free: it allocates the pointer array and each word separately, and frees
previous allocations if a later allocation fails.

Free each returned string when finished. For split, free each word, then the
array. The callback functions and input strings must be valid; striteri needs
writable storage, such as char text[] = "hello", not a string literal.
A file descriptor is a number identifying an open output destination: 1 is
standard output and 2 is standard error. The output helpers use write.

Part 2 memory and forced-allocation-failure checks (GNU-compatible linker):

```sh
cc -Wall -Wextra -Werror -I. -g -fsanitize=address,undefined test_part2.c part1/ft_*.c part2/ft_*.c part3/ft_*.c -o /tmp/test_part2_san
/tmp/test_part2_san
cc -Wall -Wextra -Werror -I. -g -fsanitize=address,undefined -DTEST_ALLOC_FAILURE test_part2.c part1/ft_*.c part2/ft_*.c part3/ft_*.c -Wl,--wrap=malloc -Wl,--wrap=free -o /tmp/test_part2_failure
/tmp/test_part2_failure
```

## Part 3: understanding linked lists

A node has two members: content points to its data, and next points to the next
node. The last node's next pointer is NULL. An empty list is a NULL head pointer.

```text
head -> [content | next] -> [content | NULL]
```

| Function | Purpose |
| --- | --- |
| ft_lstnew | Allocate a node, store the supplied content pointer, set next to NULL |
| ft_lstadd_front | Add a node before the current head |
| ft_lstsize | Count nodes; returns unsigned int as required by this subject |
| ft_lstlast | Find the last node, or return NULL for an empty list |
| ft_lstadd_back | Append a node to the list |
| ft_lstdelone | Call del on the content, then free only that node |
| ft_lstclear | Delete every node and set the caller's head to NULL |
| ft_lstiter | Call f on each node's content |
| ft_lstmap | Build new nodes with content returned by f; clean up on node allocation failure |

Start with ft_lstnew, then ft_lstsize and ft_lstlast. Functions receiving
`t_list **lst` can change your head pointer: pass `&head` when calling them.
`ft_lstnew` stores the pointer you pass; it does not copy the pointed-to data.
The `del` callback must match how the content was allocated. Use free only for
heap allocations, not string literals or stack variables. When deleting a
single node, repair the surrounding links yourself before calling lstdelone.

Supply valid callbacks. In lstmap, the callback controls whether content is
copied; use independent owned content when both lists will free their contents.
A NULL returned by f is stored as valid content, since generic void pointers
can be NULL. If a new node allocation fails, lstmap calls del on that new
content and clears the new list without freeing the source list.

Run memory checks with forced node-allocation failures:

```sh
cc -Wall -Wextra -Werror -I. -g -fsanitize=address,undefined -DTEST_ALLOC_FAILURE test_part3.c part1/ft_*.c part2/ft_*.c part3/ft_*.c -Wl,--wrap=malloc -Wl,--wrap=free -o /tmp/test_part3_san
/tmp/test_part3_san
```

## Resources

- Supplied Libft subject, version 19.3.
- System manuals: man 3 strlen, man 3 memcpy, man 3 memmove, man 3 calloc,
  man 3 atoi, and the corresponding BSD manuals for strlcpy/strlcat/strnstr.
- Campus Norm documentation.
- AI assistance: explanations of C types, headers, compilation and linking;
  implementation of Parts 1, 2 and 3, Makefile/header updates, test development, and
  documentation. Read and understand each function before evaluation.
