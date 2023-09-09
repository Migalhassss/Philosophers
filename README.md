# Philosophers

## Overview

The "Philosophers" project is a common challenge in computer science education, particularly at 42 school, where students are tasked with implementing the dining philosophers problem in the C programming language. This project teaches students about synchronization, concurrency, and multithreading concepts.

This repository contains the source code for the "Philosophers" project, along with usage instructions and a brief overview of its features.

## Table of Contents

- [Features](#features)
- [Usage](#usage)
- [Building Philosophers](#building-philosophers)
- [Running Philosophers](#running-philosophers)
- [Example Usage](#example-usage)
- [Acknowledgments](#acknowledgments)
- [Support](#support)

## Features

- Implements the dining philosophers problem using multithreading.
- Demonstrates synchronization techniques to prevent deadlocks and resource contention.
- Provides a hands-on learning experience in concurrent programming.
- Compatible with Unix-like systems (Linux, macOS).

## Usage

### Building Philosophers

1. Clone this repository or download the source code.

2. Open a terminal and navigate to the project's root directory.

3. Use the provided Makefile to build the "Philosophers" program. You can choose different compilation options by specifying the target in the Makefile.

    - To build the program with default settings:

        ```bash
        make
        ```

    - To clean up object files and executables:

        ```bash
        make clean
        ```

4. After building, you'll have an executable named "philosophers" in the project directory.

### Running Philosophers

To run the "Philosophers" program, use the following command:

```bash
./philosophers [options]
```

### Example Usage

Here's an example of how to run the "Philosophers" program with five philosophers and 200 milliseconds time to die and 200 time to eat you can :
```bash
./philo 5 200 200
```

## Acknowledgments

The "Philosophers" project is a classic exercise in concurrent programming and is commonly used in computer science education. This project is inspired by the need for students to gain practical experience in synchronization and multithreading concepts.

## Support 

If you have any questions, encounter issues, or need assistance with the libft project, please feel free to open an issue on GitHub. Im here to help and improve the library together
