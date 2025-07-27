#include <xc.h>
#include "can.h"
#include "main.h"
#include "uart.h"

void init_config(void)
{
    init_can();
    init_uart();
    GIE=1;
    PEIE=1;
//    puts("suiii");
//    puts("\n\r");
}


void main(void) 
{
    
    init_config();
    
    int i=0;
    
    while(1)
    {
        if(can_receive())
        {
            puts("UPDATED_STOCK:");
            while(i!=4)
            {
                putch(can_payload[D0+i]);
                i++;
            }
            puts("\n\r");
            puts("PRODUCT_ID:");
            while(i!=8)
            {
                putch(can_payload[D0+i]);
                i++;
            }
            puts("\n\r");
            i=0;
        }
        else
        {
            if(flag==1)
            {
                puts("enter the update stock max 4 digit: ");
                flag=-1;
            }
            else if(flag==0)
            {
                puts("enter the product stock max 4 digit: ");
                flag=-1;
            }
            
            if (ch != '\0')
            {
                putch(ch);
                
                if(ch!='\r')
                {
                    if(count == 0 )
                    {
                        if(ch>='0' && ch<='9' && data1_index < 4)
                        {
                            data1[data1_index]=ch;
                            data1_index++;
                        }
                        
                    }
                    else if(count==1)
                    {
                        if(ch>='0' && ch<='9' && data2_index < 4)
                        {
                            data2[data2_index]=ch;
                            data2_index++;
                        }
                    }
                }
                else
                {
                    count++;
                    puts("\n\r");
                    if(count==1)
                        flag=0;
                    else if(count==2)
                        flag=1;
                    
                    if(flag==0 && data1_index!=4)
                    {
                        
                        if(data1_index==0)
                        {
                            for(int i=0;i<4;i++)
                            {
                                data1[i]='0';
                            }
                        }
                        else if(data1_index==1)
                        {
                            data1[3]=data1[0];
                            data1[2]='0';
                            data1[1]='0';
                            data1[0]='0';
                        }
                        else if(data1_index==2)
                        {
                            data1[2]=data1[0];
                            data1[3]=data1[1];
                            data1[1]='0';
                            data1[0]='0';
                        }
                        else if(data1_index==3)
                        {
                            data1[3] = data1[2];
                            data1[2] = data1[1];
                            data1[1] = data1[0];
                            data1[0] = '0';
                        }
                        
                    }
                    else if(flag==1 && data2_index!=4)
                    {
                        if(data2_index==0)
                        {
                            for(int i=0;i<4;i++)
                            {
                                data2[i]='0';
                            }
                        }
                        else if(data2_index==1)
                        {
                            data2[3]=data2[0];
                            data2[2]='0';
                            data2[1]='0';
                            data2[0]='0';
                        }
                        else if(data2_index==2)
                        {
                            data2[2]=data2[0];
                            data2[3]=data2[1];
                            data2[1]='0';
                            data2[0]='0';
                        }
                        else if(data2_index==3)
                        {
                            data2[3] = data2[2];
                            data2[2] = data2[1];
                            data2[1] = data2[0];
                            data2[0] = '0';
                        }
                        
                    }
                }
                if(count==2)
                {
                    count=0;
                    data1[4]='\0';
                    data2[4]='\0';
                    for(int i=0;i<=4;i++)
                    {
                        putch(data1[i]);
                        
                    }
                    for(int i=0;i<=4;i++)
                    {
                        putch(data2[i]);
                        
                    }
                    puts("\n\r");
                    can_transmit();
                    data1_index=0;
                    data2_index=0;
                    
                }

                ch = '\0';
            }
           
            
            
        }
        
    }
    
}