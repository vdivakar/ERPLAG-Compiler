# ERPLAG-Compiler
This project was a part of the course Compiler Construction at BITS Pilani, under Dr. Vandana Aggarwal.

The name of the language is motivated by the drive to **ER**adicate **PLAG**iarism.  

We have implemented a compiler for this language in a pipelined manner with its various stages being:
  * Lexer
  * Parser
  * AST generation
  * Typechecking & Semantic checking
  
Incomplete:
  * Code Generation (NASM 64-bit compatible assembly)
  
**Authors**
 * [Divakar Verma](https://github.com/vdivakar)
 * [Akanksha Dara](https://github.com/akankshadara)
  
**Usage**
```{r, engine='bash', count_lines}
To compile: make
To execute: ./compiler testcase.txt code.asm
```

