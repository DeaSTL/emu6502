.pxlstart = $1000;
.palstart = .pxlstart + ((64 * 64) / 2);



;Black #0
LDA #0 ;R
STA .palstart
LDA #0 ;G
STA .palstart + 1
LDA #0 ;B
STA .palstart + 2

;Grey #1 
LDA #157
STA .palstart + 3
LDA #157
STA .palstart + 4
LDA #157
STA .palstart + 5

;White #2
LDA #255
STA .palstart + 6
LDA #255
STA .palstart + 7
LDA #255
STA .palstart + 8

;Red #3
LDA #255
STA .palstart + 9
LDA #0
STA .palstart + 10
LDA #0
STA .palstart + 11

;Magenta #4
LDA #255
STA .palstart + 12
LDA #0
STA .palstart + 13
LDA #255
STA .palstart + 14

;Brown #5
LDA #77
STA .palstart + 15
LDA #62
STA .palstart + 16
LDA #23
STA .palstart + 17

;Orange #6
LDA #255
STA .palstart + 18
LDA #128
STA .palstart + 19
LDA #0
STA .palstart + 20

;Yellow #7
LDA #255
STA .palstart + 21
LDA #255
STA .palstart + 22
LDA #0

;Dark Green #8
LDA #0
STA .palstart + 24
LDA #128
STA .palstart + 25
LDA #0
STA .palstart + 26

;Green #9
LDA #0
STA .palstart + 27
LDA #255
STA .palstart + 28
LDA #0
STA .palstart + 29

;Cyan #10
LDA #0
STA .palstart + 30
LDA #255
STA .palstart + 31
LDA #255
STA .palstart + 32

;Blue #11
LDA #0
STA .palstart + 33
LDA #0
STA .palstart + 34
LDA #255
STA .palstart + 35

;Purple #12
LDA #128
STA .palstart + 36
LDA #0
STA .palstart + 37
LDA #255
STA .palstart + 38

;Pink #13
LDA #255
STA .palstart + 39
LDA #0
STA .palstart + 40
LDA #128
STA .palstart + 41

;Light Grey #14
LDA #192
STA .palstart + 42
LDA #192
STA .palstart + 43
LDA #192
STA .palstart + 44

;Light Blue #15
LDA #128
STA .palstart + 45
LDA #128
STA .palstart + 46
LDA #255
STA .palstart + 47

loop:
TYA
STA .pxlstart,X
INX
INY
TYA
CMP #$F
BEQ reset
TXA
CMP #$FF
BNE loop

reset:
LDA #0
TAY
JMP loop



