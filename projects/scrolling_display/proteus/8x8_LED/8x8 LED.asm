RS_CNT	EQU		31H
DSP_CNT	EQU		34H				;显示模式
		ORG		00H
START:	MOV		RS_CNT,#00H
		MOV		DSP_CNT,#00H	;显示模式初始值
		MOV		DPTR,#SWITCH	;设置程序跳转表首地址
A0:		MOV		A,DSP_CNT
		ADD		A,DSP_CNT		;双字节指令,偏移量乘2
		JMP		@A+DPTR			;根据显示模式值跳转
SWITCH:	SJMP	DSP_0			;程序跳转表
		SJMP	DSP_1
		SJMP	DSP_2
		SJMP	DSP_3

DSP_0:	MOV		P0,#00H			;显示模式0,行线全部置0
		MOV		A,#01H			;列扫描码初值
	L0:	MOV		P3,A			;输出显示
		LCALL	DELAY
		RL		A				;列扫描码移位
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L0		;模式0显示完毕?
		INC		DSP_CNT			;显示下一模式
		MOV		RS_CNT,#00H
		LJMP	A0
DSP_1:	MOV		P0,#00H			;显示模式1,行线全部置0
	 	MOV		A,#80H			;列扫描码初值
	L1:	MOV		P3,A			;输出显示
		LCALL	DELAY
		RR		A				;列扫描码移位
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L1		;模式1显示完毕?
		INC		DSP_CNT			;显示下一模式
		MOV		RS_CNT,#00H
		LJMP	A0
DSP_2:	MOV		P3,#0FFH		;显示模式2,列线全部置1
	 	MOV		A,#7FH			;行扫描码初值
	L2:	MOV		P0,A			;输出显示
		LCALL	DELAY
		RR		A				;行扫描码移位
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L2		;模式2显示完毕?
		INC		DSP_CNT			;显示下一模式
		MOV		RS_CNT,#00H
		LJMP	A0
DSP_3:	MOV		P3,#0FFH		;显示模式3,列线全部置1
	 	MOV		A,#0FEH			;行扫描码初值
	L3:	MOV		P0,A			;输出显示
		LCALL	DELAY
		RL		A				;行扫描码移位
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L3		;模式3显示完毕?
		MOV		DSP_CNT,#00H	;显示下一模式
		MOV		RS_CNT,#00H
		LJMP	A0

DELAY:	MOV		R5,#10			;延时子程序
D1:		MOV		R6,#20
D2:		MOV		R7,#248
		DJNZ	R7,$
		DJNZ	R6,D2
		DJNZ	R5,D1
		RET

		END