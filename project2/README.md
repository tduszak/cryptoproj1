# Project 2 — Vigenere Cipher

## Status and Scope

**Updated October 29, 2026:** References and participants are confirmed, and **Part 1 is implemented**. The C++17 program validates the ciphertext, splits it for key lengths 6, 7, and 8, reports all 21 individual coincidence indices, and explains whether the calculated values support length 7. Keyword recovery, decryption, and the final PDF remain pending.

| Milestone | Status | Evidence |
| --- | --- | --- |
| Course references | Complete | Attached PDF; slide 26 visually inspected |
| Project 2 roster | Confirmed by the owner on October 29, 2026 | Group 5 names below |
| Part 1 | Complete | [All 21 values and interpretation](PART1_RESULTS.md) |
| Part 2 | Not implemented | Next: seven-column shift-score table and keyword |
| Part 3 and final submission | Not implemented | Decryption, presentation, and PDF review pending |

Project 1 source, saved outputs, and submission files are preserved under `../project1/` without content changes. Its Euclidean algorithm is not reused for Vigenere analysis. Return to the [repository overview](../README.md) for the complete layout.

## Source Guide

| File | Responsibility |
| --- | --- |
| `src/main.cpp` | Command-line arguments, confirmed roster, and Part 1 report |
| `src/ciphertext.h` | Public contract for reading and validating ciphertext |
| `src/ciphertext.cpp` | File I/O, whitespace handling, and uppercase input validation |
| `src/coincidence.h` | Substring-analysis data types and IC function contracts |
| `src/coincidence.cpp` | Interleaved splitting, coincidence indices, and benchmark comparisons |
| `data/ciphertext.txt` | Verified assignment input, separate from the code |

Keep this small separation as analysis is added; do not add placeholder modules for unfinished algorithms.

## Confirmed Group 5 Roster

The owner explicitly confirmed the same four participants on October 29, 2026:

- Nguyen Nguyen
- Spencer Steadman
- Tanishqa Gautam
- Tyler Duszak

These names appear at the top of both the program output and the Part 1 report.

## Confirmed Course References

- [Section 2.4 course notes](references/sec2.4.pdf): 27-page *Vigenere Cipher* PDF, authored by Math 4175.
- [Slide 26 image](references/slide26.png): an unannotated rendering of the required table, which is embedded as an image in the PDF and is not captured by text extraction.
- [Slides 13-18](references/sec2.4.pdf#page=13) define IC, give the formula, and explain the approximate English benchmark of 0.065 versus uniform-random 1/26.
- [Slides 24-26](references/sec2.4.pdf#page=24) define the shift-score dot products and show 26 candidate shift rows with four example substring columns. Part 2 will adapt this layout to the assignment's seven substrings; it is not part of the current implementation.

Attached PDF SHA-256: `fd5d020e56d22794d15d5daaa9858bc7e39b8bf8abd1019232e35616622af597`.

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

The output includes the confirmed roster, formula, all 21 ICs and substring lengths, three summary averages, and a data-derived yes/no explanation for length 7. The full results are recorded in [PART1_RESULTS.md](PART1_RESULTS.md).

The input path is required and resolves relative to the current working directory. Missing, empty, unreadable, lowercase, or nonalphabetic input is rejected; whitespace is allowed. Part 1 needs at least 16 normalized letters so every substring for all three candidate lengths has at least two characters. Short inputs are rejected before any report is printed, rather than reporting an undefined IC as zero.

The source can also be compiled without CMake:

```bash
c++ -std=c++17 project2/src/main.cpp project2/src/ciphertext.cpp project2/src/coincidence.cpp -o project2_vigenere
./project2_vigenere project2/data/ciphertext.txt
```

Save intermediate text output without modifying the tracked results or submission files:

```bash
mkdir -p project2/output
./build/project2_vigenere project2/data/ciphertext.txt > project2/output/part1_output.txt
```

## Validation — October 29, 2026

- Fresh C++17 builds of all three targets passed with warnings treated as errors and address/undefined-behavior sanitizers enabled.
- 314 local numerical/API checks passed, including the course example, independent pair enumeration, shift invariance, invalid lengths, and reconstruction of the original ciphertext from its columns.
- 24 CLI integration cases passed, including invalid and short input, tied evidence, and synthetic ciphertexts with periods 6, 7, and 8.
- All 21 program values, substring lengths, report numerators, and summary statistics match an independent exact-rational calculation.
- Project 1 files/output and the assignment ciphertext are unchanged; documentation links and reference checksums were verified.

## Implementation Plan

### 1. Confirm References and Participants — Complete

- Attached `sec2.4.pdf` and visually reviewed slide 26; the course's actual table layout is available for Part 2.
- Confirmed the Project 2 roster directly with the owner instead of assuming Project 1's participants carried over.
- Preserved the verified assignment ciphertext and its normalized checksum.

### 2. Implement Coincidence Analysis — Complete

- Keep input handling, numerical calculations, and report formatting separate as the implementation grows.
- For candidate length `m`, put characters at positions `j`, `j + m`, `j + 2m`, and so on in substring `j`, using zero-based positions in code.
- Calculate `IC = sum(frequency * (frequency - 1)) / (length * (length - 1))` with floating-point division and a guard for substrings shorter than two characters.
- Print all 21 individual values with clear substring labels and consistent precision. Averages may supplement, but not replace, those values.
- Explain the evidence for or against length 7 using the calculated results, without hardcoding the conclusion.

The implementation compares the mean absolute distance of every candidate's individual ICs from the course's 0.065 benchmark. It supports 7 only when that distance is strictly smaller than for both 6 and 8, and its columns are closer to the English benchmark than to the uniform-random benchmark. Ties and contrary evidence do not produce a hardcoded yes. This is a statistical comparison of the tested candidates, not a proof of the exact period or keyword.

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
- The program reports exactly 6, 7, and 8 individual ICs, including the unequal substring lengths for candidate 8.
- The calculated values agree with an independent frequency-counting calculation, and the short-input guard prevents division by zero.
- The supplied 1,260-letter ciphertext and all Project 1 artifacts remain unchanged.
- Generated build products and temporary reports do not appear as untracked files.
- Project 2 is not considered complete until the numerical analysis, keyword recovery, decryption, roster, and PDF review are finished.
