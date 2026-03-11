# DSA — Greatest Common Divisor (Euclidean Algorithm)

A focused C++ implementation of the **Greatest Common Divisor (GCD)** using the **Euclidean Algorithm** — one of the oldest and most elegant algorithms in the history of mathematics, first described around 300 BCE in Euclid's *Elements*. Despite its age, it remains the standard approach for GCD computation in modern systems, compilers, and cryptographic libraries. This implementation captures the iterative form cleanly and efficiently.

---

## Problem Statement

Given two positive integers `a` and `b`, find their **Greatest Common Divisor** — the largest integer that divides both `a` and `b` without leaving a remainder.

**Example Input:**
```
Enter First Number: 48
Enter Second Number: 18
```

**Example Output:**
```
GCD is: 6
```

*(Divisors of 48: 1, 2, 3, 4, 6, 8, 12, 16, 24, 48 — Divisors of 18: 1, 2, 3, 6, 9, 18 — Largest common: **6**)*

---

## The Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b, gcd;
    cout << "Enter First Number: ";
    cin >> a;
    cout << "Enter Second Number: ";
    cin >> b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    gcd = a;

    cout << "GCD is: " << gcd << endl;

    return 0;
}
```

---

## The Euclidean Algorithm — The Core Idea

The algorithm is grounded in one key mathematical property:

```
GCD(a, b) == GCD(b, a % b)
```

In plain terms: *the GCD of two numbers equals the GCD of the smaller number and the remainder when the larger is divided by the smaller.* This substitution is applied repeatedly, making the problem smaller at every step, until the remainder becomes `0` — at which point the non-zero number left is the GCD.

**Why does this work?**

Any divisor of both `a` and `b` must also divide `a % b` (since `a % b = a - k*b` for some integer `k`). So the set of common divisors of `(a, b)` is identical to the set of common divisors of `(b, a % b)`. The greatest among them — the GCD — is therefore preserved across every substitution.

---

## How The Code Works

The three-line loop is the entire algorithm:

```cpp
while (b != 0) {
    int temp = b;   // save current b
    b = a % b;      // new b = remainder of a ÷ b
    a = temp;       // new a = old b
}
```

- `temp` is necessary because `b` is overwritten before `a` can be updated — a classic simultaneous assignment pattern.
- The loop terminates when `b == 0`.
- After the loop, `a` holds the GCD.

**Why does `a` hold the GCD after the loop?**

The last non-zero value of `b` before it became `0` is the GCD. In the final iteration, `temp = b` (the GCD), `b = a % b = 0` (loop exits), and `a = temp` (the GCD). So `a` is assigned the GCD in the same step that `b` becomes `0`.

---

## Algorithm (Pseudocode)

```
read a, b

while b != 0:
    temp ← b
    b    ← a mod b
    a    ← temp

gcd ← a
print gcd
```

---

## Dry Run

**Input:** `a = 48`, `b = 18`

| Iteration | `a`  | `b`  | `a % b` | `temp` |
|-----------|------|------|---------|--------|
| Start     | 48   | 18   | —       | —      |
| 1         | 18   | 12   | 48%18=12 | 18    |
| 2         | 12   | 6    | 18%12=6  | 12    |
| 3         | 6    | 0    | 12%6=0   | 6     |
| Exit      | **6**| 0    | —       | —      |

**`gcd = a = 6`**
**Output:** `GCD is: 6` ✅

---

**Input:** `a = 56`, `b = 98`

| Iteration | `a`  | `b`  | `a % b` |
|-----------|------|------|---------|
| Start     | 56   | 98   | —       |
| 1         | 98   | 56   | 56%98=56 *(algorithm self-corrects when a < b)* |
| 2         | 56   | 42   | 98%56=42 |
| 3         | 42   | 14   | 56%42=14 |
| 4         | 14   | 0    | 42%14=0  |
| Exit      | **14**| 0   | —       |

**Output:** `GCD is: 14` ✅

---

## Complexity Analysis

| Metric | Complexity |
|--------|------------|
| Time   | **O(log(min(a, b)))** — the remainder shrinks at least by half every two iterations; provably sub-linear |
| Space  | **O(1)** — only three integer variables used, regardless of input size |

> The Euclidean Algorithm is remarkably fast. For two 10-digit numbers, it terminates in at most ~70 iterations. This is why it remains the algorithm of choice for GCD in production systems and cryptographic libraries (RSA key generation, for instance, relies on it heavily).

---

## Self-Correcting Behavior — When `a < b`

The algorithm does not require `a > b` as a precondition. If `a < b` on entry:

```
a = 10, b = 25
First iteration: temp=25, b = 10%25 = 10, a = 25
```

In a single step, the values are effectively swapped and the algorithm proceeds correctly. No explicit ordering is needed — a subtle but elegant property of the modulo operation.

---

## Edge Cases

| Scenario | Behavior |
|----------|----------|
| `a = b` | `a % b = 0` on the first iteration → GCD = `b` = `a`. Correct |
| `b = 1` (or `a = 1`) | GCD = 1 — any number and 1 are coprime |
| `a = 0, b = n` | Loop skipped (`b != 0` but `a = 0`... see note below) |
| Both equal `{n, n}` | Returns `n` immediately |
| Large numbers | Still O(log n) — no performance concern |

> **Zero input note:** If `a = 0`, the loop runs once: `temp=b`, `b=0%b=0`, `a=b` → GCD = b. Mathematically correct since GCD(0, n) = n by convention. However, the code does not explicitly validate for negative inputs — negative values will produce undefined modulo behavior in C++.

---

## A Note on `#include <bits/stdc++.h>`

The code uses `#include <bits/stdc++.h>`, which is a **GCC-specific convenience header** that includes the entire C++ standard library in one line. It is widely used in competitive programming for speed of writing but carries real drawbacks in production or portable code:

| Aspect | `#include <bits/stdc++.h>` | Standard Headers |
|--------|---------------------------|------------------|
| Portability | GCC/G++ only — fails on MSVC, Clang in strict mode | Universal |
| Compile time | Slower — includes everything | Faster — includes only what's needed |
| Best for | Competitive programming | Production, interviews, open-source |

For this program, the only headers actually needed are:

```cpp
#include <iostream>   // for cin, cout, endl
```

This is worth knowing — many interviewers at product companies flag `bits/stdc++.h` as a code quality concern.

---

## Repository Structure

```
DSA-GCD/
│
├── gcd.cpp         # Main C++ implementation
└── README.md       # Project documentation
```

---

## How to Compile and Run

**Prerequisites:** GCC / G++

```bash
# Clone the repository
git clone https://github.com/rishita-ops/DSA-GCD.git
cd DSA-GCD

# Compile
g++ gcd.cpp -o gcd

# Run
./gcd
```

**On Windows:**
```bash
g++ gcd.cpp -o gcd.exe
gcd.exe
```

---

## Key Concepts Covered

- **Euclidean Algorithm** — iterative GCD via successive remainder reduction
- **The identity `GCD(a, b) = GCD(b, a % b)`** — the mathematical engine behind the algorithm
- **Simultaneous assignment via `temp`** — a clean swap pattern without using `std::swap`
- **Post-loop state** — understanding why `a` holds the GCD after `b` reaches `0`
- **Self-correcting input order** — why `a < b` on entry is handled automatically
- **`#include <bits/stdc++.h>`** — convenience vs. portability trade-off, and when each is appropriate

---

## Why This Algorithm Matters in DSA

GCD is not a standalone concept — it is the foundation of a wide family of problems:

| Problem / Concept | Connection |
|-------------------|------------|
| LCM (Least Common Multiple) | `LCM(a,b) = (a * b) / GCD(a,b)` — directly derived |
| Fraction simplification | Divide numerator and denominator by their GCD |
| Coprime check | If `GCD(a, b) == 1`, the numbers are coprime |
| Extended Euclidean Algorithm | Finds integers `x`, `y` such that `ax + by = GCD(a,b)` — foundation of modular inverse |
| RSA Cryptography | Key generation relies on finding coprimes via GCD |
| Modular arithmetic | GCD determines when modular inverses exist |
| Array GCD problems | LeetCode 1979, 2447 — GCD of array, GCD of strings |

Understanding the Euclidean Algorithm deeply — not just running it, but knowing *why it terminates* and *why `a` holds the answer* — is a recurring signal of mathematical maturity that interviewers specifically look for.

---

## Contributing

Contributions are welcome. Consider adding:
- A **recursive version** for comparison (`return b == 0 ? a : gcd(b, a % b)`)
- An **Extended Euclidean Algorithm** implementation
- An **LCM** function built on top of this GCD
- Input validation for negative numbers and zero
- Implementations in Python, Java, or JavaScript

```bash
git checkout -b feature/your-feature
git commit -m "Add: your feature description"
git push origin feature/your-feature
# Then open a Pull Request
```

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

*Part of a structured DSA practice series — fundamentals, done right.*
