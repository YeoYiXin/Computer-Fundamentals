    // immediately jump to TEST to check for test case
    @TEST
    1;JGT

    // set R1 to 1 and jump to END
(ZERO)
    @R1
    M=1
    @END
    0;JMP

    // test case for zero factorial
    // if 0, then factorial is 1. Jump to ZERO.
    // otherwise, continue with code
(TEST)
    @0
    D=M
    @ZERO
    D;JEQ

    // initialise R1 to R0
    @R0
    D=M
    @R1
    M=D

(FACTORIAL)
    // decrement R0
    @R0
    M=M-1
    // condition to check whether we have reached end of loop (R0 == 0)
    D=M
    @END
    D;JEQ
    // variable counter
    @counter
    M=D
    // variable temp that stores the multiplier
    @R1
    D=M
    @temp
    M=D
    // jump to MULTIPLY for multiplication
    @MULTIPLY
    0;JMP

(MULTIPLY)
    // condition to check whether counter == 0
    @counter
    D=M
    @1
    D=A-D // 1 -  counter
    @FACTORIAL
    D;JEQ
    // decrement counter by 1
    @counter
    M=M-1
    // multiplication using adding method
    // adds temp (multiplier) to R1
    @temp
    D=M
    @R1
    M=M+D
    // jump to top of this block
    @MULTIPLY
    0;JMP

(END)
    @END
    0;JMP