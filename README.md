# MATH 4175 — Cryptography Projects

Small C++17 projects for **Virginia Tech MATH 4175: Cryptography**. Each project keeps its own source, input or saved output, and documentation; the root contains only shared build configuration and this overview.

| Project | Topic | Status |
| --- | --- | --- |
| [Project 1](project1/README.md) | Division Algorithm, gcd, and Bezout coefficients | Complete; original results and submission files preserved |
| [Project 2](project2/README.md) | Vigenere cipher analysis and decryption | Input scaffold and plan only; cryptanalysis not implemented |

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
    ├── data/
    │   └── ciphertext.txt
    └── src/
        ├── main.cpp
        ├── ciphertext.h
        └── ciphertext.cpp
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
| `build/project2_vigenere` | Project 2 input validation and scaffold status |

The Project 2 scaffold accepts the supplied **1,260-letter ciphertext**. It rejects missing, empty, unreadable, or invalid input; spaces and line breaks are allowed. It does not recover a keyword or decrypt the assignment yet.

Check that Project 1's saved result is unchanged:

```bash
./build/project1_submission | cmp - project1/output/project1_output.txt
```

No output from `cmp` means the files match.

## Where to Work

- **Project 1:** `project1/src/` is the standalone implementation; `project1/legacy/` and `project1/submission/` retain the original reference and submitted files. Detailed explanation, group roster, and results are in the [Project 1 README](project1/README.md).
- **Project 2:** `main.cpp` handles CLI messages, while `ciphertext.h` and `ciphertext.cpp` define and implement input loading. The verified assignment text lives in `project2/data/`.
- **Temporary output:** use `build/` or `project2/output/`; both are ignored. Add only deliberately selected final Project 2 deliverables under `project2/submission/` when ready.

## Project 2 Next Steps

1. Obtain slide 26 of `sec2.4.pdf` and confirm the participating students.
2. Calculate all substring coincidence indices for key lengths 6, 7, and 8.
3. Build the course-required seven-column table and recover the keyword.
4. Decrypt, verify by re-encryption, and format the plaintext for a typed PDF.

See the [Project 2 requirements and implementation plan](project2/README.md) for the full checklist. Submit the final source and PDF as separate, unzipped files with every participant's name at the top of the output.
