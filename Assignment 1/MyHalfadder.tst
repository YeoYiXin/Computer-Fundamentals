//This is the testing folder for Half Adder 
//where each input only accept 1 bit

load MyHalfadder.hdl,
output-file MyHalfadder.out,
compare-to MyHalfadder.cmp,
output-list a%B5.1.5 b%B5.1.5 carry%B5.1.5 sum%B5.1.5;

//case 1
set a 0,
set b 0,
eval,
output;

//case 2
set a 0,
set b 1,
eval,
output;

//case 3
set a 1,
set b 0,
eval,
output;

//case 4
set a 1,
set b 1,
eval,
output;
