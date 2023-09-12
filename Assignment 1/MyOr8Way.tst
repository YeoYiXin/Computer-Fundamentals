//This is for Or8Way gate, where there are 8 inputs, all 1 bit wide.
//Since there are 8 inputs, I will need 7 OR gates (all accepting 2 inputs only).
//The first step is 4 OR gates, each accepting 2 inputs.
//Then, each OR gate will produce one output.
//Now, I will have a total of 4 outputs from the first step.
//From this, I will do the second step, which will require 2 OR gates, each accepting 2 inputs.
//Then, the OR gate will produe one output which ultimately leave me with 2 outputs from the second step.
//Finally, the 2 outputs from the second step will be used as the input for the 7th OR gate.
//After that, we will get the result which is named as out variable.

load MyOr8Way.hdl,
output-file MyOr8Way.out,
compare-to MyOr8Way.cmp,
output-list in%B1.8.1 out%B3.1.3; //1 space at both left and right side of each input on the
//second line after deciding the names for the input and result variable which are in and out.
//8 in the middle of the format shows that the in variable has 8 bits,
//but for this test, each bit will be treated as one input,
//instead of looking at it as a whole (1 input, 8 bits wide).

//case 1
set in %B00000000,
eval,
output;

//case 2
set in %B11111111,
eval,
output;

//case 3
set in %B01010101,
eval,
output;

//case 4
set in %B10101010,
eval,
output;

//case 5
set in %B11001100,
eval,
output;

//case 6
set in %B00110011,
eval,
output;

//case 7
set in %B00001000,
eval,
output;

//case 8
set in %B11100011,
eval,
output;

//case 9
set in %B00010111,
eval,
output;

//case 10
set in %B11110000,
eval,
output;

//case 11
set in %B10110011,
eval,
output;

//case 12
set in %B00001111,
eval,
output;

//case 13
set in %B00111000,
eval,
output;

//case 14
set in %B01100011,
eval,
output;

//case 15
set in %B10000001,
eval,
output;

//case 16
set in %B00010100,
eval,
output;