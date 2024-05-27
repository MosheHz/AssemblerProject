; Good file: testing the macro layout, 
; ignoring white spaces, empty and comment lines.
; also testing the correct output files.

.extern A1, A2
.entry LOOP, T, MAIN
mcro M1
    add  20, @r3
    lea LOOP, @r4
endmcro
MAIN: cmp DATA, @r5
inc @r2
M1
	mov 122, @r2
LOOP:   sub T, @r1
mcro M2
    prn 80
    red @r5
endmcro
mov T, @r2
cmp A1, 9
M2
M1
	lea A2, @r6

FLOUT: .data 12, 10,  13,   11
T: .data 100
DATA: .data 12
STR: .string "Hello friends"
