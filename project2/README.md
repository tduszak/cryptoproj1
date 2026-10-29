# Project 2 — Vigenere Cipher

## Status and Scope

This directory prepares Project 2 without solving it. The C++17 scaffold reads the supplied ciphertext, validates uppercase A-Z input with optional whitespace, and reports the normalized character count. It does not calculate coincidence indices, recover a keyword, or decrypt text yet.

Project 1 source, saved outputs, and submission files are preserved under `../project1/` without content changes. Its Euclidean algorithm is not reused for Vigenere analysis. Return to the [repository overview](../README.md) for the complete layout.

## Source Guide

| File | Responsibility |
| --- | --- |
| `src/main.cpp` | Command-line arguments, error messages, and scaffold status |
| `src/ciphertext.h` | Public contract for reading and validating ciphertext |
| `src/ciphertext.cpp` | File I/O, whitespace handling, and uppercase input validation |
| `data/ciphertext.txt` | Verified assignment input, separate from the code |

Keep this small separation as analysis is added; do not add placeholder modules for unfinished algorithms.

## Requirements from the Assignment

The supplied `Project2.pdf` specifies the following deliverables:

1. For candidate key lengths 6, 7, and 8, split the ciphertext into interleaved substrings and report the index of coincidence for every substring: 6 + 7 + 8 = 21 values. State whether the results support length 7 and briefly explain why. Averages alone are insufficient.
2. Produce the seven-column table described in slide 26 of `sec2.4.pdf` and use it to identify a meaningful English keyword.
3. Decrypt the ciphertext with that keyword and present readable plaintext with spaces, periods, and sentence-initial capitalization.
4. Submit commented source code and typed PDF output as separate, unzipped files. Put every participating student's name at the top of the output.

The assignment permits any language or mathematical software. Continuing with C++17 is a repository choice, not an assignment requirement. The program need not generate PDF files directly.

## Input Provenance

`data/ciphertext.txt` contains the 18 ciphertext lines from page 1 of the supplied assignment, in their original order. Whitespace is not part of the cipher. After removing whitespace, the input contains 1,260 uppercase letters.

- Assignment PDF SHA-256: `5fd7410bc283a630f6e820c3a4e590008db4b19c30b1b63ab5093cae1ce762c2`
- Ciphertext SHA-256, uppercase letters only with no trailing newline: `bab36c9d910972629b179fab287766ebee80df00e74c7e40b3c38a9732e88d1a`

The original assignment PDF is not copied into the repository. Retain the supplied copy as the reference.

## Build and Run

From the repository root:

```bash
cmake -S . -B build
cmake --build build
./build/project2_vigenere project2/data/ciphertext.txt
```

Expected output:

```text
Project 2 - Vigenere cipher scaffold
Ciphertext characters: 1260
Status: input validated; cryptanalysis is not implemented.
```

The input path is required and resolves relative to the current working directory. Missing, empty, unreadable, lowercase, or nonalphabetic input is rejected; whitespace is allowed. The source can also be compiled without CMake:

```bash
c++ -std=c++17 project2/src/main.cpp project2/src/ciphertext.cpp -o project2_vigenere
./project2_vigenere project2/data/ciphertext.txt
```

## Implementation Plan

### 1. Confirm References and Participants

- Obtain `sec2.4.pdf`, especially slide 26, before finalizing the keyword-recovery table. Do not substitute a guessed table format.
- Confirm the Project 2 roster; do not assume it is identical to Project 1.
- Visually compare the saved ciphertext with the assignment and retain the normalized checksum as a transcription check.

### 2. Implement Coincidence Analysis

- Keep input handling, numerical calculations, and report formatting separate as the implementation grows.
- For candidate length `m`, put characters at positions `j`, `j + m`, `j + 2m`, and so on in substring `j`, using zero-based positions in code.
- Calculate `IC = sum(frequency * (frequency - 1)) / (length * (length - 1))` with floating-point division and a guard for substrings shorter than two characters.
- Print all 21 individual values with clear substring labels and consistent precision. Averages may supplement, but not replace, those values.
- Explain the evidence for or against length 7 using the calculated results, without hardcoding the conclusion.

### 3. Recover the Keyword

- Implement the course's seven-column method after reviewing slide 26.
- Display enough intermediate values to justify each chosen letter.
- Check that the resulting seven-letter keyword is a meaningful English word and leads to coherent plaintext.

### 4. Decrypt and Verify

- Use a documented A=0 through Z=25 convention and nonnegative modulo-26 arithmetic.
- Keep the raw decrypted letters separate from the human-edited presentation.
- Re-encrypt the raw plaintext with the recovered keyword and require an exact match with the normalized ciphertext.
- Review word boundaries, sentence capitalization, and periods manually. Removing presentation formatting must reproduce the raw plaintext exactly.

### 5. Prepare the Final Deliverables

- Generate intermediate reports under `project2/output/`, which is ignored by Git.
- Place the deliberately selected final source files and PDF in `project2/submission/` when ready; that directory is not ignored.
- Add explanatory code comments before submission and document any needed compile commands or input files.
- Verify that the PDF includes the confirmed roster, all three assignment parts, the complete table, the keyword explanation, and readable plaintext.
- Inspect the rendered PDF for clipped columns and missing content. Upload the required files separately, not as a ZIP archive.

## Readiness Checks

- A fresh CMake build produces all three executable targets.
- `project1_submission` still reproduces `project1/output/project1_output.txt` exactly when checked from the repository root.
- The scaffold accepts the supplied 1,260-letter ciphertext and rejects invalid input.
- Generated build products and temporary reports do not appear as untracked files.
- Project 2 is not considered complete until the numerical analysis, keyword recovery, decryption, roster, and PDF review are finished.
