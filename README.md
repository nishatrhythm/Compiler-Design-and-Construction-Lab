# Compiler Design and Construction Lab

## Problems
1. A Lex program to recognize and count the number of identifiers in a given input.
2. A Lex program to count the characters, words, spaces, and lines in a given input file.
3. A Lex program to count the number of comment lines in a given C/C++/Java program.
4. A Lex program to identify an integer, floating point, exponential, or complex number.
5. A Lex program to identify a Grameenphone/Airtel/Robi/Banglalink/Teletalk number.
6. A Lex program to recognize whether a given sentence is simple, compound, or complex.
7. A Lex program to identify "to be" verb.
8. Find the FIRST and FOLLOW of a given grammar.

## Assignment
Construct a complete 'Lexer' using Lex and a complete 'Parser' using C/C++ (either LL(0) or LL(1) parser).

## Credits
Special thanks to:
- [@najnin26](https://github.com/najnin26/Compiler-Lab)
- [@fms-byte](https://github.com/fms-byte/Compiler-Design-Lab)
- [@waliulrayhan](https://github.com/waliulrayhan/Compiler-Design-Lab)

## Installation and Usage
Ensure you have the following tools installed:
- MinGW: [Download](https://www.mingw-w64.org/downloads)
- Flex: [Download](https://gnuwin32.sourceforge.net/packages/flex.htm)
- Bison: [Download](https://gnuwin32.sourceforge.net/packages/bison.htm)

### Build and Run
Run Flex
   ```bash
   flex filename.l
   ```
Compile using GCC
   ```bash
   gcc lex.yy.c
   ```
Execute the Program
   ```bash
   a.exe
   ```
