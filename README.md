# CO Assembler and Simulator - Assembly to Binary Converter
This project aims to develop an assembler that converts assembly instructions into binary code and use that binary code to run the assember simulator for our course on Computer Organization. The assembler takes input in the form of a text file containing assembly instructions, labels, and variable definitions. It supports various types of instructions, including jumps, loads, and stores, along with the usage of registers, memory addresses, and immediate values. The simulator utilizes this binary instructions as well as different instruction types to simulate the assembler

## Functionalities of Assembler
The assembler provides the following functionalities:
- Handling supported instructions.
- Managing labels to mark specific locations in the code.
- Defining and using variables in load and store instructions.
- Detecting and reporting syntax errors for illegal instructions or usage, such as typos, undefined variables or labels, improper use of registers, incorrect immediate values, misuse of labels as variables, variables not declared at the beginning, missing halt instruction, and improper placement of the halt instruction.

## Functionalities of Simulator
The simulator provides the following functionalities:
- Takes input in binary language
- Decode and execute the instructions
- Write the operation back in register memory
- Writes the output in an output file.

## Contributions for Assember:
Following are the contributions made by the team members
- Prakriti Jain (2022362): Handled input, created a data structure, and stored the input. Identified and stored valid label names, variable names, etc.
- Rohit Singhal (2022417): Implemented functions like InsertZeroes, num_to_binary, and check_binary to support the conversion to binary code.
- Anushka Panwar (2020496): Managed variable addresses, checked for flag errors, syntax errors, variable errors, etc.
- Nishant Kumar Singh (2022327): Converted instructions to binary code, checked for other errors such as the absence of a halt instruction.

## Contributions for Simlator:
Following are the contributions made by the team members
- Prakriti Jain (2022362): Type B and C, decToBin, Overflow
- Rohit Singhal (2022417): Type A
- Anushka Panwar (2020496): Type C, binToDec
- Nishant Kumar Singh (2022327): Type E and F, Halt

 
