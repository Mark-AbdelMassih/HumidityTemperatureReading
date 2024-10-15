#include <p18cxxx.h>
#include <delays.h>
#include <LCD4lib.h>

//symbolic defintions (preprocessor) 
#define     inputData       PORTBbits.RB0
#define     outputData      PORTBbits.RB0
#define     dataDirection   TRISBbits.TRISB0


//Method declarations
void Setup(void);
void StartDHT11(void);
void CheckDHT11Response(void);
unsigned char ReadDHT11(void);

//Display measurements messages (default)
char tempStr[ ] = "Temp = 00.00 C";
char RHstr[] = "Humidity=00.00%";

//40 bit data
unsigned char RHinteger, RHdecimal, TempInteger, TempDecimal, CheckSum;
char ValidResponse; // response of the sensor flag

//Error messages
char CheckSumError[] = "CheckSum Error";
char InvalidResponse[] = "Invalid Response";


void main()
{
    Setup();
    Delay10KTCYx(100);                                                              //wait 1 sec before sending signal to DHT11
    while(1) 
    {
        StartDHT11();
        CheckDHT11Response();
        if(ValidResponse) 
        {
            RHinteger = ReadDHT11();                                                //first 8 bits for RH (integer part))
            RHdecimal = ReadDHT11();                                                // second 8 bits of RH (decimal part)
            TempInteger = ReadDHT11();                                              //first 8 bits of temperature 
            TempDecimal = ReadDHT11();                                              //second 8 bits of temperature
            CheckSum = ReadDHT11();                                                 //checksum of all previous 32 bits
            
            if(CheckSum == (RHinteger + RHdecimal + TempInteger + TempDecimal))
            {
                RHstr[9] = RHinteger/10 + '0';                                      // convert MSD to ASCII
                RHstr[10] = RHinteger%10 + '0';                                     //convert LSD to ASCII
                RHstr[12] = RHdecimal/10 + '0';
                RHstr[13] = RHdecimal%10 + '0';
                
                tempStr[7] = TempInteger/10 + '0';
                tempStr[8] = TempInteger%10 + '0';
                tempStr[10] = TempDecimal/10 + '0';
                tempStr[11] =  TempDecimal%10 + '0';
                
                //ASCII of the degree symbol
                tempStr[12] = 0xDF;
                
                DispRamStr(Ln1Ch0, RHstr);
                DispRamStr(Ln2Ch0, tempStr);
            }
            else {
                DispRamStr(Ln1Ch0, CheckSumError);
            }    
        }
        else {
            DispRamStr(Ln1Ch0, InvalidResponse);
        }
    }
}

//setup default configurations
void Setup()
{
    ANSELD = ANSELB = 0x00;                                                         // set all pins as digital
    TRISD = 0x00;                                                                   //output port for the LCD
    INTCON2bits.RBPU = 0;                                                           //enable internal weak pull-ups
    InitLCD();                                                                      //initiate LCD configurations
}

//method definitions
void StartDHT11(void) 
{
     dataDirection = 0;                                                             //set pin as output to send bit '0'
     outputData = 0;                                                                // send bit 0 
     Delay1KTCYx(18);                                                               //18 ms delay
     outputData = 1;                                                                // pull back data bus to high 
     Delay10TCYx(4);                                                                //40 us delay
     dataDirection = 1;                                                             //set pin as input to read response from sensor
}


void CheckDHT11Response(void)
{
    //Delay10TCYx(4);
    if(!inputData)
    {        
       Delay10TCYx(8);                                                              // 80us delay
       if(inputData)
       {
           Delay10TCYx(8);                                                          //80us delay
           ValidResponse = 1;                                                       // successful response           
       }
    }
    else{
        ValidResponse = 0;                                                          //incorrect response
    }
}


unsigned char ReadDHT11(void)
{
    char i,data=0;
    for(i=0; i<8; i++) 
    {
        while(!inputData);                                                          //wait until high signal is sent, takes approx 50us 
        Delay10TCYx(3);                                                             // bit 0 is high for approx 26-28 us
        if(inputData)
        {
            data = data << 1 | 1 ;                                                  //set the bit and shift to the left
        }
        else{
            data = data << 1 ;
        }
        while(inputData);                                                            //wait until 0 is sent to iterate for the next bit
    }
    return data;
}



