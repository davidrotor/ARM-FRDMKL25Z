#include "mbed.h"
#include "TSISensor.h"

Serial device(PTA2, PTA1);  // tx, rx
Ticker tick;
float percent = 0;
float percent1 = 0;
int opt = 0;

void send()
{
    device.putc(percent);
}

void read()
{
    percent1 = device.getc();
}

int main(void)
{
    PwmOut led(LED_GREEN);
    PwmOut led1(LED_BLUE);
    PwmOut led2(LED_RED);

    TSISensor tsi;

    tick.attach(&send,0.01);
    device.attach(&read);

    float valor;
    float valorant;
    float x;
    float y;
    float z;

    while (true) {
        percent = tsi.readPercentage()*10;
        if(percent1 != 0) {
            valor = percent1/10;
        }
        if(valor > 0.80 && valorant < 0.80) {
            opt++;
            if(opt > 3) {
                opt = 0;
            }
        } else {
            if(opt == 0) {
                x = 1.1 - valor;
                led = x;
                led2 = 1;
                led1 = 1;
            }
            if(opt == 1) {
                y = 1.1 - valor;
                led1 = y;
                led2 = 1;
                led = 1;
            }
            if(opt == 2) {
                z = 1.1 - valor;
                led2 = z;
                led1 = 1;
                led = 1;
            }
            if(opt == 3) {
                led2 = z;
                led1 = y;
                led = x;
            }
        }
        wait(0.1);
        valorant = valor;
    }
}