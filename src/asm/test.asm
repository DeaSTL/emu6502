
LDX #$00
loop:
  LDA #$20 ; opcode $A9
  STA $00,X ; opcode $95
  INX ; opcode $E8
  JMP loop ; opcode $4C


