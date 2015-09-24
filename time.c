#include "time.h"
#include "kwrite.h"
#include "string.h"

//Define some constants
#define CURRENT_CENTURY 20 /*XXI century!!*/
#define MINUTE 60
#define HOUR (MINUTE * 60)
#define DAY (HOUR * 24)
#define YEAR (DAY * 365)
#define LEAP_YEAR (DAY * 366)
#define CENTURY_REG 0x00 /* 0x00 means undefined */
const char DAYS_IN_MONTH_REG[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char DAYS_IN_MONTH_LEAP[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//Define ports for rtc reading
#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

//Define enum for easier register reading
#define NUM_REGS 7
enum t_tim {SEC=0, MIN, HR, DY, MTH, YR, CTR};
unsigned int registers[] = {0x00, 0x02, 0x04, 0x07, 0x08, 0x09, CENTURY_REG};


//Grab read/write functions from kernel.asm
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

//==Private functions

int get_UP_flag() {
          write_port(CMOS_ADDRESS, 0x0A);
                return (read_port(CMOS_DATA) & 0x80);
}
 
unsigned char get_RTC_reg(int reg) {
          write_port(CMOS_ADDRESS, reg);
                return read_port(CMOS_DATA);
}

char is_leap(int year)
{
    if(year%4 != 0)
        return 0;
    else if (year%100!=0)
        return 1;
    else if (year%400!=0)
        return 0;
    else
        return 1;
}

//==Public functions
//Grab 'random' bytes - approx. seconds from 01.01.1970
//TODO move _time and last_time to root of this file, create a separate method for reading, this method
//should call that one, and then calculate timestamp
unsigned long time_grab()
{
    unsigned long result = 0;
    unsigned int _time[NUM_REGS];
    unsigned int last_time[NUM_REGS];
    unsigned char registerB; //To read format of data - binary/decimal/12/24
    int i = 0;
    while (get_UP_flag());                // Make sure an update isn't in progress
    for (i = SEC; i<=YR ;i++){
        _time[i] = get_RTC_reg(registers[i]);
    }
    if(CENTURY_REG != 0) {
        _time[CTR] = get_RTC_reg(registers[CTR]);
    }
    
    do{
        for(i = SEC; i<=CTR ;i++)
            last_time[i] = _time[i];

        while (get_UP_flag());                // Make sure an update isn't in progress
        for (i = SEC; i<=YR ;i++){
            _time[i] = get_RTC_reg(registers[i]);
        }
        if(CENTURY_REG != 0) {
            _time[CTR] = get_RTC_reg(registers[CTR]);
        }

    }while((_time[SEC] != last_time[SEC])||
            (_time[MIN] != last_time[MIN])||
            (_time[HR] != last_time[HR])||
            (_time[DY] != last_time[DY])||
            (_time[MTH] != last_time[MTH])||
            (_time[YR] != last_time[YR])||
            (_time[CTR] != last_time[CTR]));

    //Get format of output
    registerB = get_RTC_reg(0x0B);
    
    //Convert from binary if necesary
    if (!(registerB & 0x04)) {
        _time[SEC] = (_time[SEC] & 0x0F) + ((_time[SEC] / 16) * 10);
        _time[MIN] = (_time[MIN] & 0x0F) + ((_time[MIN] / 16) * 10);
        _time[HR] = ( (_time[HR] & 0x0F) + (((_time[HR] & 0x70) / 16) * 10) ) | (_time[HR] & 0x80);
        _time[DY] = (_time[DY] & 0x0F) + ((_time[DY] / 16) * 10);
        _time[MTH] = (_time[MTH] & 0x0F) + ((_time[MTH] / 16) * 10);
        _time[YR] = (_time[YR] & 0x0F) + ((_time[YR] / 16) * 10);
            if(CENTURY_REG != 0) {
                _time[CTR] = (_time[CTR] & 0x0F) + ((_time[CTR] / 16) * 10);
            }
    }
    
    // Convert 12 hour clock to 24 hour clock if necessary
    if (!(registerB & 0x02) && (_time[HR] & 0x80)) {
        _time[HR] = ((_time[HR] & 0x7F) + 12) % 24;
    }

    // Calculate the full (4-digit) year
    if(CENTURY_REG != 0) {
        _time[YR] += _time[CTR] * 100;
    } else {
        _time[YR] += CURRENT_CENTURY * 100;
    }
    //Print read time:
    char str[10];
    writexy("YEAR: ", 0, 10);
    itostr(_time[YR], 10, str);
    writexy(str, 10, 10);
    writexy("MONTH: ", 0, 11);
    itostr(_time[MTH], 10, str);
    writexy(str, 10, 11);
    writexy("DAY: ", 0, 12);
    itostr(_time[DY], 10, str);
    writexy(str, 10, 12);
    writexy("HOUR: ", 0, 13);
    itostr(_time[HR], 10, str);
    writexy(str, 10, 13);
    writexy("MINUTE: ", 0, 14);
    itostr(_time[MIN], 10, str);
    writexy(str, 10, 14);
    writexy("SECOND: ", 0, 15);
    itostr(_time[SEC], 10, str);
    writexy(str, 10, 15);
      
    //Read and conversion complete, Let's calculate fingerprint
    for(i=1970; i<_time[YR] ;i++)
        result += (is_leap(i))?LEAP_YEAR:YEAR;
    for(i = 1; i<_time[MTH] ; i++)
        if(is_leap(_time[YR]))
            result += DAYS_IN_MONTH_LEAP[i] * DAY;
        else
            result += DAYS_IN_MONTH_REG[i] * DAY;
    result += (_time[DY] - 1)*DAY;
    result += _time[HR] * HOUR;
    result += _time[MIN] * MINUTE;
    result += _time[SEC];
    return result;
}

