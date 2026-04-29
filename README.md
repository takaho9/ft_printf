*This project has been created as part of the 42 curriculum by ttakemur.*

## Description

`ft_printf` is a partial re-implementation of the C standard library function `printf`.
The goal is to understand variadic functions and produce formatted output by writing
directly to file descriptor 1 via `write`, without relying on any standard I/O functions.

The library is compiled as a static archive `libftprintf.a` and supports the following
conversion specifiers:

| Specifier | Output |
|-----------|--------|
| `%c` | Single character |
| `%s` | String (`NULL` → `(null)`) |
| `%d` / `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` / `%X` | Unsigned hexadecimal (lower / upper case) |
| `%p` | Pointer address in hex (`NULL` → `(nil)`) |
| `%%` | Literal `%` |

The return value is the total number of characters printed, matching the behaviour of
the standard `printf`.

## Instructions

### Compilation

```sh
make        # build libftprintf.a
make re     # full rebuild
make clean  # remove object files
make fclean # remove object files and libftprintf.a
```

### Linking in your project

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o my_program
```

Or reference the archive directly:

```sh
cc main.c libftprintf.a -o my_program
```

### Usage example

```c
#include "src/ft_printf.h"

int main(void)
{
    int n = ft_printf("Hello, %s! dec=%d hex=%x ptr=%p\n",
                      "world", 42, 255, &n);
    ft_printf("chars printed: %d\n", n);
    return (0);
}
```

## Algorithm and Data Structure

### Format string parsing

`ft_printf` performs a single linear scan of the format string character by character.
When a `%` is encountered the next character is consumed immediately and dispatched to
`ft_handle_specifier`, which reads exactly one argument from the `va_list` with the
type expected by that specifier.

This one-pass approach is simple and sufficient for the subset of specifiers required
by the project; no intermediate buffer or state machine is needed.

### Recursive digit extraction

All numeric output functions (`ft_putnbr`, `ft_putunsigned`, `ft_puthex`) use
**tail-first recursion** to print digits in the correct (most-significant-first) order:

```
ft_putnbr(123)
  → ft_putnbr(12) → ft_putnbr(1) → print '1'
                  → print '2'
  → print '3'
```

This avoids allocating a temporary buffer to reverse the digits.
The recursion depth is at most log₁₀(2³¹) ≈ 10 for integers and log₁₆(2⁶⁴) = 16 for
hexadecimal values, so stack usage is negligible.

### Shared `ft_puthex` for `%x`/`%X` and `%p`

`ft_puthex` takes `unsigned long` so that a single function handles both
`unsigned int` values (for `%x`/`%X`) and 64-bit pointer values (for `%p`).
At the call site for `%x`/`%X`, `va_arg` reads `unsigned int` (the type the caller
actually pushed) and the result is widened to `unsigned long` before being passed in —
this avoids undefined behaviour from reading more bytes than were pushed onto the
variadic stack.

### No heap allocation

Every output path calls `write` directly on individual characters or short literals.
No `malloc` is used, so there is no possibility of allocation failure.

## Resources

- `man 3 printf` — specification of the standard `printf` behaviour
- `man 3 stdarg` — `va_list`, `va_start`, `va_arg`, `va_end`
- [cppreference — printf](https://en.cppreference.com/w/c/io/fprintf)
- [cppreference — Variadic functions](https://en.cppreference.com/w/c/variadic)

### AI usage

Claude (claude.ai/code) was used during this project for the following tasks:

- **Code formatting**: running `c_formatter_42` and the 42 header script via the
  `/norm-format` skill to keep all files Norm-compliant.
- **README authoring**: drafting this document based on the project requirements.

All logic, design decisions, and the final implementation were written and reviewed
by the student.
