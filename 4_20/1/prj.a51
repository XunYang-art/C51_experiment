ORG 0000H        ; ������ʼ��ַ
MOV DPTR, #2000H ; �����ⲿRAM��ʼ��ַ
MOV R0, #20H     ; �����ڲ�RAM��ʼ��ַ
MOV R2, #31H     ; ����ѭ������

LOOP:
MOVX A, @DPTR    ; ��ȡ�ⲿRAM���ݵ��ۼ���A
MOV @R0, A       ; �����ݴ����ڲ�RAM
MOV A, #0        ; ׼����������
MOVX @DPTR, A    ; ���ⲿRAMԭ��ַ����
INC DPTR         ; �ⲿ��ַָ���1
INC R0           ; �ڲ���ַָ���1
DJNZ R2, LOOP    ; ѭ������

END              ; �������
    
    
    ;Ƭ��RAM��2000H---2030H��Ԫ�����ݣ�ȫ���Ƶ�Ƭ��RAM��20H---50H��Ԫ
    