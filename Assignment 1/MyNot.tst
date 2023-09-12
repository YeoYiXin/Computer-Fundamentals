//MyNot test folder
//Use Nand to create NOT gate. 
//NAND gate can only be NOT gate using two 1-bit inputs which are
//when a and b are both 0 or 1

load MyNot.hdl,
output-file MyNot.out,
compare-to MyNot.cmp,
output-list a%B3.1.3 out%B3.1.3;

set a 0,
eval,
output;

set a 1,
eval,
output;