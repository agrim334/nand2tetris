@17
D=A
@R0
A=M
M=D
@R0
M=M+1
@17
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
D;JEQ
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

@17
D=A
@R0
A=M
M=D
@R0
M=M+1
@16
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
@TRUE1
D;JEQ
D=0
@S1
D;JMP
(TRUE1)
D=-1
(S1)
@R0
A=M
M=D
@R0
M=M+1

@16
D=A
@R0
A=M
M=D
@R0
M=M+1
@17
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
@TRUE2
D;JEQ
D=0
@S2
D;JMP
(TRUE2)
D=-1
(S2)
@R0
A=M
M=D
@R0
M=M+1

@892
D=A
@R0
A=M
M=D
@R0
M=M+1
@891
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
@TRUE3
D;JLT
D=0
@S3
D;JMP
(TRUE3)
D=-1
(S3)
@R0
A=M
M=D
@R0
M=M+1

@891
D=A
@R0
A=M
M=D
@R0
M=M+1
@892
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
@TRUE4
D;JLT
D=0
@S4
D;JMP
(TRUE4)
D=-1
(S4)
@R0
A=M
M=D
@R0
M=M+1

@891
D=A
@R0
A=M
M=D
@R0
M=M+1
@891
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
@TRUE5
D;JLT
D=0
@S5
D;JMP
(TRUE5)
D=-1
(S5)
@R0
A=M
M=D
@R0
M=M+1

@32767
D=A
@R0
A=M
M=D
@R0
M=M+1
@32766
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
@TRUE6
D;JGT
D=0
@S6
D;JMP
(TRUE6)
D=-1
(S6)
@R0
A=M
M=D
@R0
M=M+1

@32766
D=A
@R0
A=M
M=D
@R0
M=M+1
@32767
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
@TRUE7
D;JGT
D=0
@S7
D;JMP
(TRUE7)
D=-1
(S7)
@R0
A=M
M=D
@R0
M=M+1

@32766
D=A
@R0
A=M
M=D
@R0
M=M+1
@32766
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
@TRUE8
D;JGT
D=0
@S8
D;JMP
(TRUE8)
D=-1
(S8)
@R0
A=M
M=D
@R0
M=M+1

@57
D=A
@R0
A=M
M=D
@R0
M=M+1
@31
D=A
@R0
A=M
M=D
@R0
M=M+1
@53
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
M=D+M
@R0
M=M+1
@112
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
@R0
M=M-1
A=M
M=-M
@R0
M=M+1
@R0
M=M-1
A=M
D=M
@R0
M=M-1
A=M
M=D&M
@R0
M=M+1

@82
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
M=D|M
@R0
M=M+1

@R0
M=M-1
A=M
M=!M
@R0
M=M+1
