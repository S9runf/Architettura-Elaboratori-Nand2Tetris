# Computer Architecture Projects (Nand2Tetris)

This repository contains my implementation of projects from the Computer
Architecture course at the University of Bologna (a.y. 2022-22).

The projects follow the structure of the Nand2Tetris course, covering the
construction of a simple computer from logic gates up to an assembler and
virtual machine compiler.


## Repository Structure

Each project is contained in a separate folder:

- 1 - logicGates: Basic Logic Gates (AND, OR, NOT, XOR, etc.) built from NAND
- 2 - ALU: ALU (Arithmetic Logic Unit) and adders implementation
- 3 - RAM: Memory Components
- 4 - CPU: CPU Design (Instruction Set & Execution)
- 5 - assembler: Assembler (Translating Assembly to Machine Code)
- 6 - VM_Translator: Virtual Machine compiler (Handling Stack-Based Execution)
- Bonus - SpaceInvaders: A simplified version of Space Invaders written in the
VM language


## Additional Information

- The Hardware projects (1-4) use the Hardware Description Language (HDL) 
from Nand2Tetris.

- The Software projects (5-6) include C implementations of an assembler and VM 
interpreter, they can be built by running `make` in the respective folders.

- The Bonus project is a program written in the VM language, the folder
includes a modified version of the VMtranslator that compiles more efficiently
to the CPU's assembly, the resulting programs can then be run using the 
nand2tetris software suite.
