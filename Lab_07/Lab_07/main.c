//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2012-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.2.0.295 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

// Gabriel Carrera 21216 - Lab 7

// --------------- Librerias ---------------
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/adc.h"

// --------------- Frecuencia ---------------
#define XTAL 16000000       // Establecer reloj a 16MHz

// --------------- Variables ---------------
int bandera = 0; //bandera para iniciar el semáforo
uint32_t i; //variable para delay
int valor; //Valor para leer estado del push button

// --------------- Prototipos ---------------
void setup(void); //Función del setup
void delay1ms(void); //Función para delay de 1ms
void delay(uint32_t msec); //Función para delay en ms

// --------------- Loop principal ---------------
int main(void){
    setup(); //Llamar al setup

//Loop
    while(1){
            valor = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4); //Leer estado del Push button
            if (valor == 0){ //Si está presionado limpiar la bandera del semáforo
                if (bandera == 1){
                    bandera = 0; //Limpiar bandera
                }
            }
            if (valor == 0 && bandera == 0){ //Si se presionó el botón y la bandera es 0
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); //Encender led verde
                delay(3000); //delay de 3s
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); //Apagar led verde
                delay(200); //delay de 200ms
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); //Encender led verde
                delay(200); //delay de 200ms
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); //Apagar led verde
                delay(200); //delay de 200ms
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); //Encender led verde
                delay(200); //delay de 200ms
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); //Apagar led verde
                delay(200); //delay de 200ms
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); //Encender led verde
                delay(200); //delay de 200ms
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); //Apagar led verde
                delay(1000); //delay de 1s

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_1, GPIO_PIN_3 | GPIO_PIN_1); //Encender led amariila
                delay(3000); //delay de 3s
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_1, 0); //Apagar led amarilla
                delay(1000); // delay de 1s

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1); //Encender led rojo
                delay(3000); //delay de 3s
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); //Apagar led rojo
                bandera = 1; //Encender bandera de terminación
            }
     }
}

void setup(void){
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //Configuración del reloj a 40MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //Habilitar el puerto F
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); //Esperar a que se inicialice
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4); //Configurar push1 como entrada
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //Configurar pines 1, 2 y 3 del Puerto F (LEDS)
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); //Pull-up al push1
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0); //Iniciar con leds apagados
}

void delay(uint32_t msec){
    for (i = 0; i < msec; i++){ //Ejecutar número de veces del argumento
        delay1ms(); //Llamar a función de 1ms
    }
}

void delay1ms(void){
    SysTickDisable(); //Deshabilitar el Sistick
    SysTickPeriodSet(40000-1); //Por aproximadamente 1ms
    SysTickEnable(); //Iniciar el set del periodo

    while((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0); //Mientras el bit de count sea 0 no hacer nada
}
