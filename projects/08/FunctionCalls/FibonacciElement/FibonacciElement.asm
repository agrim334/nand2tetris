@256
D=A
@R0
M=D

@RETSys.init0
D=A
@R0
A=M
M=D
@R0
M=M+1

@R1
D=M
@R0
A=M
M=D
@R0
M=M+1

@R2
D=M
@R0
A=M
M=D
@R0
M=M+1

@R3
D=M
@R0
A=M
M=D
@R0
M=M+1

@R4
D=M
@R0
A=M
M=D
@R0
M=M+1

@R0
D=M
@0
D=D-A
@5
D=D-A
@R2
M=D
@R0
D=M
@R1
M=D

@Sys.init
D;JMP

(RETSys.init0)

(Sys.init)

@4
D=A
@R0
A=M
M=D
@R0
M=M+1
@RETMain.fibonacci1
D=A
@R0
A=M
M=D
@R0
M=M+1

@R1
D=M
@R0
A=M
M=D
@R0
M=M+1

@R2
D=M
@R0
A=M
M=D
@R0
M=M+1

@R3
D=M
@R0
A=M
M=D
@R0
M=M+1

@R4
D=M
@R0
A=M
M=D
@R0
M=M+1

@R0
D=M
@1
D=D-A
@5
D=D-A
@R2
M=D
@R0
D=M
@R1
M=D

@Main.fibonacci
D;JMP

(RETMain.fibonacci1)

(Main.fibonacci$WHILE)

@Main.fibonacci$WHILE
D;JMP

(Main.fibonacci)

@R2
D=M
@0
D=D+A
A=D
D=M
@R0
A=M
M=D
@R0
M=M+1
@2
D=A
@R0
A=M
M=D
@R0
M=M+1
@R0
M=M-1
A=M
D=M
@R0
M=M-1
A=M
D=M-D
@TRUE0
D;JLT
D=0
@S0
D;JMP
(TRUE0)
D=-1
(S0)
@R0
A=M
M=D
@R0
M=M+1

@R0
AM=M-1
D=M
@Main.fibonacci$IF_TRUE
D;JNE

@Main.fibonacci$IF_FALSE
D;JMP

(Main.fibonacci$IF_TRUE)

@R2
D=M
@0
D=D+A
A=D
D=M
@R0
A=M
M=D
@R0
M=M+1
@R1
D=M
@FRAME
M=D
@5
A=D-A
D=M
@RETMain.fibonacci2
M=D

@R0
AM=M-1
D=M
@R2
A=M
M=D

@R2
D=M+1
@R0
M=D
@FRAME
A=M
D=A-1
@R13
AM=D
D=M
@R4
M=D
@R13
AM=M-1
D=M
@R3
M=D
@R13
AM=M-1
D=M
@R2
M=D
@R13
AM=M-1
D=M
@R1
M=D
@RETMain.fibonacci2
A=M
D;JMP

(Main.fibonacci$IF_FALSE)

@R2
D=M
@0
D=D+A
A=D
D=M
@R0
A=M
M=D
@R0
M=M+1
@2
D=A
@R0
A=M
M=D
@R0
M=M+1
@R0
M=M-1
A=M
D=M
@R0
M=M-1
A=M
M=M-D
@R0
M=M+1
@RETMain.fibonacci3
D=A
@R0
A=M
M=D
@R0
M=M+1

@R1
D=M
@R0
A=M
M=D
@R0
M=M+1

@R2
D=M
@R0
A=M
M=D
@R0
M=M+1

@R3
D=M
@R0
A=M
M=D
@R0
M=M+1

@R4
D=M
@R0
A=M
M=D
@R0
M=M+1

@R0
D=M
@1
D=D-A
@5
D=D-A
@R2
M=D
@R0
D=M
@R1
M=D

@Main.fibonacci
D;JMP

(RETMain.fibonacci3)

@R2
D=M
@0
D=D+A
A=D
D=M
@R0
A=M
M=D
@R0
M=M+1
@1
D=A
@R0
A=M
M=D
@R0
M=M+1
@R0
M=M-1
A=M
D=M
@R0
M=M-1
A=M
M=M-D
@R0
M=M+1
@RETMain.fibonacci4
D=A
@R0
A=M
M=D
@R0
M=M+1

@R1
D=M
@R0
A=M
M=D
@R0
M=M+1

@R2
D=M
@R0
A=M
M=D
@R0
M=M+1

@R3
D=M
@R0
A=M
M=D
@R0
M=M+1

@R4
D=M
@R0
A=M
M=D
@R0
M=M+1

@R0
D=M
@1
D=D-A
@5
D=D-A
@R2
M=D
@R0
D=M
@R1
M=D

@Main.fibonacci
D;JMP

(RETMain.fibonacci4)

@R0
M=M-1
A=M
D=M
@R0
M=M-1
A=M
M=D+M
@R0
M=M+1
@R1
D=M
@FRAME
M=D
@5
A=D-A
D=M
@RETMain.fibonacci5
M=D

@R0
AM=M-1
D=M
@R2
A=M
M=D

@R2
D=M+1
@R0
M=D
@FRAME
A=M
D=A-1
@R13
AM=D
D=M
@R4
M=D
@R13
AM=M-1
D=M
@R3
M=D
@R13
AM=M-1
D=M
@R2
M=D
@R13
AM=M-1
D=M
@R1
M=D
@RETMain.fibonacci5
A=M
D;JMP

