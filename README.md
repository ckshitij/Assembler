# Two-pass Assembler
+ An assembler is a _translator_, that translates an assembler program into a conventional **machine language program**. Basically, the assembler goes through the program *one line at a time*, and generates machine code for that instruction. Then the assembler procedes to the next instruction. In this way, the entire machine code program is created. 
```
Consider an assembler instruction like the following

          JMP  LATER
          ...
          ...
LATER:
This is known as a forward reference.
```

+ If the assembler is processing the file one line at a time, then it doesn't know where LATER is when it first encounters the jump instruction. So, it doesn't know if the jump is a short jump, a near jump or a far jump. 
+ There is a large difference amongst these instructions. They are 2, 3, and 5 bytes long respectively. The assembler would have to guess how far away the instruction is in order to generate the correct instruction. If the assembler guesses wrong, then the addresses for all other labels later in the program woulds be wrong, and the code would have to be regenerated. 

## Structure of Two-pass Assembler

![img1](https://github.com/ckshitij/Assembler/blob/master/img1.png)

+ Processing the source program into two passes.
+ The internal tables and subroutines that are used only during Pass 1. 
+ The *SYMTAB, LITTAB, and MOTTAB* are used by both passes.
+ The main problems to assemble a program in one pass involves **forward references**.

### PASS 1

+ Assign addresses to all statements in the program. 
+ Addresses of symbolic labels are stored.
+ Some assemble directives will be processed.

### PASS 2

+ Translate opcode and symbolic operands.
+ Generate data values defined by BYTE,WORD etc. 
+ Assemble directives will be processed.
+ Write the object program and assembly listing.

## Reference 
+ [ppt Related to two Pass Assembler](https://github.com/ckshitij/Assembler/blob/master/twopassass-141009084203-conversion-gate02.pptx)
+ [REF_2](http://users.cis.fiu.edu/~downeyt/cop3402/two-pass.htm)
+ [StackOverFlow](http://stackoverflow.com/questions/10244422/how-is-2-pass-assembler-different-from-one-pass-assembler-in-resolving-the-futur)
 
## How to Run Code

+ Make a new folder **"Assebler"**.
+ Download **Mot_input,assembler.cpp** and **pass1_input** in Assembler folder.
+ compile assembler.cpp

         
          g++ -std=c++11 assembler.cpp
          ./a.out
          
       
          
+ It generate Three Files.
   + pass1_out
   + pass2_input
   + pass2_out
+ You can see files using **cat command**<br>
          ```
          cat filename
          ```
