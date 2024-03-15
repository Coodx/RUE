/*

For ESP32 UWB or ESP32 UWB Pro

3/15/24
got 1 to 1 working need to try 2a to 1t, then display it

*/
float ToFreedom(char typeIn, float value, char typeTo);

#include <SPI.h>
#include "DW1000Ranging.h"

#define ANCHOR_ADD "86:17:5B:D5:A9:9A:E2:9C"

#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

//to freedom units
float ToFreedom(char typeIn, float valuein, char typeTo)
{
    float democracy = 0;
    // Serial.print(typeIn);
    // Serial.print(valuein);
    // Serial.print(typeTo);

    // if (typeIn == 'm'){
    //     if (typeTo == 'i')
    //     {
    //         democracy = valuein * 39.3701;
    //     }
    // }

    switch(typeIn)
    {
        case 'm':
        //Serial.print("TypeTo \n");
            switch(typeTo){
                case 'i':
                    democracy = valuein * 39.37;
                    Serial.print(democracy);
                    Serial.println(" in");
                    return democracy;
                    break;
                    
                case 'f':
                    democracy = valuein * 3.28;    
                    Serial.print(democracy); 
                    Serial.println(" f");
                    return democracy;       
                    break;
                    
            default:
                Serial.print("Type out Selection not valid: i(inches), f(ft)");
                return democracy;     
                break;
            }
    default:
        Serial.print("Type In Selection not valid: m(meters) ");
        Serial.print(typeIn);
        Serial.print(valuein);
        Serial.print(typeTo);
        Serial.println(democracy);
        return democracy;
        //  return democracy;
        break;
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    //init the configuration
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
    //define the sketch as anchor. It will be great to dynamically change the type of module
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newBlink);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    //DW1000Ranging.useRangeFilter(true);

    //we start the module as an anchor
    // DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);

    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_LOWPOWER);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_LOWPOWER);
    DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_ACCURACY);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_ACCURACY);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

void loop()
{
    DW1000Ranging.loop();
}

void newRange()
{
    float rangeIn;

    //Serial.print("from: ");
    //Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    // Serial.print("\t Range: ");
    rangeIn = DW1000Ranging.getDistantDevice()->getRange();
    Serial.println(rangeIn);
    ToFreedom('m',rangeIn, 'i');
    //Serial.print(ToFreedom('m',rangeIn, 'f'));


   // Serial.print("\t RX power: ");
   // Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
   // Serial.println(" dBm");
}

void newBlink(DW1000Device *device)
{
    Serial.print("blink; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}
