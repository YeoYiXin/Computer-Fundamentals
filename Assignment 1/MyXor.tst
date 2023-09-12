//This is for XOR gate
//require 1 OR gate, 2 NOT gate, 2 AND gate
//since XOR gate can only be build using NAND gate
//XOR boolean expression:
//P(x, y) = xy'+x'y

load MyXor.hdl,
output-file MyXor.out,
compare-to MyXor.cmp,
output-list a%B3.1.3 b%B3.1.3 out%B3.1.3;

set a 0,
set b 0,
eval,
output;

set a 0,
set b 1,
eval,
output;

set a 1,
set b 0,
eval,
output;

set a 1,
set b 1,
eval,
output;