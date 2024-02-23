## Medición y Síntesis de Frecuencias de hasta 200Hz

El proyecto consiste en poder analizar la frecuencia de diferentes formas de onda (sinusoidal, triangular,
cuadrada) y en base al cálculo de la frecuencia medida poder luego generar una señal sinusoidal de la misma
frecuencia. El proyecto se dividió en dos partes, la medición de la frecuencia de entrada y la síntesis de la
sinusoide.
Se realizó el programa en C utilizando un microcontrolador ATmega328p y se utilizaron los siguientes periféricos: módulos Timer0 y Timer2 (para generar un PWM), el módulo
UART para poder pasar los datos por el puerto serie, el módulo del conversor ADC para analizar los datos
de la señal de entrada, e interrupciones.
Dentro de la carpeta 'Documentación' se encuentra la explicación detallada del proyecto.

### Resultados
En las siguientes figuras se muestran en azul las señales de entrada y en rosado las sinusoides sintetizadas a la salida. Las figuras fueron tomadas usando el simulador Proteus.

![sintesis_cuadrada](https://github.com/EzeMat21/Proyecto-Arquitectura/assets/126365409/bc610949-f697-459f-9d51-8f5f4d8b6866)
![sintesis_2](https://github.com/EzeMat21/Proyecto-Arquitectura/assets/126365409/383200ad-669b-44df-ad22-155ac123b53f)
