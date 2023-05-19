# CO Assembler - Assembly to Binary Converter
This project aims to develop an assembler that converts assembly instructions into binary code language for our course project on Computer Organization. The assembler takes input in the form of a text file containing assembly instructions, labels, and variable definitions. It supports various types of instructions, including jumps, loads, and stores, along with the usage of registers, memory addresses, and immediate values.

## Functionalities
The assembler provides the following functionalities:
- Handling supported instructions.
- Managing labels to mark specific locations in the code.
- Defining and using variables in load and store instructions.
- Detecting and reporting syntax errors for illegal instructions or usage, such as typos, undefined variables or labels, improper use of registers, incorrect immediate values, misuse of labels as variables, variables not declared at the beginning, missing halt instruction, and improper placement of the halt instruction.

## Contributions:
Following are the contributions made by the team members
- Prakriti Jain (2022362): Handled input, created a data structure, and stored the input. Identified and stored valid label names, variable names, etc.
- Rohit Singhal (2022417): Implemented functions like InsertZeroes, num_to_binary, and check_binary to support the conversion to binary code.
- Anushka Panwar (2020496): Managed variable addresses, checked for flag errors, syntax errors, variable errors, etc.
- Nishant Kumar Singh (2022327): Converted instructions to binary code, checked for other errors such as the absence of a halt instruction.

**Note**: The visible contributions mentioned above are based on commits made on 19th May 2023.




