#pragma once
/* ---------------------------------------------------------------------------------
 *          GLOBAL Classes and Structures
 * ----------------------------------------------------------------------------------
 */

#include "nmpClass.h"
#include <IGlobal.h>            // interface class including external definitions and headers for cpu..eep

#define MAGIC_CODE 0x3232

extern NMP nmp;                 // allocated in myGlobals.cpp; used only by this                             

// ---------------------- Definition of the Global class ----------------------------

class Global: public IGlobal
{
public:                                                 // ======= A1. Add here all volatile parameters 
    
    void initVolatile(){;}                              // ======= A2. Initialize here the volatile parameters
    void printVolatile( char *prompt="", 
                        BUF *bp=NULL ){;}               // ======= A3. Add to buffer (or print) all volatile parms
    struct gp_t                                         // ======= B1. Add here all non-volatile parameters into a structure
    {                           
        int   itest;                
    } gp;
    
    void initMyEEParms()                                // ======= B2. Initialize here the non-volatile parameters
    {
        gp.itest = 10;
    } 
    void registerMyEEParms()                            // ======= B3. Register parameters by name
    {   
        nmp.resetRegistry();
        nmp.registerParm( "itest", 'i', &gp.itest,    "Test int" );
        PF("%d named parameters registed\r\n", nmp.getParmCount() );
        ASSERT( nmp.getSize() == sizeof( gp_t ) );
    }
    void printMyEEParms( char *prompt="", BUF *bp=NULL ) // ======= B4. Add to buffer (or print) all volatile parms
    {
        PF( "%s\r\n", prompt );
        PF( "itest\t= %d\r\n", gp.itest );
    }    
    void initAllParms()
    {
        initTheseParms( MAGIC_CODE, (byte *)&gp, sizeof( gp ) );
    }
};
// Exported class
extern Global myp;                                     // allocated by Globals.cpp       
  
