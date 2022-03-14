#include "address_map_arm.h";

volatile int *timer_ptr = (int *)MPCORE_PRIV_TIMER;
volatile int *seconds_display_ptr = (int *)HEX3_HEX0_BASE;
volatile int *hour_display_ptr = (int *)HEX5_HEX4_BASE;

typedef struct a9_timer
{
    int load;
    int curVal;
    int control;
    int interruptStatus;
};

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

    // Initial timer values
    int ms = 0;
    int s = 0;
    int min = 0;

    // Initial lap values
    int lap_ms = 0;
    int lap_s = 0;
    int lap_min = 0;

    DisplayHex(ms, s, min);
}