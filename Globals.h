#pragma once
/* ---------------------------------------------------------------------------------
 *          GLOBAL Classes and Structures
 * ----------------------------------------------------------------------------------
 */

#include <externIO.h>           // external definitions and headers for cpu..eep

// ---------------------- Definition of the Global class ----------------------------

class Globals
{
public:
    byte *bpntr;                // pointer to free space
    int bsize;                  // set by constructor

    struct mee_t                // EEPROM PARAMETERS
    {                           
        int test;               // add here user parameters
    } mee; 
    #define MEE_SIZE sizeof( mee_t )
    
    void initMyParms( bool saveflag )                   // (2a) initialize parameters in memory
    {
        if (saveflag) 
            saveMyParms();                                  // and save the new values     
    }
    Globals()
    {
        initMyParms( false );                           // initialize parameters in memory
        bsize = MEE_SIZE;                               // size of all parameters
        bpntr = new byte [bsize];                       // allocate this in the heap
    }
    #define MEE_SIZE sizeof( mee_t )
    
    ~Globals() { delete [] bpntr; }
    
    void fetchMyParms()                                 // (2b) OR, fetch them from EEPROM
    {
         PF("Fetching %d mee_t parms\r\n", sizeof( mee_t ) );         
         eep.fetchUserStruct( bpntr, bsize );          
         memcpy( &mee, bpntr, MEE_SIZE );
    }        
    void saveMyParms()                                  // (3) use after modifying myp.parameters
    {
        memcpy( bpntr, &mee, MEE_SIZE );                // copy mee_t
        PF("Saving %d mee_t parms\r\n", MEE_SIZE );        
        eep.saveUserStruct( bpntr, bsize );
    }
};

// Exported class
extern Globals myp;                                     // allocated by Globals.cpp       
  
