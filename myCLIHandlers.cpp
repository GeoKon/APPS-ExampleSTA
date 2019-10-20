/* ----------------------------------------------------------------------------------
 *  Copyright (c) George Kontopidis 1990-2019 All Rights Reserved
 *  You may use this code as you like, as long as you attribute credit to the author.
 * ---------------------------------------------------------------------------------
 */

#include "myGlobals.h"
#include "myCLIHandlers.h"

#define BINIT( A, ARG )    BUF *A = (BUF *)ARG[0]
#define RESPONSE( A, ... ) if( bp )                     \
                            bp->add(A, ##__VA_ARGS__ ); \
                           else                         \
                            PF(A, ##__VA_ARGS__);
							
// ----------------------------- CLI Command Handlers ---------------------------

    void cliDemo( int n, char **arg )
    {
        BINIT( bp, arg );   
        bool ok;
        if( n<=1 )
        {
            RESPONSE("? Missing <arg>\r\n" );
        }
        else
        {
            RESPONSE( "Enteed number %d\r\n", atoi(arg[1]) ); 
        }
    }
// ============================== CLI COMMAND TABLE =======================================
                     
    CMDTABLE mypTable[]= 
    {
        {"h",       "Help", []( int n, char **arg ){exe.help ( n, arg );} },
        {"demo",    "[mask]. Lists of all commands", cliDemo },
        {NULL, NULL, NULL}
    };

#undef BINIT
#undef RESPONSE
