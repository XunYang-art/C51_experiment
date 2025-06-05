#include <reg51.h>


unsigned char code segmentCodes[] = {
    0x03, 0x9F, 0x25, 0x0D, 0x99, 
    0x49, 0x41, 0x1F, 0x01, 0x09
};

void delay(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 125; j++); 
}

void main() {
    unsigned char i;
    SCON = 0x00; // ´®¿ÚÄ£Ê½0
    while (1) 
    {
        for (i = 0; i < 10; i++) 
        {
            SBUF = segmentCodes[i]; 
            while (!TI); 
            TI = 0; 
            delay(500); 
        }
    }
}