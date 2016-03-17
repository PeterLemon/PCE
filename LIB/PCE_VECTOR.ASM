//==================
// PC-Engine VECTOR
//==================
seek($FFF6)
// VECTOR (HuC6280 Mode)
dw $0000 // IRQ2  VECTOR (BRK)
dw $0000 // IRQ1  VECTOR (VDC)
dw $0000 // TIMER VECTOR
dw $0000 // NMI VECTOR
dw $0000 // RESET VECTOR