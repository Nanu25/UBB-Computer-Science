# Lab 9 – GenAI code optimization

We started from the GenAI-produced C program in `lab8/src/geometry_program.c` (translation of the Mini DSL that reads two numbers and prints the hypotenuse and area of a right triangle). For Lab 9, we used GenAI again to **optimize** that C code, focusing on readability and numeric precision, without changing the program’s behavior.

## Prompt used for optimization

The following prompt was given to GenAI to obtain the optimized version:

```
You are improving a small C program that was generated from a tiny DSL.
The current C code is in lab8/src/geometry_program.c and is functionally correct.

Goals:
- Keep the program’s behavior identical (same inputs and outputs).
- Replace all float values and functions with double for better numerical precision.
- Rename generic variables a and b to more descriptive names that reflect right-triangle legs.
- Optionally introduce small helper functions to reduce duplication and improve readability.
- Keep using stdio.h and math.h only.

Please show the revised C code and briefly explain the main readability and naming improvements you made.
```

## Optimized code

- Original code: `lab8/src/geometry_program.c`
- Optimized code: `lab9/geometry_program_optimized.c`

Both programs:
- Read two numeric inputs (the legs of a right triangle) from standard input.
- Print the hypotenuse.
- Print the area of the right triangle.

## Differences between original and optimized version

- **Numeric type**
  - Original: used `float` and `sqrtf`, with `scanf("%f", &a)` / `scanf("%f", &b)` and `printf("%f", ...)`.
  - Optimized: uses **`double`** everywhere and `sqrt`, with `scanf("%lf", &leg_a)` / `scanf("%lf", &leg_b)` and `printf("%.2f", ...)` for nicer formatting.

- **Variable names**
  - Original: generic names `a` and `b` for the two inputs.
  - Optimized: more descriptive names **`leg_a`** and **`leg_b`**, matching the right-triangle interpretation.

- **Helper function and readability**
  - Original: duplicated input-reading logic for `a` and `b` with inline `scanf` and error checks.
  - Optimized: introduces a small helper function `read_double(const char *name, double *value)` that performs the `scanf` and error message in one place, reducing duplication and making `main` easier to read.
  - Added short comments that connect the C code back to the DSL operations (`read`, `write`, `pythagoras`, `area_triangle`).

- **Behavior**
  - The **logical behavior is unchanged**: same inputs, same mathematical computations (hypotenuse and area).
  - Output is now formatted with two decimal places, but the values themselves are equivalent (just displayed more cleanly).


