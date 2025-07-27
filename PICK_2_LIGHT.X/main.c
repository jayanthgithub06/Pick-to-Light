
#include <xc.h>
#include "digital_keypad.h"
#include "ssd_display.h"
#include "external_interrupt.h"
#include "main.h"
#include "eeprom.h"
#include "can.h"

void init_config(void)
{
    init_digital_keypad();
    init_ssd_control(); 
    init_can();
    
    
    init_external_interrupt();
    GIE=1;
    PEIE=1;
    TRISB0=1;
    
}

void main(void) 
{
    init_config();
    

    while (1)
    {
        
        can_receive_data();
        if(interrupt_flag)
        {
            
            if(key_flag)
            {
                key = read_digital_keypad(STATE_CHANGE);
            }
            else
            {
                
                key=read_digital_keypad(LEVEL);
                 
            }
            
            if(normal_client_flag)
            {
            
                if((key==SWITCH3) && (update_save_flag==0) && (product_save_flag==0)) 
                    sw3_flag=!sw3_flag;

                if(sw3_flag)
                {
                    product_id_function();

                }

                else
                {
    //                if(receive_conform_flag==1)
    //                {
    //                    compare_check();
    //                    receive_conform_flag=0;
    //                }
//                    if(update_flag==1)
//                    {
                        update_stock_function();
//                    }

//                    else
//                    {
    //                    can_receive_stock();
//                        received_data_from_server();
//                    }

                }
            }
//            else
//            {
//                if(normal_client_flag==0)
//                {
//    //                if(receive_conform_flag==1)
//    //                {
//    //                    compare_check();
//    //                    receive_conform_flag=0;
//    //                }
//
//                    if(receive_toggle_flag=1)
//                    {
//
//                        ssd[0]=digit[received_up_stk[0]-48];
//                        ssd[1]=digit[received_up_stk[1]-48];
//                        ssd[2]=digit[received_up_stk[2]-48];
//                        ssd[3]=digit[received_up_stk[3]-48];
//                        display(ssd);
//                    }
//                    else
//                    {
////                        update2_stk();
//                        ssd[0]=digit[1];
//                        ssd[1]=digit[2];
//                        ssd[2]=digit[3];
//                        ssd[3]=digit[4];
//                        display(ssd);
//                        
//                    }
//                }
//                
//                
//            }
            
        }
        else
            PORTD=BLANK;
        
        if(normal_client_flag==0)
        {
    //                if(receive_conform_flag==1)
    //                {
    //                    compare_check();
    //                    receive_conform_flag=0;
    //                }

            if(receive_toggle_flag==1)
            {
                key_flag=0;
                static unsigned int delay=0;
                static unsigned int delay1=0;

                static int server_data=0;
                
                 if (server_enter_flag == 1) 
                 {
                    server_data = 0; 
                     for (unsigned int i = 0; i < 4; i++) 
                     {
                        if (received_up_stk[i] >= '0' && received_up_stk[i] <= '9') 
                        { 
                            server_data = (server_data * 10) + (received_up_stk[i] - '0');
                        } 

                    }
                    server_enter_flag = 0;
                }

                if (key == SWITCH1 && delay++==20) 
                {
                    
                    server_data++;
                    if (server_data > 9999) 
                    { 
                        server_data = 0;
                    }
                        delay=0;
                    
                }
                else if (key == SWITCH2 && delay1++==20) 
                {
                    
                    if (server_data > 0) 
                    {
                        server_data--; 
                    } 
                    else 
                    {
                        server_data = 9999; 
                    }
                    delay1=0;
                    
                    
                }
                
                if(key==SWITCH3)
                {
                    write_internal_eeprom(0x10,(server_data/1000));
                    write_internal_eeprom(0x11, ((server_data/100)%10));
                    write_internal_eeprom(0x12,((server_data/10)%10));
                    write_internal_eeprom(0x13,(server_data%10));
                    
                    normal_client_flag=1;
                    server_flag=1;
                    
                    interrupt_flag=0;
                    
                    key_flag=1;
                    server_data=0;
                    
                }

    
                ssd[0] = digit[server_data / 1000];
                ssd[1] = digit[(server_data / 100) % 10];
                ssd[2] = digit[(server_data / 10) % 10];
                ssd[3] = digit[server_data % 10];

                
                display(ssd);
               
            }
            else
            {

                key_flag=1;
                if(read_one_time)
                {
                    count3=read_internal_eeprom(0x10);
                    count2=read_internal_eeprom(0x11);
                    count1=read_internal_eeprom(0x12);
                    count=read_internal_eeprom(0x13);
                    read_one_time=0;
                }
                
                
                if(key==SWITCH3)
                {
                    write_internal_eeprom(0x10,count3);
                    write_internal_eeprom(0x11,count2);
                    write_internal_eeprom(0x12,count1);
                    write_internal_eeprom(0x13,count);
                    
                    count3=0,count2=0,count1=0,count=0;
                    
                    normal_client_flag=1;
                    server_flag=1;
                    interrupt_flag=0;
                    read_one_time=1;
                    dp_flag=1;
                    key_flag=1;
                    
                    
                }
                
                if(key==SWITCH2)
                {
//                    count3=read_internal_eeprom(0x10);
//                    count2=read_internal_eeprom(0x11);
//                    count1=read_internal_eeprom(0x12);
//                    count=read_internal_eeprom(0x13);
                    
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
                {

//                    update_stock();
//                    write_internal_eeprom(0x13,count);
//                    count=read_internal_eeprom(0x13);
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
                else if(dp_flag==2)
                {

//                    update_stock1();
//                    write_internal_eeprom(0x12,count1);
//                    count1=read_internal_eeprom(0x12);
                    
                    ssd[0] = digit[count3];
                    ssd[1] = digit[count2];
                    ssd[2] = digit[count1] | DOT;
                    ssd[3] = digit[count];
    

                    if (key == SWITCH1) 
                    {
                        if (count1 < 9)
                            count1++;
                        else
                            count1 = 0;
                    }
                    
                }
                else if(dp_flag==3)
                {
                   
//                    update_stock2();
//                    write_internal_eeprom(0x11,count2);
//                    count2=read_internal_eeprom(0x11);
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
                else if(dp_flag==4)
                {
//                    update_stock3();
//                    write_internal_eeprom(0x10,count3);
//                    count3=read_internal_eeprom(0x10);
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
       
//        if(receive_toggle_flag)
//        {
//            ssd[0]=digit[received_up_stk[0]-48];
//            ssd[1]=digit[received_up_stk[1]-48];
//            ssd[2]=digit[received_up_stk[2]-48];
//            ssd[3]=digit[received_up_stk[3]-48];
//            display(ssd);
//            
//        }
//        else
//        {
//            update2_stk();
//            
//        }
        
    }
        
}

void can_receive_data(void)
{
    if(can_receive())
    {
        received_up_stk[0]=can_payload[D0+0];
        received_up_stk[1]=can_payload[D0+1];
        received_up_stk[2]=can_payload[D0+2];
        received_up_stk[3]=can_payload[D0+3];
        received_up_stk[4]='\0';
        received_pt_id[0]=can_payload[D0+4];
        received_pt_id[1]=can_payload[D0+5];
        received_pt_id[2]=can_payload[D0+6];
        received_pt_id[3]=can_payload[D0+7];
        received_pt_id[4]='\0';
        
        
//        while(1)
//        {
//            ssd[0] = digit[received_pt_id[0] - '0'];
//            ssd[1] = digit[received_pt_id[1] - '0'];
//            ssd[2] = digit[received_pt_id[2] - '0'];
//            ssd[3] = digit[received_pt_id[3] - '0'];
//
//            display(ssd);
//        }
        
        int index=0;
        
        if(received_pt_id[0]==(read_internal_eeprom(0x21)+48))
            index++;
        if(received_pt_id[1]==(read_internal_eeprom(0x22)+48))
            index++;
        if(received_pt_id[2]==(read_internal_eeprom(0x23)+48))
            index++;
        if(received_pt_id[3]==(read_internal_eeprom(0x24)+48))
            index++;
        
        if(index==4)
        {
             interrupt_flag=1;

            normal_client_flag=0;
            receive_toggle_flag=1;

            server_flag=0;
            server_enter_flag=1;
            read_one_time=1;
            index=0;
            
        }
        else
        {
            normal_client_flag=1;
             server_flag=1;
             server_enter_flag=0;
        }
        
        
//        int index=0;
//        for(int i=21;i<=24;i++)
//        {
//            char ch = read_internal_eeprom(i)+48;
//            if(received_pt_id[index] == ch)
//            {
//                index++;
//            }
//
//        }
//         
//         if(index==4)
//         {
//             interrupt_flag=1;
//
//            normal_client_flag=0;
//
//            server_flag=0;
//            server_enter_flag=1;
//            index=0;
//             
//         }
//         else
//         {
//             normal_client_flag=1;
//             server_flag=1;
//             server_enter_flag=0;
//         }
        
//        interrupt_flag=1;
//
//        normal_client_flag=0;
//        
//        server_flag=0;
//        server_enter_flag=1;

        
        
    }
    
}


