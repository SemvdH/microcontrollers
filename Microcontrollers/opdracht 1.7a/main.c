// /*
//  * main.c
//  *
//  * Created: 08-Feb-21 10:03:33 AM
//  *  Author: lemms
//  */ 
// # define F_CPU 10000000UL
// 
// #include <util/delay.h>
// #include <xc.h>
// 
// typedef enum {
// 	IDLE,
// 	PERPARE_COFFEE_POWDER,
// 	BOIL_WATER,
// 	POUR_COFFEE
// 	} state ;
// 	
// 	typedef enum {
// 		false = 0,
// 		true = 1
// 	} bool;
// 
// state current_state;
// 
// void wait( int ms )
// {
// 	for (int i=0; i<ms; i++)
// 	{
// 		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
// 	}
// }
// 
// void setPulveriserState(bool state){
// 	// set coffee powder mill on or off;
// }
// 
// bool checkCoffeePowderLevel(){
// 	// check sensor
// 	return true;
// }
// 
// void updateScreen(){
// 	// update its display;
// 	if(...){
// 		current_state = PERPARE_COFFEE_POWDER;
// 	}
// }
// 
// void setBoilerState(bool state){
// 	// set boiler on or off;
// }
// 
// bool checkWaterTemp(){
// 	// check sensor
// 	return true;
// }
// 
//  long milisPouring;
//  
// void setPourPumpState(bool state){
// 	// set pump on or off;
// }
// 
// int main(void)
// {
//     while(1)
//     {
//         switch(state){
// 			case IDLE:
// 				updateScreen();
// 			break;
// 			
// 			case PERPARE_COFFEE_POWDER:
// 				bool coffeeLevel = checkCoffeePowderLevel();
// 				setPulveriserState(!coffeeLevel);
// 			
// 				if(coffeeLevel){
// 					current_state = BOIL_WATER;
// 				}
// 			break;
// 			
// 			case BOIL_WATER:
// 				bool waterTemp = checkWaterTemp();
// 				setBoilerState(!waterTemp);
// 				if(waterTemp){
// 					current_state = POUR_COFFEE;
// 				}
// 			break;
// 			
// 			case POUR_COFFEE:
// 				bool shouldPour = !(milisPouring => 2000);
// 				setPourPumpState(shouldPour);
// 			
// 				milisPouring++;
// 			
// 				if(!shouldPour){
// 					milisPouring = 0;
// 				}
// 			break;
// 		}
// 		wait(1);
//     }
// }