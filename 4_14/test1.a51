	ORG 0000H
	LJMP MAIN
	ORG 0100H
        
        
MAIN: MOV A, #0FFH           ;此处修改为FFH，则能把 2000H-20FFH 中的内容改成 FF
	  MOV R0, #00H
      MOV DPTR, #2000H
LOOP1: MOVX @DPTR, A
       INC DPTR
       ;INC R0
       DJNZ R0,LOOP1
       SJMP $
       END

