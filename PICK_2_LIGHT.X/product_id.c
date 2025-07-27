#include <xc.h>
#include "digital_keypad.h"
#include "ssd_display.h"
#include "external_interrupt.h"
#include "main.h"
#include "eeprom.h"
#include "can.h"


void product_id_function(void)
{
    if(display_flag_product==0)
    {
        display(product);
    }
  
    if (product_save_flag==1 && key == SWITCH3)
    {
//         while(1);
        sw2_flag=0;
        interrupt_flag=0;
        display_flag_product=0;
        display_flag_update=0;
        sw3_flag=0;
        product_save_flag=0;
        
        write_internal_eeprom(0x21,count3);
        write_internal_eeprom(0x22,count2);
        write_internal_eeprom(0x23,count1);
        write_internal_eeprom(0x24,count);
        count=0,count1=0,count2=0,count3=0;
        read_product_flag=1;
        
        
                
    }
        
    
    
    if(key==SWITCH2)
    {

        product_save_flag=1;

        
//        if(read_product_flag)
//        {
            
//            read_data_product_stock();
            count3 = read_internal_eeprom(0x21);
            count2 = read_internal_eeprom(0x22);
            count1 = read_internal_eeprom(0x23);
            count = read_internal_eeprom(0x24);
            
//            read_product_flag=0;
//        }
        display_flag_product=1;
        
       if (sw2_flag < 4)
       {
          sw2_flag++;
       }
       else
       {
          sw2_flag = 1;
       }
 
    }
    
    if(display_flag_product==1)
    {
        if (sw2_flag == 1)
        {

    //        update_stock();
            write_internal_eeprom(0x24,count);

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

        }
        else if (sw2_flag == 2)
        {
    //        update_stock1();
            write_internal_eeprom(0x23,count1);
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
        else if (sw2_flag == 3)
        {
    //        update_stock2();
            write_internal_eeprom(0x22,count2);
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
        else if (sw2_flag == 4)
        {
    //        update_stock3();
            write_internal_eeprom(0x21,count3);
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
        display(ssd);
    }
    
}
