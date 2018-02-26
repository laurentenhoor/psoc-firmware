/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "debug.h"


char* convert(unsigned int, int);       //Convert integer number into octal, hex, etc.

void DebugCode(const char* txt)
{
        uint8_t endline[2] = { '\r', '\n' };
        UART_Dbg_PutArray(endline, 2);
        UART_Dbg_PutArray((uint8_t*)txt, strlen(txt));
        UART_Dbg_PutArray(endline, 2);
}

#if defined(__ARMCC_VERSION)
 /* For MDK/RVDS compiler revise fputc function for printf functionality */
 struct __FILE
 {
     int handle;
 };
 enum
 {
     STDIN_HANDLE,
     STDOUT_HANDLE,
     STDERR_HANDLE
 };
 FILE __stdin = {STDIN_HANDLE};
 FILE __stdout = {STDOUT_HANDLE};
 FILE __stderr = {STDERR_HANDLE};
 int fputc(int ch, FILE *file)
 {
     int ret = EOF;
     switch( file->handle )
     {
         case STDOUT_HANDLE:
             UART_DEB_UartPutChar(ch);
             ret = ch ;
             break ;
         case STDERR_HANDLE:
             ret = ch ;
             break ;
         default:
             file = file;
             break ;
     }
     return ret ;
 }
 #elif defined (__ICCARM__)      /* IAR */
 /* For IAR compiler revise __write() function for printf functionality */
 size_t __write(int handle, const unsigned char * buffer, size_t size)
 {
     size_t nChars = 0;
     if (buffer == 0)
     {
         /*
          * This means that we should flush internal buffers.  Since we
          * don't we just return.  (Remember, "handle" == -1 means that all
          * handles should be flushed.)
          */
         return (0);
     }
     for (/* Empty */; size != 0; --size)
     {
         UART_DEB_UartPutChar(*buffer++);
         ++nChars;
     }
     return (nChars);
 }
 #else  /* (__GNUC__)  GCC */
 /* For GCC compiler revise _write() function for printf functionality */
 int _write(int file, char *ptr, int len)
 {
     int i;
     file = file;
     for (i = 0; i < len; i++)
     {
         UART_Dbg_PutChar(*ptr++);
     }
     return len;
 }
 #endif  /* (__ARMCC_VERSION) */ 

void sk_printf(char * format,...)
{
    char *traverse; 
    int i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while( *traverse != '%' ) 
        { 
            UART_Dbg_PutChar(*traverse);
            traverse++; 
        } 

        traverse++; 

        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        UART_Dbg_PutChar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            UART_Dbg_PutChar('-'); 
                        } 
                        UART_Dbg_PutString(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        UART_Dbg_PutString(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        UART_Dbg_PutString(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        UART_Dbg_PutString(convert(i,16));
                        break; 
        }   
    } 
    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}
/* [] END OF FILE */
