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

## Project Objective

For each required pair of positive integers $a$ and $b$, the program:

- creates the Division Algorithm table used in the course notes
- computes $\gcd(a,b)$
- finds the corresponding Bézout coefficients $x$ and $y$
- prints the results in a formatted table

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
├── main.cpp
└── README.md
```

### `algo.cpp`

Contains the Division Algorithm implementation.

It:

- initializes the $u$, $v$, and $q$ values
- generates each row of the table
- computes the gcd
- finds the Bézout coefficients $x$ and $y$

### `algo.h`

Contains the declaration of the `findGcd()` function.

### `main.cpp`

Runs `findGcd()` for the three required integer pairs.

### `CMakeLists.txt`

Contains the CMake configuration used to compile the project.

### `build/`

Generated automatically by CMake.

It contains the compiled executable and other build files and is not part of the main source code.

---

## Division Algorithm

The program starts with

$$
u_1 = 1,\qquad v_1 = 0
$$

$$
u_2 = 0,\qquad v_2 = 1
$$

$$
u_3 = a,\qquad v_3 = b
$$

and

$$
q = 0.
$$

For each new row, the quotient is computed as

$$
q =
\left\lfloor
\frac{u_3}{v_3}
\right\rfloor.
$$

The previous $v$ values become the new $u$ values:

$$
u_i^{\text{new}} = v_i^{\text{old}}.
$$

The new $v$ values are then calculated by

$$
v_i^{\text{new}}
=
u_i^{\text{old}}
-
qv_i^{\text{old}}.
$$

The process repeats until

$$
v_3 = 0.
$$

At the final row,

$$
\gcd(a,b) = u_3,
$$

and the Bézout coefficients are

$$
x = u_1,\qquad y = u_2.
$$

Therefore,

$$
ax + by = \gcd(a,b).
$$

---

## Build

From the project directory, configure the project with CMake:

```bash
cmake -S . -B build
```

Then compile it:

```bash
cmake --build build
```

A successful build creates the executable:

```text
build/cryptoproj1
```

---

## Run

Run the compiled program with:

```bash
./build/cryptoproj1
```

The program prints a complete Division Algorithm table for each required pair.

---

## Results

The program produces the following final values.

### Pair 1

$$
a = 768336,\qquad b = 78192
$$

$$
\gcd(a,b) = 48
$$

with

$$
x = 236,\qquad y = -2319.
$$

Therefore,

$$
768336(236) + 78192(-2319) = 48.
$$

### Pair 2

$$
a = 494752,\qquad b = 296864
$$

$$
\gcd(a,b) = 32
$$

with

$$
x = 4637,\qquad y = -7728.
$$

Therefore,

$$
494752(4637) + 296864(-7728) = 32.
$$

### Pair 3

$$
a = 17601969,\qquad b = 2364768
$$

$$
\gcd(a,b) = 483
$$

with

$$
x = -1741,\qquad y = 12959.
$$

Therefore,

$$
17601969(-1741) + 2364768(12959) = 483.
$$

---

## Program Output

For each pair, the program prints a table with the columns

```text
u1    v1    u2    v2    u3    v3    q
```

followed by the final values of

$$
\gcd(a,b),\qquad x,\qquad y.
$$

The tables are then used to prepare the required PDF output for the project.

---

## Submission

The project instructions require two separate, unzipped files:

```text
source_code_file
output_file.pdf
```

The PDF output should include:

- the names of all participating group members
- all three Division Algorithm tables
- the value of $\gcd(a,b)$ for each pair
- the corresponding values of $x$ and $y$
- clearly formatted typed output
```

One thing I especially changed is the **Build** section. Since you're actually running:

```bash
cmake -S . -B build
cmake --build build
./build/cryptoproj1
```
