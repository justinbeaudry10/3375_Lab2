#include "address_map_arm.h";

volatile int *timer_ptr = (int *)MPCORE_PRIV_TIMER;
volatile int *seconds_display_ptr = (int *)HEX3_HEX0_BASE;
volatile int *minutes_display_ptr = (int *)HEX5_HEX4_BASE;

typedef struct _A9_timer
{
    int load;
    int curVal;
    int control;
    int interruptStatus;
} A9_timer;

// Displays number on 7 seg display
void DisplayHex(int ms, int s, int min)
{
    char lookUpTable[10];
    lookUpTable[0] = 0x3F;
    lookUpTable[1] = 0x06;
    lookUpTable[2] = 0x5B;
    lookUpTable[3] = 0x4F;
    lookUpTable[4] = 0x66;
    lookUpTable[5] = 0x6D;
    lookUpTable[6] = 0x7D;
    lookUpTable[7] = 0x07;
    lookUpTable[8] = 0x7F;
    lookUpTable[9] = 0x67;

    // Displaying seconds and milliseconds
    *seconds_display_ptr = lookUpTable[s / 10] << 24 | lookUpTable[s % 10] << 16 | lookUpTable[ms / 10] << 8 | lookUpTable[ms % 10];

    // Displaying minutes
    *minutes_display_ptr = lookUpTable[min / 10] << 8 | lookUpTable[min % 10];
}

// Reads switches
int ReadSwitches(void)
{
    volatile int *SW_ptr = (int *)SW_BASE;
    return (*(SW_ptr));
}

// Reads buttons
int ReadButtons(void)
{
    volatile int *BTN_ptr = (int *)KEY_BASE;
    return (*(BTN_ptr));
}

int main(void)
{
    volatile int DELAY_LENGTH = 2000000; // Hundredth of a second because 1 second = 200,000,000 for 200Mhz clock

    // Set to 1 if timer is running
    int runnning = 0;

    // Initial timer values
    int ms = 0;
    int s = 0;
    int min = 0;

    // Initial lap values
    int lap_ms = 0;
    int lap_s = 0;
    int lap_min = 0;

    // Sets initial display to 00:00:00
    DisplayHex(ms, s, min);

    while (1)
    {
    }
}