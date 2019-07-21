#pragma once
/* ---------------------------------------------------------------------------------
 *          GLOBAL Classes and Structures
 * ----------------------------------------------------------------------------------
 */

#include <externIO.h>           // external definitions and headers for cpu..eep

// ---------------------- Definition of the Global class ----------------------------

class Globals
{
public:                                                 // ======= A1. Add here all volatile parameters 
    
    void initVolatile()                                 // ======= A2. Initialize here the volatile parameters
    {
        ;
    }    
    void printVolatile( char *prompt="", BUF *bp=NULL ) // ======= A3. Add to buffer (or print) all volatile parms
    {
        ;
    }
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
        ;
    }
    void printMyEEParms( char *prompt="", BUF *bp=NULL ) // ======= B4. Add to buffer (or print) all volatile parms
    {
        PF( "%s\r\n", prompt );
        PF( "itest\t= %d\r\n", gp.itest );
    }    
    #include <GLOBAL.hpp>                               // Common code for all Global implementations
    
//    void initAllParms( int myMagic  )       
//    void fetchMyEEParms()
//    void saveMyEEParms()
};

// Exported class
extern Globals myp;                                     // allocated by Globals.cpp       
  
//  class Globals
//{
//public:
//    byte *bpntr;                // pointer to free space
//    int bsize;                  // set by constructor
//
//    struct mee_t                // EEPROM PARAMETERS
//    {                           
//        int test;               // add here user parameters
//    } mee; 
//    #define MEE_SIZE sizeof( mee_t )
//    
//    void initMyParms( bool saveflag )                   // (2a) initialize parameters in memory
//    {
//        if (saveflag) 
//            saveMyParms();                                  // and save the new values     
//    }
//    Globals()
//    {
//        initMyParms( false );                           // initialize parameters in memory
//        bsize = MEE_SIZE;                               // size of all parameters
//        bpntr = new byte [bsize];                       // allocate this in the heap
//    }
//    #define MEE_SIZE sizeof( mee_t )
//    
//    ~Globals() { delete [] bpntr; }
//    
//    void fetchMyParms()                                 // (2b) OR, fetch them from EEPROM
//    {
//         PF("Fetching %d mee_t parms\r\n", sizeof( mee_t ) );         
//         eep.fetchUserStruct( bpntr, bsize );          
//         memcpy( &mee, bpntr, MEE_SIZE );
//    }        
//    void saveMyParms()                                  // (3) use after modifying myp.parameters
//    {
//        memcpy( bpntr, &mee, MEE_SIZE );                // copy mee_t
//        PF("Saving %d mee_t parms\r\n", MEE_SIZE );        
//        eep.saveUserStruct( bpntr, bsize );
//    }
//};
//
//// Exported class
//extern Globals myp;                                     // allocated by Globals.cpp       
  
