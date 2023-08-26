.index = $f;Index pointer in zero page

loop:
LDA #$10
STA $00,X
INX 
TXA
CMP #$FF
BNE loop

