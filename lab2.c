#include "address_map_arm.h";

// For simulator
// #define MPCORE_PRIV_TIMER 0xFFFEC600
// #define HEX3_HEX0_BASE 0xFF200020
// #define HEX5_HEX4_BASE 0xFF200030
// #define SW_BASE 0xFF200040
// #define KEY_BASE 0xFF200050

// volatile int *timer_ptr = (int *)MPCORE_PRIV_TIMER;
volatile int *seconds_display_ptr = (int *)HEX3_HEX0_BASE;
volatile int *minutes_display_ptr = (int *)HEX5_HEX4_BASE;

typedef struct _a9_timer
{
    int load;
    int count;
    int control;
    int status;
} a9_timer;

int main(void)
{
    // Pointer to timer
    volatile a9_timer *const timer = (a9_timer *)MPCORE_PRIV_TIMER;
    int interval = 2000000; // Interval for counting 1/100th of a sec for 200MHz clock with no prescaler

    int curCount = 0;
    int lastCount = interval;

    // Initialize timer for 1ms interval
    timer->load = interval;
    // Clear any prev timeout flag
    timer->status = 1;
    // Start timer for continuous counting
    timer->control = 3;

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

    // Main loop
    while (1)
    {
        // Wait until timer counts down
        while (timer->status == 0)
            ;
        // Clear timeout flag
        timer->status = 1;

        if (ms == 99)
        {
            ms = 0;
            if (s == 59)
            {
                s = 0;
                if (min == 59)
                {
                    min = 0;
                }
                else
                    min++;
            }
            else
                s++;
        }
        else
            ms++;

        DisplayHex(ms, s, min);
    }
}

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
    lookUpTable[9] = 0x6F;

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
int ReadButton(int btn)
{
    volatile int *BTN_ptr = (int *)KEY_BASE;
    return ((*BTN_ptr >> (btn)) & 1);
}
