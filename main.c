#include "MKL25Z4.h"
#include "LCD_I2C.h"

int cont = 0;

int main(){
    while(1){
        LCD_Init()
        tiempo = millis() - 1000 * cont;
        if(tiempo == 1000){
            LCD_Print(cont);
        }
    }
}