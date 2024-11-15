# SYCL Programming Setup and Execution

This project demonstrates a minimal setup for SYCL programming using Intel’s oneAPI DPC++ compiler, avoiding the complexity (and error-prone / misconfigured) use of the provided CMake-based setups in [Intel's official samples](https://github.com/oneapi-src/oneAPI-samples/). The `src` directory contains the example programs, and the `build` directory is used for compiling and running them.

## Project Structure

- **`src/`**: Contains source files with basic SYCL programs:
  - `hello_world.cpp`: Simple device query and "Hello, World" message.
  - `vector_add.cpp`: Performs vector addition on the device.
  - `mat_mul.cpp`: Executes a matrix multiplication on the device.
  - `PrefixSum.cpp`: Computes the inclusive prefix sum in parallel.

- **`build/`**: Folder for executing compilation commands listed below.

## Setup Instructions

To get the environment ready for compiling and running SYCL programs, I followed these steps:

### 1. Install Prerequisites

- **Visual Studio Build Tools and Visual Studio**: Downloaded from [here](https://visualstudio.microsoft.com/de/downloads/). Both were necessary to successfully set up the SYCL environment.
- **Intel oneAPI Base Toolkit**: Downloaded from [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html). This toolkit includes the DPC++ compiler (`dpcpp`) used to compile SYCL programs.

### 2. Set Up VSCode

In Visual Studio Code, select the correct setvars environment by navigating to the path where you installed the oneAPI toolkit into, e.g. `...\Intel\oneAPI\setvars.bat`. This script initializes the environment variables required by oneAPI tools:

![image](https://github.com/user-attachments/assets/e37283e3-0164-435c-9457-f6e58b2234b0)

which is followed by a success message:

![image](https://github.com/user-attachments/assets/28db2568-e51e-4b6f-b838-1d363f5c0bc5)


### 3. Compilation and Execution

Intel's provided tutorials at [oneAPI-samples](https://github.com/oneapi-src/oneAPI-samples/tree/master) were overly complicated for me, using CMake extensively, which often failed to compile examples. I had also tried this [VSCode extension](https://marketplace.visualstudio.com/items?itemName=intel-corporation.oneapi-extension-pack) without luck. 

Instead, I compiled the programs with these straightforward commands:

```bash
cd build

dpcpp -o hello_world.exe ..\src\hello_world.cpp
dpcpp -o vector_add.exe ..\src\vector_add.cpp
dpcpp -o mat_mul.exe ..\src\mat_mul.cpp
dpcpp -o PrefixSum.exe ..\src\PrefixSum.cpp
```

Each command compiles an individual source file to an executable, making the setup simple and quick.

### 4. Running the Programs

To run any of the executables, navigate to the `build` directory and execute them as follows:

```bash
./hello_world.exe
./vector_add.exe
./mat_mul.exe
./PrefixSum.exe
```

The output e.g. of `hello_world.cpp` will indicate which device the code is running on (CPU or GPU), along with a "Hello, World!" message:

```
Running on 13th Gen Intel(R) Core(TM) i5-13600K
Hello, World!
```

or

```
Running on Intel(R) UHD Graphics 770
Hello, World!
```
