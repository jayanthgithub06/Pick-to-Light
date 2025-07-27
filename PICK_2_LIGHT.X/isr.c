#include <xc.h>
#include "main.h"

//unsigned char  key_detected;

void __interrupt() isr(void)
{
	if (INT0F == 1)
	{
//		key_detected = 1;
//        if(receive_flag==1)
//        {
        if(server_flag)
            interrupt_flag = !interrupt_flag;
        
        else
            receive_toggle_flag = !receive_toggle_flag;
//        }
//        else if(receive_flag==0)
//        {
//            update_flag = !update_flag;
//            
//        }
        

		INT0F = 0;
	}
}