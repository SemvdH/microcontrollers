/*
 * main.c
 *
 * Created: 2/10/2021 11:45:42 AM
 *  Author: Sem
 */ 

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char Numbers [10] = {
	// dPgfe dcba
	0b 0011 1111, // 0
	0b 0000 0110, // 1
	0b 0101 1011, // 2
	0b 0100 1111, // 3
	0b 0110 0110, // 4
	0b 0110 1101, // 5
	0b 0111 1101, // 6
	0b 0000 0111, // 7
	0b 0111 1111, // 8
	0b 0110 1111, // 9
};

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}