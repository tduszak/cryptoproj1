# MATH 4175 — Cryptography Project 1

A C++ implementation of the Division Algorithm table from  
**Virginia Tech MATH 4175: Cryptography**.

The program computes

$$
\gcd(a,b)
$$

and finds integers $x$ and $y$ satisfying

$$
ax + by = \gcd(a,b).
$$

---

## Group Members

**Group 5**

- Nguyen Nguyen
- Spencer Steadman
- Tanishqa Gautam
- Tyler Duszak

---

## Project Objective

For each required pair of positive integers $a$ and $b$, the program:

- creates the Division Algorithm table used in the course notes
- computes $\gcd(a,b)$
- finds the corresponding Bézout coefficients $x$ and $y$
- verifies that $ax+by=\gcd(a,b)$
- prints the results in a readable format for the final PDF output

The table follows the class notation

$$
u_1,\;v_1,\;u_2,\;v_2,\;u_3,\;v_3,\;q
$$

with initial row

$$
1,\;0,\;0,\;1,\;a,\;b,\;0.
$$

---

## Required Input Pairs

| # | $a$ | $b$ |
|---|---:|---:|
| 1 | 768336 | 78192 |
| 2 | 494752 | 296864 |
| 3 | 17601969 | 2364768 |

---

## Project Structure

```text
cryptoproj1/
├── algo.cpp
├── algo.h
├── build/
├── CMakeLists.txt
├── division_algorithm
├── division_algorithm.cpp
├── main.cpp
├── project1_output_with_names.txt
├── project1_output.pdf
├── project1_output.txt
├── README.md
└── submission/
    ├── division_algorithm.cpp
    └── project1_output.pdf
```

### `division_algorithm.cpp`

The final standalone source file used for submission.

It contains:

- the Division Algorithm implementation
- the three required input pairs
- the group information
- formatted table output
- the gcd and Bézout coefficients
- verification of $ax+by=\gcd(a,b)$

This file combines the functionality of the original `algo.cpp`, `algo.h`, and `main.cpp` into one source file.

### `project1_output.pdf`

The final typed PDF output containing:

- all group member names
- all three Division Algorithm tables
- the gcd for each pair
- the corresponding values of $x$ and $y$
- verification of each linear combination

### `submission/`

Contains exactly the two files intended for Canvas submission:

```text
submission/
├── division_algorithm.cpp
└── project1_output.pdf
```

These files should be uploaded separately and should not be zipped.

---

## Original C++ Project Files

### `algo.cpp`

Contains the original implementation of the Division Algorithm and table generation.

### `algo.h`

Contains the declaration of the `findGcd()` function.

### `main.cpp`

Runs the original `findGcd()` implementation on the three required pairs.

### `CMakeLists.txt`

Contains the CMake configuration for the original multi-file version of the project.

### `build/`

Generated automatically by CMake.

It contains the compiled executable, object files, cache files, Makefiles, and other build information.

The files inside `build/` are generated files and do not need to be edited manually.

---

## Division Algorithm

The program begins with

$$
u_1=1,\qquad v_1=0
$$

$$
u_2=0,\qquad v_2=1
$$

$$
u_3=a,\qquad v_3=b
$$

and

$$
q=0.
$$

For each new row, the quotient is computed as

$$
q=
\left\lfloor
\frac{u_3}{v_3}
\right\rfloor.
$$

The previous $v$ values become the new $u$ values:

$$
u_i^{\text{new}}=v_i^{\text{old}}.
$$

The new $v$ values are calculated by

$$
v_i^{\text{new}}
=
u_i^{\text{old}}
-
qv_i^{\text{old}}.
$$

The process continues until

$$
v_3=0.
$$

At the final row,

$$
\gcd(a,b)=u_3,
$$

and the Bézout coefficients are

$$
x=u_1,\qquad y=u_2.
$$

Therefore,

$$
ax+by=\gcd(a,b).
$$

---

## Build the Original CMake Project

Configure the project:

```bash
cmake -S . -B build
```

Compile it:

```bash
cmake --build build
```

Run it:

```bash
./build/cryptoproj1
```

---

## Build the Final Standalone Program

The final submission source file can also be compiled directly:

```bash
g++ -std=c++17 division_algorithm.cpp -o division_algorithm
```

Run it normally:

```bash
./division_algorithm
```

Or save the complete program output to a text file:

```bash
./division_algorithm > project1_output.txt
```

---

## Results

### Pair 1

$$
a=768336,\qquad b=78192
$$

$$
\gcd(a,b)=48
$$

with

$$
x=236,\qquad y=-2319.
$$

Verification:

$$
768336(236)+78192(-2319)=48.
$$

### Pair 2

$$
a=494752,\qquad b=296864
$$

$$
\gcd(a,b)=32
$$

with

$$
x=4637,\qquad y=-7728.
$$

Verification:

$$
494752(4637)+296864(-7728)=32.
$$

### Pair 3

$$
a=17601969,\qquad b=2364768
$$

$$
\gcd(a,b)=483
$$

with

$$
x=-1741,\qquad y=12959.
$$

Verification:

$$
17601969(-1741)+2364768(12959)=483.
$$

---

## Program Output

For each pair, the program prints a table with the columns

```text
u1          v1          u2          v2          u3          v3           q
```

The final row has

$$
v_3=0,
$$

so the program reports

$$
\gcd(a,b)=u_3,
$$

with

$$
x=u_1,\qquad y=u_2.
$$

It also prints a verification showing that

$$
ax+by=\gcd(a,b).
$$

---

## Create the PDF Output

The program output can be saved with

```bash
./division_algorithm > project1_output.txt
```

On macOS, the text output can be converted to PDF with

```bash
cupsfilter -m application/pdf project1_output.txt > project1_output.pdf
```

The generated PDF can be checked with

```bash
file project1_output.pdf
```

and opened with

```bash
open project1_output.pdf
```

---

## Final Submission

The project instructions require two separate, unzipped files.

The final submission files are:

```text
division_algorithm.cpp
project1_output.pdf
```

A clean copy of both files is stored in:

```text
submission/
├── division_algorithm.cpp
└── project1_output.pdf
```

The files should be uploaded to Canvas individually rather than submitting the `submission/` folder as a ZIP archive.