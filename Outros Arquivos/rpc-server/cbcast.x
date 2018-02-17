/** 
    Author: Avelino F. Zorzo
    avelino.zorzo@pucrs.br

    Date: 10.03.2001
    Modified: 10.03.2012

   This code will be translated into the needed stubs and headers
   Use: rpcgen cbcast.x

**/


program CBCASTPROG {                /* value to register the program */
    version CBCASTVERS {            /* version must be assigned a value */           
        int START(string)      = 1;   /* this is a service function */  
        int NUMERO(void)       = 2;  
    } =1;                          /* version value */
} = 0x20000003;                    /* program value */   
