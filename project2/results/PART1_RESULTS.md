# Project 2 — Part 1 Results

**Group 5 — confirmed October 29, 2026**

- Nguyen Nguyen
- Spencer Steadman
- Tanishqa Gautam
- Tyler Duszak

**Status:** References and roster confirmed; Part 1 complete. Parts 2-3 and the final PDF are not complete.

## Method and References

The supplied ciphertext has **1,260 uppercase letters**. For candidate key length `m`, substring `y1` contains characters at one-based positions `1, 1 + m, 1 + 2m, ...`; `y2` starts at position 2, and so on. These are interleaved subsequences, not consecutive chunks.

For a substring of length `n` with letter frequencies `f_A, ..., f_Z`, calculate:

```text
IC = sum(frequency * (frequency - 1)) / (n * (n - 1))
```

The numerator counts matching ordered pairs without replacement. The tables include this numerator to make the values auditable. All reported ICs are rounded to nine decimal places; the program calculates comparisons before rounding.

[Course slides 13-18](references/sec2.4.pdf#page=13) give the formula and the approximate benchmarks **English = 0.065**, **uniform random = 1/26 = 0.038461538...**. [Slide 26](references/slide26.png) is attached and reviewed for the later keyword-recovery table; Part 1 does not calculate that table yet.

## Candidate m = 6

Each of the six substrings has 210 letters, so the denominator is `210 * 209 = 43890`.

| Substring | Length | Matching ordered pairs | IC |
| --- | ---: | ---: | ---: |
| y1 | 210 | 1856 | 0.042287537 |
| y2 | 210 | 1870 | 0.042606516 |
| y3 | 210 | 1780 | 0.040555935 |
| y4 | 210 | 1780 | 0.040555935 |
| y5 | 210 | 1846 | 0.042059695 |
| y6 | 210 | 1844 | 0.042014126 |

## Candidate m = 7

Each of the seven substrings has 180 letters, so the denominator is `180 * 179 = 32220`.

| Substring | Length | Matching ordered pairs | IC |
| --- | ---: | ---: | ---: |
| y1 | 180 | 2296 | 0.071260087 |
| y2 | 180 | 2296 | 0.071260087 |
| y3 | 180 | 2196 | 0.068156425 |
| y4 | 180 | 1978 | 0.061390441 |
| y5 | 180 | 2202 | 0.068342644 |
| y6 | 180 | 2006 | 0.062259466 |
| y7 | 180 | 2188 | 0.067908132 |

## Candidate m = 8

The first four substrings have 158 letters and denominator `158 * 157 = 24806`; the last four have 157 letters and denominator `157 * 156 = 24492`. No letters are dropped or padded.

| Substring | Length | Matching ordered pairs | IC |
| --- | ---: | ---: | ---: |
| y1 | 158 | 1000 | 0.040312828 |
| y2 | 158 | 988 | 0.039829074 |
| y3 | 158 | 1084 | 0.043699105 |
| y4 | 158 | 1074 | 0.043295977 |
| y5 | 157 | 1022 | 0.041727911 |
| y6 | 157 | 1082 | 0.044177691 |
| y7 | 157 | 992 | 0.040503021 |
| y8 | 157 | 928 | 0.037889923 |

## Comparison and Explanation

The averages below supplement, rather than replace, the 21 individual values above. Mean absolute distance is the average of `abs(IC(y_j) - 0.065)` over the candidate's substrings.

| Candidate key length | Mean IC | Mean absolute distance from 0.065 |
| --- | ---: | ---: |
| 6 | 0.041679957 | 0.023320043 |
| 7 | 0.067225326 | 0.004039638 |
| 8 | 0.041429441 | 0.023570559 |

**Yes, the outputs support the guess m = 7.** Its individual ICs range from **0.061390441 to 0.071260087**, close to the English benchmark of 0.065. They are consistently more English-like than the m = 6 and m = 8 values, which cluster near 0.04, much closer to the uniform-random benchmark. The substantially smaller mean absolute distance for m = 7 confirms that the preference is visible across its individual substrings, not only in its average.

With the correct period, each substring is encrypted using a single Caesar shift, which preserves its letter frequencies and IC. Incorrect candidate periods mix positions encrypted with different shifts, tending to flatten the frequency distribution. Thus 7 is supported over the tested alternatives 6 and 8. This statistical evidence does not independently prove the exact key length or recover the keyword; the later table and meaningful plaintext are still needed.

## Reproduce

From the repository root:

```bash
cmake -S . -B build
cmake --build build
./build/project2_vigenere project2/data/ciphertext.txt
```

The input's normalized SHA-256 remains `bab36c9d910972629b179fab287766ebee80df00e74c7e40b3c38a9732e88d1a`. The confirmed participants appear before the calculated report. No keyword or plaintext is included in this milestone.
