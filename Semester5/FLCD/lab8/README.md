# Lab 8 – GenAI to C (Mini DSL)
We used GenAI to translate a simple DSL program into C code, validated it, and compared it to our yacc/Bison baseline from Lab 6. This was a team project: I handled the GenAI prompting, and my partner did the validation and comparison.

## R1: Prompt used
```
You are translating a tiny DSL into plain C. Keep the logic identical.
DSL features: variable declarations (int/float/string/char), assignments, read/write, arithmetic (+ - * / %), comparisons (== != < > <= >=), if/else, while, and two geometry functions: pythagoras(x, y) returns sqrt(x*x + y*y); area_triangle(b, h) returns 0.5 * b * h.
Input DSL program:
```
float a;
read(a);
float b;
read(b);
write("Hypotenuse is: ");
write(pythagoras(a, b));
write("Area of triangle is: ");
write(area_triangle(a, b));
```
Please produce a single C file that:
1) Preserves the program’s behavior.
2) Uses stdio.h/math.h (no external libs).
3) Implements pythagoras and area_triangle if they are called.
4) Reads/writes via scanf/printf with sensible formats.
5) Adds minimal, clear comments (no fluff).
After the code, briefly explain:
- What inputs are read.
- What outputs are printed and in what order.
- Any assumptions you made (e.g., scanf format).
```
GenAI output: `src/geometry_program.c`.

## R2: Validation
- Build: `gcc -std=c11 -Wall -Wextra -lm src/geometry_program.c -o geometry_program`
- Run: `./geometry_program` with input `3 4`
- Output:
  ```
  Hypotenuse is: 5.000000
  Area of triangle is: 6.000000
  ```
- No warnings or fixes needed.

## R3: Comparison with yacc/Bison
- Baseline: lab6 Bison parser accepts the same DSL (see `productions.txt` in this folder).
- The baseline is syntax-only; it confirms the DSL is valid.
- GenAI C runs correctly and matches expected behavior. No differences observed on tested input (`3 4`).

## Files
- `src/geometry_program.c` – GenAI-produced C
- `productions.txt` – derivation from the Bison parser for the same DSL input