// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R1 and R2 and stores the result in R3.
// (R1, R2, R3 refer to RAM[1], RAM[2], and RAM[3], respectively.)
// The algorithm is based on repetitive addition.

//Code starts here
//Initialise R3=0 to make sure that the storage =0 as we need to store the value of multiplication into R3
	@R3 //A=R3
	D=0 //Initialise data=0
	M=D //Memory[A]=0 which will then make R3=0

//Determine the value of R2 and make it the counter as R2=B and A will be multiplied according to B
//It will jump into Loop if R2>0

(LOOP)
	@R2
	D=M //Data=Memory[A] which means R2=the value set in Mult.tst
	//Next round onwards, Memory[A]=Data ; to update the value of R2
	@END 
	D;JLE  //Jump into loop if R2<=0

	//Receive R3
	@R3
	D=M //1st round is D=0, consequent round, value of R3 will be updated to the value of previous round

	//Receive R1
	@R1
	D=D+M //R3=R3+R1
	
	@R3
	M=D //Update the value at R3

	//Reduce R2 by 1
	@R2
	M=M-1 //R2=R2-1

	@LOOP //go back to ROM line 3 to check for the condition
	0;JMP
(END)
	@END
	0;JMP


























