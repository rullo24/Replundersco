# Replundersco

A simple C program that takes a user-provided string, converts all spaces to underscores, and copies the resulting string to the Windows clipboard. This only works on Microsoft Windows obviously.

## How it Works
- Prompts the user for a string input.
- Replaces all spaces in the input with underscores.
- Copies the modified string to the system clipboard.
- Exits

## Compiling
As the project utilises GNU make, the following command will compile the program. 
```bash
make
```
Other than windows, no external dependencies are required.

## Running
The program is to be run with no arguments. Any arguments provided will cause the program to safely close w/o execution
```bash
./replundersco
```
