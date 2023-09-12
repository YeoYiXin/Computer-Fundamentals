// This is the testing folder for full adder
// Full adder have 3 inputs, a, b and c 
// where it has the combination of 2 Half Adders and 1 Or gate

load MyFulladder.hdl,
output-file MyFulladder.out,
compare-to MyFulladder.cmp,
output-list a%B3.1.3 b%B3.1.3 c%B3.1.3 carry%B3.1.3 sum%B3.1.3;

//case 1
set a 0,
set b 0,
set c 0,
eval,
output;

//case 2
set a 0,
set b 0,
set c 1,
eval,
output;

//case 3
set a 0,
set b 1,
set c 0,
eval,
output;

//case 4
set a 0,
set b 1,
set c 1,
eval,
output;

//case 5
set a 1,
set b 0,
set c 0,
eval,
output;

//case 6
set a 1,
set b 0,
set c 1,
eval,
output;

//case 7
set a 1,
set b 1,
set c 0,
eval,
output;

//case 8
set a 1,
set b 1,
set c 1,
eval,
output;