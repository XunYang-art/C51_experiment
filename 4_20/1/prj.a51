ORG 0000H        ; 程序起始地址
MOV DPTR, #2000H ; 设置外部RAM起始地址
MOV R0, #20H     ; 设置内部RAM起始地址
MOV R2, #31H     ; 设置循环次数

LOOP:
MOVX A, @DPTR    ; 读取外部RAM数据到累加器A
MOV @R0, A       ; 将数据存入内部RAM
MOV A, #0        ; 准备清零数据
MOVX @DPTR, A    ; 将外部RAM原地址清零
INC DPTR         ; 外部地址指针加1
INC R0           ; 内部地址指针加1
DJNZ R2, LOOP    ; 循环控制

END              ; 程序结束
    
    
    ;片外RAM的2000H---2030H单元的内容，全部移到片内RAM的20H---50H单元
    