#include <xc.h>
#include "digital_keypad.h"
#include "ssd_display.h"
#include "external_interrupt.h"
#include "main.h"
#include "eeprom.h"


void store_data_update_stock(void)
{
    write_internal_eeprom(0x00,count3);
    write_internal_eeprom(0x01,count2);
    write_internal_eeprom(0x02,count1);
    write_internal_eeprom(0x03,count);
    
}
void read_data_update_stock(void)
{
//    char up0,up1,up2,up3;
    
    count3 = read_internal_eeprom(0x10);
   
    count2 = read_internal_eeprom(0x11);
    
    count1 = read_internal_eeprom(0x12);
    
    count = read_internal_eeprom(0x13);
    
    

}

void store_data_product_stock(void)
{
    write_internal_eeprom(0x04,count3);
    write_internal_eeprom(0x05,count2);
    write_internal_eeprom(0x06,count1);
    write_internal_eeprom(0x07,count);
    
}
void read_data_product_stock(void)
{
//    char pr0,pr1,pr2,pr3;
    
    count3 = (read_internal_eeprom(0x04));
    count2 = (read_internal_eeprom(0x05));
    count1 = (read_internal_eeprom(0x06));
    count = (read_internal_eeprom(0x07));
    
}


