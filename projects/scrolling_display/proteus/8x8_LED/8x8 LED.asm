RS_CNT	EQU		31H
DSP_CNT	EQU		34H				;��ʾģʽ
		ORG		00H
START:	MOV		RS_CNT,#00H
		MOV		DSP_CNT,#00H	;��ʾģʽ��ʼֵ
		MOV		DPTR,#SWITCH	;���ó�����ת���׵�ַ
A0:		MOV		A,DSP_CNT
		ADD		A,DSP_CNT		;˫�ֽ�ָ��,ƫ������2
		JMP		@A+DPTR			;������ʾģʽֵ��ת
SWITCH:	SJMP	DSP_0			;������ת��
		SJMP	DSP_1
		SJMP	DSP_2
		SJMP	DSP_3

DSP_0:	MOV		P0,#00H			;��ʾģʽ0,����ȫ����0
		MOV		A,#01H			;��ɨ�����ֵ
	L0:	MOV		P3,A			;�����ʾ
		LCALL	DELAY
		RL		A				;��ɨ������λ
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L0		;ģʽ0��ʾ���?
		INC		DSP_CNT			;��ʾ��һģʽ
		MOV		RS_CNT,#00H
		LJMP	A0
DSP_1:	MOV		P0,#00H			;��ʾģʽ1,����ȫ����0
	 	MOV		A,#80H			;��ɨ�����ֵ
	L1:	MOV		P3,A			;�����ʾ
		LCALL	DELAY
		RR		A				;��ɨ������λ
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L1		;ģʽ1��ʾ���?
		INC		DSP_CNT			;��ʾ��һģʽ
		MOV		RS_CNT,#00H
		LJMP	A0
DSP_2:	MOV		P3,#0FFH		;��ʾģʽ2,����ȫ����1
	 	MOV		A,#7FH			;��ɨ�����ֵ
	L2:	MOV		P0,A			;�����ʾ
		LCALL	DELAY
		RR		A				;��ɨ������λ
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L2		;ģʽ2��ʾ���?
		INC		DSP_CNT			;��ʾ��һģʽ
		MOV		RS_CNT,#00H
		LJMP	A0
DSP_3:	MOV		P3,#0FFH		;��ʾģʽ3,����ȫ����1
	 	MOV		A,#0FEH			;��ɨ�����ֵ
	L3:	MOV		P0,A			;�����ʾ
		LCALL	DELAY
		RL		A				;��ɨ������λ
		INC		RS_CNT
		MOV		R0,RS_CNT
		CJNE	R0,#24,L3		;ģʽ3��ʾ���?
		MOV		DSP_CNT,#00H	;��ʾ��һģʽ
		MOV		RS_CNT,#00H
		LJMP	A0

DELAY:	MOV		R5,#10			;��ʱ�ӳ���
D1:		MOV		R6,#20
D2:		MOV		R7,#248
		DJNZ	R7,$
		DJNZ	R6,D2
		DJNZ	R5,D1
		RET

		END