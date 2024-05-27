# AssemblerProject


This project is based on the two-pass assembler model.<br />
Note: the computer model for this project and the given assembly language are imaginary.



This project is an invented assembly language assembler.
The program gets a files with invented assembly language code and checks the syntax.
If non error occur in the file the program will create an 'object' file (.ob) with base 64 code representation,
'entry' file (.ent) that represent the location of entry labels (use for other files if they use those labels),
'extern' file (.ext) that represent the location of which the file use extern labels.
If an error occur the program will print an error message and continue
to test the rest of the code. in case of error no output files will be created.


