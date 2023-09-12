//This is the testing folder for add16

load MyAdd16.hdl,
output-file MyAdd16.out,
compare-to MyAdd16.cmp,
output-list a%B1.16.1 b%B1.16.1 out%B1.16.1;

//case 1
set a %B0000000000000000,
set b %B0000000000000000,
eval,
output;

//case 2
set a %B0000000000000000,
set b %B1111111111111111,
eval,
output;

//case 3
set a %B1111111111111111,
set b %B0000000000000000,
eval,
output;

//case 4
set a %B1111111111111111,
set b %B1111111111111111,
eval,
output;

//case 5
set a %B1100110011001100,
set b %B1010101010101010,
eval,
output;

//case 6
set a %B1011101110111011,
set b %B1101101101101101,
eval,
output;

//case 7
set a %B0011001100110011,
set b %B0101010101010101,
eval,
output;

//case 8
set a %B1111000011110000,
set b %B1110001110001110,
eval,
output;

//case 9
set a %B0000011111000111,
set b %B1001001001010101,
eval,
output;

//case 10
set a %B0101010101010101,
set b %B0011001100110011,
eval,
output;

//case 11
set a %B1111111100000001,
set b %B0000011111000000,
eval,
output;

//case 12
set a %B1110001100101000,
set b %B0000101010101010,
eval,
output;

//case 13
set a %B1111111111111100,
set b %B0001110101010100,
eval,
output;

//case 14
set a %B0000000011110000,
set b %B0110110110110110,
eval,
output;

//case 15
set a %B1100001111111000,
set b %B1111111111000000,
eval,
output;

//case 16
set a %B1101101101101101,
set b %B1011010110101011,
eval,
output;

 