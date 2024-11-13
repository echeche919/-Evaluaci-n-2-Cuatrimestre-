#include "MKL25Z4.h"
#include "LCD_I2C.h"

#define I2C_W 0
#define I2C_R 1
#define MSB
#define LSB
#define columnas[4] = {0x80, 0xC0, 0x94, 0xD4};

void LCD_Init(void){
    SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
    SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

    PORTB->PCR[2] = PORT_PCR_MUX(2);
    PORTB->PCR[3] = PORT_PCR_MUX(2); 
    
    I2C0->F = I2C_F_ICR(0x14) | I2C_F_MULT(0); // 100 kHz
    I2C0->C1 |= I2C_C1_IICEN_MASK; 

    I2C0->C1 |= I2C_C1_TX_MASK;       // Poner en modo transmisión
    I2C0->C1 |= I2C_C1_MST_MASK; 
}
void LCD_Clear(){
    LCD_Command(00000001);
}
void LCD_Print(char *texto){
    while(*texto){
        LCD_Write(*texto++);
    }
}
void LCD_SetCursor(int fila, int colum){
   int aux = 0;
   switch fila{
        case 0:
         aux = 000;
        break;
        case 1:
         aux = 001;
        break;
        case 2:
         aux = 010;
        break;
        case 3:
         aux = 011;
        break;
   }
    LCD_Command(aux|columnas[colum]);
}
void LCD_Command(uint8_t command){
    LSB = (command << 4)& F0;
    MSB = (command)& F0;
    LCD_Write(LSB|0x80);
    LCD_Write(MSB|0x80);    
}
void LCD_Write(uint8_t data){
    I2C_Start();
    I2C_WriteByte((0x27 << 1) | I2C_W); 
    I2C_WriteByte(20);
    I2C_WriteByte(data);                              
    I2C_Stop();
}
void LCD_ScrllDisplayRight(){
    LCD_Write(00000110);
}
void LCD_ScrllDisplayLeft(){
    LCD_Write(00000111);
}