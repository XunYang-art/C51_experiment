	ORG 0000H
	LJMP MAIN
	ORG 0100H
        
        
MAIN: MOV A, #0FFH           ;�˴��޸�ΪFFH�����ܰ� 2000H-20FFH �е����ݸĳ� FF
	  MOV R0, #00H
      MOV DPTR, #2000H
LOOP1: MOVX @DPTR, A
       INC DPTR
       ;INC R0
       DJNZ R0,LOOP1
       SJMP $
       END

