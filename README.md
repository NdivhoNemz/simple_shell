# Simple Shell Project

Welcome to the Simple Shell Project, a hands-on learning experience that will help you explore the fundamentals of a Unix-like shell. This project covers various aspects of shell development, historical context, and essential Unix concepts. By the end of this project, you will gain a deeper understanding of how shells work and their significance in the computing world.

## Learning Objectives

The project covers the following key concepts to learn and understand:

1. **Unix Origins:**

    - Learn about the designers and implementers of the original Unix operating system.

2. **History of Shells:**

    - Discover who wrote the first version of the UNIX shell.

3. **Programming Language Evolution:**

    - Understand the connection between the B programming language (predecessor to C) and shell development.

4. **Ken Thompson:**

    - Explore the significance of Ken Thompson in the development of Unix and shells.
    - Shell in [C](<https://en.wikipedia.org/wiki/C_(programming_language)>).
    - [the Thompson Shell](https://en.wikipedia.org/wiki/Thompson_shell).

5. **Shell Functionality:**

    - Learn how a shell operates, including its core functionalities.

6. **Process Management:**

    - Understand the concepts of Process ID (PID) and Parent Process ID (PPID).

7. **Environment Manipulation:**

    - Explore how to manipulate the environment of the current process.

8. **Function vs. System Call:**

    - Distinguish between functions and system calls in the context of shell development.

9. **Process Creation:**

    - Learn how to create new processes and manage them effectively.

10. **Main Function Prototypes:**

    - Understand the three prototypes of the `main` function in a shell program.

11. **Program Execution:**

    - Explore how the shell uses the `PATH` environment variable to locate and execute programs.

12. **Executing Programs:**

    - Learn how to execute other programs using the `execve` system call.

13. **Process Suspension:**

    - Understand how to suspend process execution until a child process terminates.

14. **EOF (End-of-File):**
    - Learn about the concept of "EOF" and its significance.

## Built-in Commands

Our shell has support for the following built-in commands:

| Command              | Definition                                                                                |
| -------------------- | ----------------------------------------------------------------------------------------- |
| exit [n]             | Exit the shell, with an optional exit status, n.                                          |
| env                  | Print the environment.                                                                    |
| setenv [var][value]  | Set an environment variable and value. If the variable exists, the value will be updated. |
| alias[name[='value]] | Reads aliases name                                                                        |
| unsetenv [var]       | Remove an environment variable.                                                           |
| cd [dir]             | Change the directory.                                                                     |
| help [built-in]      | Read documentation for a built-in.                                                        |

## Installation : Getting HSH

Clone the below repository and compile the files into an executable using the GCC compiler.

```
https://github.com/NdivhoNemz/simple_shell.git
```

### Basic usage

-   First, Fork this Repository [Learn how to fork repo](https://docs.github.com/en/github/getting-started-with-github/fork-a-repo).
-   Then Clone [Learn how to clone ](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository).
-   Create an executable by running the following command:
-   `gcc -Wall -Werror -Wextra -pedantic *.c -o shell`
-   From there, type in the following command and press your enter button.
-   `./shell`
-   Final step: ENJOY!

Please refer to the specific man pages for each of these functions and system calls to understand their usage in greater detail.

Now that you have a clear overview of this Simple Shell Project, feel free to start exploring the world of shell development, Unix history, and process management. This project is designed to be a valuable learning experience that will deepen your understanding of shell programming and its historical context. Good luck with your shell development journey!

## Authors

-   [@NdivhoNemz](https://github.com/NdivhoNemz)
-   [@Kalophain14](https://github.com/Kalophain14)

## Used By

This project is used by the following companies:

-   ALX Africa
-   Holberton School

## 🛠 Skills
<<<<<<< HEAD
=======

>>>>>>> 32fdeb6d063e0c68be20f87a2a875c5ccea8c8ca
Shell
