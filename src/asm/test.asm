        LDX #$00       ; Clear X register, will be used as index
init:
        LDA #$20       ; Load A with the value 20
        STA $00,X      ; Store A at the address 0 + X in zero page
        INX            ; Increment X register
        CPX #$08       ; Compare X with 8
        BNE init       ; If X is not 8, loop back to 'init'
        
loop:
        LDX #$00       ; Clear X register for loop
next:
        LDA $00,X      ; Load A from address 0 + X in zero page
        CLC            ; Clear carry flag for addition
        ADC #$01       ; Add 1 to A
        STA $00,X      ; Store A back to address 0 + X
        INX            ; Increment X register
        CPX #$08       ; Compare X with 8
        BNE next       ; If X is not 8, loop back to 'next'
        JMP loop       ; Infinite loop back to 'loop'
