@5
D=A
@R0
M=-D


@5
D=A
@R1
M=D

@R0
D=M

@END
D; JLT //If R0 < 0 then abort

@R1
D=M

@END
D; JLT //if R1 < 0 then abort



@R0
D=M
@R2
M=D //Result memory


@R1
D=M
@iterable
M=D //iterable = r1

@LOOP

(LOOP)
    @iterable
    M=M-1 // iterable--
    @iterable
    D=M

    @END
    D; JEQ //if iterable == 0 then abort
    

    @R0
    D=M 
    @R2
    M=D+M //res = res + r0
    @LOOP
    D; JMP //goto in the start of the loop
(END)
@37
D;JMP
    



