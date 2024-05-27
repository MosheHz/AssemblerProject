mov E,E
GOOD1:          prn 12
GOODDATA:       .data 6,-1,0,-12,123
;macro definitions
mcro m2
    ,mov 1, @r2
add, 3, @r4
endmcro
m2
LabMacro: m2

;code/general sentences
LONGLABELnnnalksjSADAasdasdsadDLKAJS: mov 12, @r4
add 123, DEST,
    add 123 DEST
MAIN:           mov @r3 ,,LENGTH
asd 123, LOOP
sub@r0, @r4
    FEW:            add @r3
    jmp L4, LOOP
add 123, @r3, DEST
prn -
sub @r9, @r4
    mov 123, 123
lea @r3, DEST
lea FEW, 123
clr 20
clr @r4 andJust Jibrish
sub 123, 98
sub 123.4, 98
sub 123, LOOP_AS
sub 512, @r3
sub -513, @r4
prn -5, asd
GOOD1:          prn 12
GOOD.1:         prn 12
extern:         not L1

;data sentences
GOODDATA:       .data 6,-1,0,-12,123
NODATA:         .data
    .data 2,54,BAD
    .data 2048
    .data -2049
    .data @r3
    .data "Good String"

;string sentences
GOODSTR:        .string "Good String"
NOSTR:          .string
    .string "Bad"String""
    .string BAD
    .string "Two","Strings"
    .string 123

;extern sentences
TEST:           .extern W,X,Y
    .extern
    .extern r1, L3
    .extern 123
    .extern W
    .extern GOOD1

;entry Sentences
TESTent:        .entry A,B,C
    .entry
    .entry 123,@r3
    .entry B
    .entry GOODDATA


