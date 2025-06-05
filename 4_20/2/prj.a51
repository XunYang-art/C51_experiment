ORG 0000H           ; 程序起始地址
MOV DPTR, #2000H    ; 设置外部RAM起始地址
MOV R2, #00H        ; 初始化计数器R2清零
MOV R3, #64H        ; 循环次数100次（64H = 100）

LOOP:
MOVX A, @DPTR       ; 读取外部RAM数据到累加器A
CJNE A, #00H, NEXT  ; 比较A与0，不等则跳转
INC R2              ; 若相等计数器R2加1
NEXT:
INC DPTR            ; 外部RAM地址指针加1
DJNZ R3, LOOP       ; 循环次数减1，不为零则继续循环

END                 ; 程序结束
    ;编程统计从片外RAM2000H开始的100个单元中“0”的个数，将结果存放于R2中