*This project has been created as part of the 42 curriculum by joaocast.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard library function `printf`, written from scratch in C as part of the 42 curriculum. The goal is to learn how variadic functions work (`<stdarg.h>`), how to parse a format string, and how to structure a small library into clean, reusable pieces. The result is compiled into a static library, `libftprintf.a`, that can be linked into other projects.

The prototype is:

```c
int ft_printf(const char *format, ...);
```

It writes to the standard output and returns the number of characters printed, like the original `printf`.

### Supported conversions

| Specifier | Output |
|-----------|--------|
| `%c` | A single character |
| `%s` | A string (`(null)` if the pointer is `NULL`) |
| `%p` | A pointer in hexadecimal, prefixed with `0x` (`(nil)` if `NULL`) |
| `%d` / `%i` | A signed decimal integer |
| `%u` | An unsigned decimal integer |
| `%x` | An unsigned integer in lowercase hexadecimal |
| `%X` | An unsigned integer in uppercase hexadecimal |
| `%%` | A literal percent sign |

## Instructions

### Compilation

From the root of the repository:

```sh
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # rebuilds everything from scratch
```

The code is compiled with `cc -Wall -Wextra -Werror`.

### Usage

Include the header in your code and link against the library:

```c
#include "ft_printf.h"

int main(void)
{
    int ret;

    ret = ft_printf("Char: %c | Str: %s | Ptr: %p\n", 'A', "ola", "ola");
    ft_printf("Int: %d | Unsigned: %u | Hex: %x | %X | %%\n", -42, 42, 255, 255);
    ft_printf("Printed %d characters\n", ret);
    return (0);
}
```

```sh
cc main.c -L. -lftprintf -o test
./test
```

### Testing

The output and, just as importantly, the **return value** of `ft_printf` can be compared against the real `printf`:

```c
int a = printf("Hex: %x | %X | %%\n", 255, 255);
int b = ft_printf("Hex: %x | %X | %%\n", 255, 255);
// a and b must be equal, and both lines must be identical
```

## Algorithm and data structures

### Overall approach

`ft_printf` does a **single linear pass** over the format string:

1. Initialize a `va_list` with `va_start`.
2. Walk the string character by character.
3. If the character is not `%`, write it and add 1 to the counter.
4. If it is `%`, look at the next character and dispatch to the function that handles that conversion, using `va_arg` to fetch the argument with the right type.
5. Add the value returned by that function to the counter.
6. Call `va_end` and return the counter.

**Why this approach:** the mandatory part only needs a fixed set of single-character conversions, so a one-pass scan with a small dispatcher (`if / else if` on the specifier) is the simplest correct solution. It is easy to read, easy to extend with a new specifier, and needs no extra memory.

### Counting printed characters

Every helper (`ft_putchar`, `ft_putstr`, `ft_putnbr`, `ft_putunsigned`, `ft_puthex`, `ft_putptr`) **returns the number of bytes it wrote**, and the dispatcher accumulates those values into a single `len`. This is what makes the return value of `ft_printf` correct without a global variable and without having to compute the length of the output beforehand.

### Number conversion by recursion

Numbers are printed with a **recursive function** that divides by the base (10 or 16) until a single digit remains, and writes the digits on the way back up the call stack:

```c
if (n >= base)
    len += ft_put...(n / base);   // digits that come before
len += write(1, &digit, 1);       // this digit
```

**Why recursion:** converting a number to a base produces the digits from least to most significant, but they must be printed in the opposite order. Recursion gives the correct order for free, with no temporary buffer, no `malloc`, and no string reversal. Each call has its own local counter, so the value returned by the deepest call propagates up and the total is the number of digits.

- **`%d` / `%i`:** the sign is written first, then the magnitude is printed as an `unsigned int` (`-(unsigned int)n`). This avoids overflow on `INT_MIN`.
- **`%x` / `%X`:** a base string (`"0123456789abcdef"` or `"0123456789ABCDEF"`) is used as a lookup table, selected by the specifier. This replaces any `if (digit < 10)` logic with a single index.
- **`%p`:** the pointer is cast to `uintptr_t`, so the full address width is preserved (a plain `unsigned int` would truncate 64-bit addresses). It is printed with the `0x` prefix. A `NULL` pointer prints `(nil)`, matching glibc on Linux.

### Data structures

No dynamic data structures are needed:

- `va_list` to walk the variadic arguments.
- A constant string used as a digit lookup table for hexadecimal.
- An `int` counter for the number of characters written.

**Trade-off:** characters are written with one `write` call each, which is simpler but slower than building a buffer and flushing it once. For the scope of this project (correctness, return value and clarity), the simplicity was preferred over buffering. Strings are the exception: their length is computed first and they are written with a single `write`.

## Resources

### References

- `man 3 printf`: behavior and return value of the original function.
- `man 3 stdarg`: `va_start`, `va_arg`, `va_end`, `va_list`.
- `man 2 write`: behavior and return value of `write`.
- [GNU C Library manual: Variadic Functions](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)
- [cppreference: `printf`](https://en.cppreference.com/w/c/io/fprintf)
- [cppreference: Variadic arguments](https://en.cppreference.com/w/c/variadic)

### Use of AI

AI (Claude) was used as a support tool during development, **not** to write the project from scratch. It was used for:

- **Code review and debugging:** reviewing small helper functions (`ft_putstr`, `ft_puthex`, `ft_putptr`) and helping interpret the failing test output. This led to finding that several helpers were not returning the number of characters written, and that a recursive call was discarding its return value.
- **Explanations:** clarifying how the recursive counting works and why each call has its own local counter, and the difference between putting a function in a header versus only its prototype.
- **Documentation:** helping draft this README.

All code was written, understood and tested by the author, and the final behavior was checked against the real `printf`.