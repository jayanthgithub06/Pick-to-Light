#include <xc.h>
#include "digital_keypad.h"
#include "ssd_display.h"
#include "external_interrupt.h"
#include "main.h"
#include "eeprom.h"
#include "can.h"


void update_stock_function(void)
{
    if(display_flag_update==0)
    {
        display(update);

    }
    
    if (update_save_flag==1 && key == SWITCH3)
    {
        can_transmit();
        sw2_flag=0;
        interrupt_flag=0;
        display_flag_product=0;
        display_flag_update=0;
        sw3_flag=0;
        update_save_flag=0;
        
        write_internal_eeprom(0x10,count3);
        write_internal_eeprom(0x11,count2);
        write_internal_eeprom(0x12,count1);
        write_internal_eeprom(0x13,count);
        
//        store_data_update_stock();

        count=0,count1=0,count2=0,count3=0;
        read_update_flag=1;
        
       
    }
    
    
    if(key==SWITCH2)
    {
        update_save_flag=1;
        if(read_update_flag)
        {
            
//            read_data_update_stock();
//            char c3,c2,c1,c;
            count3 = read_internal_eeprom(0x10);
           
   
            count2 = read_internal_eeprom(0x11);
            
    
            count1 = read_internal_eeprom(0x12);
            
            
    
            count = read_internal_eeprom(0x13);
            
            read_update_flag=0;
            
        }
        
        display_flag_update=1;
        
       if (sw2_flag < 4)
       {
          sw2_flag++;
       }
       else
       {
          sw2_flag = 1;
       }
 
    }
    
    if(display_flag_update==1)
    {
        if (sw2_flag == 1)
        {

            update_stock();
//            if(key==SWITCH1)
//            count++;
//
//
//            ssd[0] = digit[count3];
//            ssd[1] = digit[count2];
//            ssd[2] = digit[count1];
//            ssd[3] = digit[count%10] | DOT;
            

        }
        else if (sw2_flag == 2)
        {
            update_stock1();

//            if(key==SWITCH1)
//            count1++;
//
//            ssd[0] = digit[count3];
//            ssd[1] = digit[count2];
//            ssd[2] = digit[count1%10] | DOT;
//            ssd[3] = digit[count];
            

        }
        else if (sw2_flag == 3)
        {
            update_stock2();
//            if(key==SWITCH1)
//            count2++;
//
//            ssd[0] = digit[count3];
//            ssd[1] = digit[count2%10] | DOT;
//            ssd[2] = digit[count1];
//            ssd[3] = digit[count];
            

        }
        else if (sw2_flag == 4)
        {
            update_stock3();
//             if(key==SWITCH1)
//                count3++;
//
//            ssd[0] = digit[count3%10] | DOT;
//            ssd[1] = digit[count2];
//            ssd[2] = digit[count1];
//            ssd[3] = digit[count];
            

        }
        display(ssd);
    }
    
}

void compare_check(void)
{
    int index=0;
    for(int i=21;i<=24;i++)
    {
        char ch = read_internal_eeprom(i)+48;
        if(received_pt_id[index] == ch);
            index++;

    }
    if(index==4)
    {
        receive_flag=0;
        update_flag=0;
    }
    else
    {
        receive_flag=1;
    }
}
void received_data_from_server(void)
{
    static int once_read_can_data =1,num;
    if(once_read_can_data)
    {
        for(unsigned int i=0;i<4;i++)
        {
            num = (num * 10) + (received_up_stk[i]-48);
        }
        once_read_can_data=0;
    }
    if(key==SWITCH1)
    {
        num++;
        if(num>9999)
            num=0;
        else if(key==SWITCH3)
        {
            sw3_flag=0;
            display_flag_update=0;
            interrupt_flag=0;
            sw2_flag=0;
            receive_flag=1;
            update_flag=1;
            receive_conform_flag=0;
            
            write_internal_eeprom(0x10,(num/1000));
            write_internal_eeprom(0x11, ((num/100)%10));
            write_internal_eeprom(0x12,((num/10)%10));
            write_internal_eeprom(0x13,(num%10));
            num=0;
//            can_transmit();
        }
        ssd[0]=digit[num/1000];
        ssd[1]=digit[(num/100)%10];
        ssd[2]=digit[(num/10)%10];
        ssd[3]=digit[num%10];
        display(ssd);
    }
}

void update2_stk(void)
{
    if(read_one_time)
    {
        count3 = read_internal_eeprom(0x10);
        count2 = read_internal_eeprom(0x11);
        count1 = read_internal_eeprom(0x12);
        count = read_internal_eeprom(0x13);
        read_one_time=0;
    }
    if(key==SWITCH3)
    {
        write_internal_eeprom(0x10,count3);
        write_internal_eeprom(0x11,count2);
        write_internal_eeprom(0x12,count1);
        write_internal_eeprom(0x13,count);
        
        interrupt_flag=0;
        normal_client_flag=1;
        display_flag_update=0;
        display_flag_product=0;
        
    }
    
    if(key==SWITCH2)
    {
        
//        count3 = read_internal_eeprom(0x10);
//        count2 = read_internal_eeprom(0x11);
//        count1 = read_internal_eeprom(0x12);
//        count = read_internal_eeprom(0x13);
       if (dp_flag < 4)
       {
          dp_flag++;
       }
       else
       {
          dp_flag = 1;
       }
        
    }
    if(dp_flag==1)
        update_stock();
    else if(dp_flag==2)
        update_stock1();
    else if(dp_flag==3)
        update_stock2();
    else if(dp_flag==4)
        update_stock3();
    
    display(ssd);
            
            
        
}




