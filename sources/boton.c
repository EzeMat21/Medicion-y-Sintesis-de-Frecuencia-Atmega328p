/*
 * boton.c
 *
 * Created: 22/12/2022 01:24:19
 *  Author: ezema
 */ 


#include "../headers/boton.h"

//Interrupción externa por flanco pin INT0

void INT0_init(){
	
	 EICRA |= (1<<ISC01);		//The falling edge of INT0 generates an interrupt request.
	 EIMSK |= (1<<INT0);		//Habilitar la interrupción 
	
}