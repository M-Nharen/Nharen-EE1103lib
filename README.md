EE1103lib
Comprehensive C Library for Numerical Methods and Simulations (EE1103 – IIT Madras)

EE1103lib is a unified, educational C library implementing the numerical and stochastic methods taught in EE1103 – Numerical Methods at IIT Madras.
It provides a clean, modular collection of algorithms for numerical computation, interpolation, ODE solving, matrix operations, random number generation, statistical testing, and physical simulations.

🧭 Overview

This library is designed for both learning and experimentation — easy to read, easy to extend, and fully self-contained (no external dependencies).
Each source file implements a specific numerical or computational method with consistent API naming.
```
📂 Directory Structure
Nharen-EE1103lib/
├──docs/
|   └── API_REFERENCE.md
├── include/
│   └── EE1103lib.h             # Central public header (all prototypes)
├── src/
│   ├── general.c               # Math utilities (mean, stdev, taylor, factorial)
│   ├── random.c                # Random numbers, uniform/Gaussian noise
│   ├── normal.c                # Normal distribution, Student’s t-test
│   ├── matrix.c                # Matrix creation, neighbour sum, fill with randoms
│   ├── interpolation.c         # Lagrange & Newton polynomial interpolation
│   ├── ode.c                   # Euler, Midpoint, Heun, RK4 solvers
│   ├── solvelinearequations.c  # Gaussian elimination & LU decomposition
│   ├── peaks.c                 # Signal peak detection and width estimation
│   ├── metropolishastings.c    # Metropolis–Hastings simulation sweep
│   ├── hamming.c               # Bitwise operations, noise, random bits
├── LICENSE
├── Makefile
└── README.md
```

⚙️ Build & Installation

📦 1. Get the Library

You can either:

Option A – Clone the repository (recommended):
```
git clone https://github.com/M-Nharen/Nharen-EE1103lib.git
cd Nharen-EE1103lib
```

Option B – Download as ZIP:
```
Go to the GitHub page: https://github.com/M-Nharen/Nharen-EE1103lib

Click the green “Code” button → “Download ZIP”

Extract it anywhere on your computer.
```
🧱 2. Build the Static Library

Once you’ve downloaded or cloned the repo, open a terminal in the folder and simply run:
```
make
```

This will:

Compile all .c files in the src/ directory

Create a static library file named libee1103.a in the current folder

Example output:
```
Compiling source files...
Archiving into static library...
✅ Build complete: libee1103.a created in current folder.
```

To clean up:
```
make clean
```

🧩 3. Using the Library in Your Own Code

After building, you’ll have a file called libee1103.a and a folder include/ with the header file.

To compile your own program with this library:
```
gcc your_program.c -I /path/to/Nharen-EE1103lib/include /path/to/Nharen-EE1103lib/libee1103.a -lm -o your_program
```

Example:
```
gcc test_main.c -I include libee1103.a -lm -o test_main
```

Then run:
```
./test_main
```
🧰 Requirements

C compiler: GCC, Clang, or any C99-compatible compiler

OS: Works on Linux, macOS, and Windows (via WSL or MinGW)

Dependencies: Only the standard C library (no external libraries required)

🧹 Optional

You can move the compiled libee1103.a and include/ folder anywhere on your system (for example, into /usr/local/lib and /usr/local/include) if you want to reuse it globally.


🚀 Quick Usage Examples

1. Random Numbers
```
#include "EE1103lib.h"
#include <stdio.h>

int main() {
    srand(time(NULL));
    printf("Random float: %f\n", randombetween(0, 1, "float"));
}
```
2. Solving an ODE (RK4)
```
#include "EE1103lib.h"
#include <stdio.h>

double dydx(double x, double y) { return -2*y + 1; }

int main() {
    double y = rk4(dydx, 0.0, 1.0, 0.1, 10);
    printf("y(1.0) = %f\n", y);
}
```
3. Interpolation
```
#include "EE1103lib.h"
#include <stdio.h>

int main() {
    struct point pts[3] = {{0,1},{1,3},{2,7}};
    printf("Lagrange at x=1.5: %.4f\n", lagrangian(1.5, pts, 3));
    printf("Newton at x=1.5: %.4f\n", newton(1.5, pts, 3));
}
```
4. Solving Linear Systems
```
#include "EE1103lib.h"
#include <stdio.h>

int main() {
    double *Adata[2];
    double A0[2] = {3, 2}, A1[2] = {1, 2};
    Adata[0] = A0; Adata[1] = A1;
    double b[2] = {5, 5};
    double *x = gaussian_elimination(Adata, b, 2);
    printf("x = %.3f, y = %.3f\n", x[0], x[1]);
    free(x);
}
```
📘 Module Documentation

🧩 general.c

Mathematical utility functions:
```
mean(arr, n) – returns mean of an array.
```
```
standard_deviation(arr, n) – computes sample standard deviation.
```
```
thetatoradian(theta) / radiantotheta(radian) – angle conversions.
```
```
factorial(n) – recursive factorial (returns long long).
```
```
taylorsin(theta, N) / taylorcos(theta, N) – Taylor series approximations up to N terms.
```

🎲 random.c

Random number and noise utilities:
```
randombetween(start, end, "int"|"float") – uniform RNG.
```
```
randarray(size, start, end) – generate float array.
```
```
gaussian_noise(stddev) – single Gaussian-distributed sample.
```
📈 normal.c

Statistical functions:
```
normal(size, mean, stdev) – returns array sampled from normal distribution.
```
```
ttest(arr1, arr2, n1, n2) – performs Student’s t-test between two samples.
```

🧮 matrix.c

Matrix utilities:
```
emptymatrix(N) / freematrix(M, N) – allocate/free N×N integer matrix.
```
```
neighboursum(M, i, j, N) – sum of four neighbors (wrap-around).
```
```
matrixfillrandvalues(M, N, start, end) – fill matrix with random integers.
```

📊 interpolation.c

Polynomial interpolation and evaluation:
```
lagrangian(x, pts, M) – Lagrange interpolation.
```
```
newton(x, pts, M) – Newton’s divided difference interpolation.
```
```
newton_maker(pts, M) – compute coefficient array.
```
```
computepoly(x, n, coeffs) – evaluate polynomial at x.
```

🧠 ode.c

Deterministic ODE solvers:
```
euler(f, x0, y0, h, n) – explicit Euler method.
```
```
midpoint(f, x0, y0, h, n) – midpoint method.
```
```
heun(f, x0, y0, h, n) – Heun’s (improved Euler).
```
```
rk4(f, x0, y0, h, n) – classical 4th-order Runge–Kutta.
```

🔢 solvelinearequations.c
```
Solvers for linear systems 
A⋅x=b:
```
```
gaussian_elimination(A, b, n) – Gaussian elimination with pivoting.
```
```
lu_decomposition(A, b, n) – LU decomposition and back-substitution.
(Both return dynamically allocated solution arrays.)
```

📉 peaks.c
```
Signal-processing routine for peak detection in CSV data:

Reads input file with x,y data.

Smooths and denoises signal.

Computes dynamic threshold.

Detects peaks and their full width at half maximum (FWHM).

Prints peak position, width, and separation.
```

🔥 metropolishastings.c
```
Monte Carlo simulation:

metropolis_sweep(M, N, J, T) – single sweep of the 2D Ising-like spin lattice using the Metropolis–Hastings algorithm.
```

⚙️ hamming.c

Bitwise and noise utilities:
```
hamming(a, b, N) – compute Hamming distance between bit arrays.
```
```
insert_bits(dest, src, d, M) – insert bits into destination.
```
```
generate_random_bits(N) – allocate random bit sequence.
```
```
add_noise(block, N, p) – flip bits with probability p.
```

📖 **Full API Documentation:** See the [API Reference →](docs/API_REFERENCE.md)

🧪 Testing

Every function is self-contained and easily testable.
Example test:
```
gcc tests/test_gaussian.c source/*.c -Iinclude -lm -o test
./test
```

🧰 Design Principles

Plain C99, no external dependencies.

Educational clarity and numerical correctness over optimization.

Explicit memory management (malloc/free clearly documented).

Consistent naming and argument order across modules.

Easily portable to any OS or microcontroller.

📜 License

This project is released under the MIT License — see LICENSE for details.

✍️ Author

Developed and maintained by M Nharen.
A comprehensive toolkit for understanding and applying numerical methods in C.
