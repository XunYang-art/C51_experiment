ORG 0000H          ; 程序起始地址

MOV DPTR, #2000H   ; 指向2000H地址
MOVX A, @DPTR      ; 读取2000H的内容到累加器A
MOV B, A           ; 备份原始数据到寄存器B

SWAP A             ; 将A的高四位与低四位交换（例如0xAB → 0xBA）
ANL A, #0FH        ; 保留低四位，清零高四位（0xBA → 0x0A）
MOV DPTR, #2001H   ; 指向2001H地址
MOVX @DPTR, A      ; 将处理后的高四位存入2001H的低位

MOV A, B           ; 恢复原始数据到A
ANL A, #0FH        ; 保留低四位，清零高四位（例如0xAB → 0x0B）
MOV DPTR, #2002H   ; 指向2002H地址
MOVX @DPTR, A      ; 将处理后的低四位存入2002H的低位

END               ; 程序结束