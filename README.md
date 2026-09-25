# MATH 4175 — Cryptography Project 1

A C++ implementation of the Division Algorithm table used in  
**Virginia Tech MATH 4175: Cryptography**.

This project computes

\[
\gcd(a,b)
\]

and finds integers \(x\) and \(y\) such that

\[
ax + by = \gcd(a,b).
\]

---

## Project Objective

For each required pair of positive integers \(a\) and \(b\), the program:

- creates the Division Algorithm table
- computes \(\gcd(a,b)\)
- finds the corresponding Bézout coefficients \(x\) and \(y\)
- prints the final values in a readable format

The table follows the notation used in the course notes:

\[
u_1,\; v_1,\; u_2,\; v_2,\; u_3,\; v_3,\; q
\]

with the initial row

\[
1,\;0,\;0,\;1,\;a,\;b,\;0.
\]

---

## Required Input Pairs

| # | \(a\) | \(b\) |
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
├── CMakeLists.txt
├── main.cpp
└── README.md
```

### `algo.cpp`

Contains the implementation of the Division Algorithm table and computes the gcd and Bézout coefficients.

### `algo.h`

Contains the declaration for the `findGcd()` function.

### `main.cpp`

Runs the algorithm on the three required input pairs.

### `CMakeLists.txt`

Contains the CMake configuration used to build the project.

---

## Algorithm

The program begins with

\[
u_1=1,\qquad v_1=0
\]

\[
u_2=0,\qquad v_2=1
\]

\[
u_3=a,\qquad v_3=b
\]

and

\[
q=0.
\]

For each new row, the quotient is

\[
q=\left\lfloor\frac{u_3}{v_3}\right\rfloor.
\]

The new \(u\)-values are taken from the previous \(v\)-values:

\[
u_i^{\text{new}}=v_i^{\text{old}}.
\]

The new \(v\)-values are computed by

\[
v_i^{\text{new}}
=
u_i^{\text{old}}
-
qv_i^{\text{old}}.
\]

The process continues until

\[
v_3=0.
\]

At the final row,

\[
\gcd(a,b)=u_3
\]

and the Bézout coefficients are

\[
x=u_1,\qquad y=u_2.
\]

Therefore,

\[
ax+by=\gcd(a,b).
\]

---

## Build

Using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Run

From the build directory:

```bash
./cryptoproj1
```

The program prints a formatted Division Algorithm table for each input pair, followed by the values of

\[
\gcd(a,b),\qquad x,\qquad y.
\]

---

## Output

The program output is used to create the required PDF submission.

The final submission should contain two separate unzipped files:

```text
source_code_file
output_file.pdf
```

The PDF should clearly show the Division Algorithm tables and the final values of

\[
\gcd(a,b),\qquad x,\qquad y
\]

for all three required pairs.
