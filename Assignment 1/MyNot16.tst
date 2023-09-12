//This is test folder for Not 16-bits
//with one input and one output
//but each input has 16 bits so
//the output will be 16 bits as well
//the output will be the opposite value 
//of each input bits as observed in the cmp file

load MyNot16.hdl,
output-file MyNot16.out,
compare-to MyNot16.cmp,
output-list in%B1.16.1 out%B1.16.1; //1 space at both left and right side of each input on the
//second line after deciding the name for the 1 input and 1 result variable which are in and out
//16 in the middle of the format shows in input has 16 bits.

//case 1
set in %B0000000000000000,
eval, 
output;

//case 2
set in %B1111111111111111,
eval,
output;

//case 3
set in %B0101010101010101,
eval, 
output;

//case 4
set in %B1100110011001100,
eval,
output;

//case 5
set in %B0001110001110001,
eval, 
output; 

//case 6
set in %B1111000011110000,
eval, 
output; 

//case 7
set in %B1100011000110001,
eval, 
output; 

//case 8
set in %B1000001100000111,
eval, 
output; 

//case 9
set in %B1110000111100011,
eval, 
output; 

//case 10
set in %B1011000111100000,
eval, 
output; 

//case 11
set in %B0000000111111111,
eval, 
output; 

//case 12
set in %B1010111001010100,
eval, 
output; 

//case 13
set in %B0110110110110110,
eval, 
output; 

//case 14
set in %B0000000111100001,
eval, 
output; 

//case 15
set in %B1010101010111100,
eval, 
output; 

//case 16
set in %B1001110000111110,
eval, 
output; 