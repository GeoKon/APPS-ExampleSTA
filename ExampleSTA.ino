/* ---------------------------------------------------------------------------
 *  Example of a simple WEB application. Should be used as a template
 *  to create other applications.
 *  
 *  Use/Modify the ExampleSTA.cpp to include the specific STA callbacks
 *  Use/Modify the ExampleAP.cpp to include AP mode functionality
 *  The above should include SimpleSRV.cpp with the baseline WEB functions
 *  --------------------------------------------------------------------------
 */
    #include <ESP8266WebServer.h>
    #include <ESP8266mDNS.h>        // Include the mDNS library
    
    #include <FS.h>

    #include "cliHandlers.h"        // in this local directory
    #include "Globals.h"            // in this local directory
    #include "eepTable.h"           // in GKE-L2
    #include "SimpleSRV.h"          // in GKE-Lw
    #include "SimpleSTA.h"          // in GKE-Lw
    #include <externIO.h>           // external definitions and headers for cpu..eep

#define CLI_WAITSEC 10              // how long to wait before RETURN is sensed for CLI
#define WIFI_TIMEOUT_SEC 5      

// ---------- allocation of classes used in this application ------------------
    CPU cpu;
    CLI cli;
    EXE exe;
    EEP eep;
    ESP8266WebServer server(80);   
    
    BUF buffer(1024);           // cli buffer used by cliCallbacks()
           
// ------ Forward References (located in this module --------------------------
    
    void setupSTA();
    void initEEParms();

// ----------------------------- Main Setup -----------------------------------
void setup() 
{
    cpu.init(); 
    ASSERT( SPIFFS.begin() );

    initEEParms();

    exe.registerTable( mypTable );               // register CLI tables
    exe.registerTable( eepTable ); 
    exe.printTables( "See all tables" );  

    cli.init( ECHO_ON, "cmd: " );               // prepare CLI

    PF( "----- For CLI, press CR within %dsec\r\n", CLI_WAITSEC );

    for( int i=0; i<CLI_WAITSEC*100; i++ )
    {
        if( (i%100)==0 ) PR(".");
        if( Serial.read() == 0x0D )
            interactForever();
        delay(10);
    }
    setupSTA();
    srvCallbacks( server, Landing_STA_Page );   // standard WEB callbacks. "staLanding" is /. HTML page
    cliCallbacks( server, buffer );             // enable WEB CLI with buffer specified

    setTrace( T_REQUEST | T_JSON );             // default trace    
    server.begin( 80 );                         // start the server
    PRN("HTTP server started.");
    
    cli.init( ECHO_ON, "cmd: " );
}

void loop()
{
    if( cli.ready() )               // handle serial interactions
    {
        char *p = cli.gets();
        exe.dispatchConsole( p );
        cli.prompt();                
    }
    server.handleClient();    
}

// ------------------- initialize eeprom parms --------------------------------------
#define myMAGIC 0xBABE
void initEEParms()
{
    if( !eep.checkEEParms( myMAGIC, myp.bsize ) )      // fetches parameters and returns TRUE or FALSE
    {
        PF("=== Initializing parms!\r\n" );
        eep.initHeadParms( myMAGIC, myp.bsize );        // initialize header parameters AND save them in eeprom
        eep.initWiFiParms();                            // initialize with default WiFi AND save them in eeprom
        
        myp.initMyParms( true );                        // initialize named parameters AND save them in EEPROM
        PF("AFTER INITIALIZATION\r\n");
    }
    eep.incrBootCount();
    myp.fetchMyParms();                                 // retrieve parameters from EEPROM
    eep.printHeadParms("--- Current Head Parms");       // print current parms
    eep.printWiFiParms("--- Current WiFi Parms");                 
}
