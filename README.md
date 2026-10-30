# MATH 4175 — Cryptography Projects

Small C++17 projects for **Virginia Tech MATH 4175: Cryptography**. Each project keeps its own source, input or saved output, and documentation; the root contains only shared build configuration and this overview.

| Project | Topic | Status |
| --- | --- | --- |
| [Project 1](project1/README.md) | Division Algorithm, gcd, and Bezout coefficients | Complete; original results and submission files preserved |
| [Project 2](project2/README.md) | Vigenere cipher analysis and decryption | References and roster confirmed; Part 1 complete; Parts 2-3 pending |

## Repository Layout

```text
cryptoproj1/
├── .gitignore
├── CMakeLists.txt
├── README.md
├── project1/
│   ├── README.md
│   ├── src/
│   │   └── division_algorithm.cpp
│   ├── legacy/
│   │   ├── algo.cpp
│   │   ├── algo.h
│   │   └── main.cpp
│   ├── output/
│   │   ├── project1_output.pdf
│   │   ├── project1_output.txt
│   │   └── project1_output_with_names.txt
│   └── submission/
│       ├── division_algorithm.cpp
│       └── project1_output.pdf
└── project2/
    ├── README.md
    ├── PART1_RESULTS.md
    ├── data/
    │   └── ciphertext.txt
    ├── references/
    │   ├── sec2.4.pdf
    │   └── slide26.png
    └── src/
        ├── main.cpp
        ├── ciphertext.h
        ├── ciphertext.cpp
        ├── coincidence.h
        └── coincidence.cpp
```

Generated files live in `build/`, which is ignored by Git and omitted from the source tree above. Project 1's `output/` directory is a tracked archive, not a scratch directory.

## Build and Run

Requirements: a **C++17 compiler** and **CMake 3.10 or newer**. Run all commands from the repository root:

```bash
cmake -S . -B build
cmake --build build

./build/project1_submission
./build/project2_vigenere project2/data/ciphertext.txt
```

| Executable | Purpose |
| --- | --- |
| `build/project1_submission` | Authoritative standalone Project 1 implementation |
| `build/cryptoproj1` | Original multi-file Project 1 implementation, retained for reference |
| `build/project2_vigenere` | Project 2 Part 1: all 21 coincidence indices and key-length comparison |

Project 2 analyzes the supplied **1,260-letter ciphertext** for key lengths 6, 7, and 8. The results support length 7: its mean IC is **0.067225326**, compared with **0.041679957** and **0.041429441** for lengths 6 and 8. See the [full 21-value Part 1 report](project2/PART1_RESULTS.md).

Input must contain uppercase A-Z and optional whitespace, with at least 16 letters so every substring has two characters. Invalid or unreadable input is rejected. Keyword recovery and decryption are not implemented yet.

Check that Project 1's saved result is unchanged:

```bash
./build/project1_submission | cmp - project1/output/project1_output.txt
```

No output from `cmp` means the files match.

## Where to Work

- **Project 1:** `project1/src/` is the standalone implementation; `project1/legacy/` and `project1/submission/` retain the original reference and submitted files. Detailed explanation, group roster, and results are in the [Project 1 README](project1/README.md).
- **Project 2:** `main.cpp` presents the report; `ciphertext.h` and `ciphertext.cpp` load input; `coincidence.h` and `coincidence.cpp` split substrings and calculate ICs. Verified input lives in `project2/data/`, and the attached course notes are in `project2/references/`.
- **Temporary output:** use `build/` or `project2/output/`; both are ignored. Add only deliberately selected final Project 2 deliverables under `project2/submission/` when ready.

## Project 2 Progress

Updated **October 29, 2026**:

- [x] Attach `sec2.4.pdf`, inspect slide 26, and confirm the four-person Group 5 roster with the owner.
- [x] Implement Part 1, report all 21 individual ICs, and explain the evidence supporting length 7.
- [ ] Implement Part 2: expand the course's shift-score table to seven substring columns and recover the keyword.
- [ ] Implement Part 3: decrypt, verify by re-encryption, and format the plaintext for a typed PDF.

See the [Project 2 requirements and implementation plan](project2/README.md) for the full checklist. Submit the final source and PDF as separate, unzipped files with every participant's name at the top of the output.
