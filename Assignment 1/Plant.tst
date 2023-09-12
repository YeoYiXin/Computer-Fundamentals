//This is the testing folder for Plant.hdl (working is in Plant.hdl).

load Plant.hdl,
output-file Plant.out,
compare-to Plant.cmp,
output-list A%B3.1.3 B%B3.1.3 C%B3.1.3 out%B3.1.3; //1 space at both left and right side of each input on the
//second line after deciding the name for the 3 inputs and result variable which are A, B, C and out
//1 in the middle of the format shows each input has 1 bit.

//case 1
set A 0,
set B 0,
set C 0,
eval,
output;

//case 2
set A 0,
set B 0,
set C 1,
eval,
output;

//case 3
set A 0,
set B 1,
set C 0,
eval,
output;

//case 4
set A 0,
set B 1,
set C 1,
eval,
output;

//case 5
set A 1,
set B 0,
set C 0,
eval,
output;

//case 6
set A 1,
set B 0,
set C 1,
eval,
output;

//case 7
set A 1,
set B 1,
set C 0,
eval,
output;

//case 8
set A 1,
set B 1,
set C 1,
eval,
output;