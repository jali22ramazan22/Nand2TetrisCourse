@SCREEN
D=A
@0
M=D	
@KBD
D=M
@12
D;JGT	
@16
D;JEQ
@KBDCHECK
0;JMP
@1
M=-1	
@20
0;JMP
@1
M=0	
@20
0;JMP
@1	
D=M	
@0
A=M
M=D
@0
D=M+1	
@KBD
D=A-D	
@0
M=M+1	
A=M
@20
D;JGT
@0
0;JMP
