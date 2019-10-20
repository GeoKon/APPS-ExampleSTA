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

    #include "eepTable.h"           // in GKE-L2
    #include "SimpleSRV.h"          // in GKE-Lw
    #include "SimpleSTA.h"          // in GKE-Lw
    #include "CommonCLI.h"          // in GKE-Lw
    #include "myCLIHandlers.h"      // in this application
    #include "myGlobals.h"          // in this application
        
    #define CLI_WAITSEC 10          // how long to wait before RETURN is sensed for CLI

// ---------- allocation of classes used in this application ------------------
    CPU cpu;
    CLI cli;
    EXE exe;
    EEP eep;
    ESP8266WebServer server(80);   
    
    BUF buffer(2048);                           // cli buffer 
           
// ------ Forward References (located in this module --------------------------
    
// ----------------------------- Main Setup -----------------------------------
void setup() 
{
    int runcount = setjmp( myp.env );            // env is allocated in IGlobals
    cpu.init(); 
    ASSERT( SPIFFS.begin() );

    myp.initAllParms();

    exe.initTables();                            // clear all tables
    linkParms2cmnTable( &myp );
    exe.registerTable( mypTable );               // register common CLI tables
    exe.registerTable( eepTable ); 
    exe.registerTable( cmnTable );               // register common CLI tables
    exe.printTables( "See all tables" );  

    startCLIAfter( CLI_WAITSEC, &buffer );      // prepare CLI
    setupWiFi();                                // setup WiFi. If AP not found, do SmartConfig
    
    srvCallbacks( server, Landing_STA_Page );   // standard WEB callbacks. "staLanding" is /. HTML page
    cliCallbacks( server, buffer );             // enable WEB CLI with buffer specified

    setTrace( T_REQUEST | T_JSON );             // default trace    
    server.begin( 80 );                         // start the server
    PRN("HTTP server started.");
    
    cli.prompt();
}

void loop()
{
    if( cli.ready() )                   // handle serial interactions
    {
        exe.dispatchBuf( cli.gets(), buffer );
        buffer.print();
        cli.prompt();
    }
    if( checkWiFi() )                  // Good WiFi connection?
    {    
         server.handleClient();
    }
    else                               // no WiFi connection
    {        
        reconnectWiFi();               // if necessary, add callback() here
    }
}
