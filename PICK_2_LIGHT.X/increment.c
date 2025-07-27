#include <xc.h>
#include "digital_keypad.h"
#include "ssd_display.h"
#include "external_interrupt.h"
#include "main.h"
#include "eeprom.h"

void update_stock(void)
{
    
//    write_internal_eeprom(0x13,count);
    
    ssd[0] = digit[count3];
    ssd[1] = digit[count2];
    ssd[2] = digit[count1];
    ssd[3] = digit[count] | DOT;
    
    if (key == SWITCH1) 
    {
        if (count < 9)
            count++;
        else
            count = 0;
    }
    
//    display(ssd);
    
    
}
void update_stock1(void)
{
//    if(key==SWITCH1)
//        count1++;
//    write_internal_eeprom(0x12,count1);
    ssd[0] = digit[count3];
    ssd[1] = digit[count2];
    ssd[2] = digit[count1] | DOT;
    ssd[3] = digit[count];
    
//    display(ssd);
    if (key == SWITCH1) 
    {
        if (count1 < 9)
            count1++;
        else
            count1 = 0;
    }
    
    
}
void update_stock2(void)
{
//    if(key==SWITCH1)
//        count2++;
//    write_internal_eeprom(0x11,count2);
    ssd[0] = digit[count3];
    ssd[1] = digit[count2] | DOT;
    ssd[2] = digit[count1];
    ssd[3] = digit[count];
    
//    display(ssd);
    
    if (key == SWITCH1) 
    {
        if (count2 < 9)
            count2++;
        else
            count2 = 0;
    }
    
    
    
}
void update_stock3(void)
{
//    if(key==SWITCH1)
//        count3++;
//    write_internal_eeprom(0x10,count3);
    ssd[0] = digit[count3] | DOT;
    ssd[1] = digit[count2];
    ssd[2] = digit[count1];
    ssd[3] = digit[count];
    
//   display(ssd);
    if (key == SWITCH1) 
    {
        if (count3 < 9)
            count3++;
        else
            count3 = 0;
    }
    
}
