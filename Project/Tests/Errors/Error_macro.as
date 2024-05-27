; This file contain errors in macro layout.
; for this file no "am" file will be created.
; the program will stop after the layout.


.extern L1
mcro mov
    mov 12, @r4
    jmp L1
endmcro
lea @r3, LOOP
mov  
mcro .data
    jsr @r4
endmcro
mcro M1 extra_text
    prn 10
    dec @r3
endmcro
mcro @r2
   inc L1
endmcro
mcro !
   not @r4
endmcro

