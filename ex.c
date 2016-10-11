//Codigo-fonte exemplo: manipulação de I/Os
//Descrição: leitura de dois botões e controle de dois LEDs (on/off)
//Autor: Pedro Bertoleti
//Data: Outubro/2016
//
//Observacoes:
//1) Antes de compilar, instale a biblioteca wiringPi (https://learn.sparkfun.com/tutorials/raspberry-gpio#c-wiringpi-setup)
//2) Compile o programa com o seguinte comando: gcc -o ex ex.c -l wiringPi
//3) Após compilar, rode o programa com o seguinte comando: ./ex


#include <stdio.h>    
#include <wiringPi.h> //header para utilizar funções da wiringPi

//defines
//numeros dos pinos, não dos GPIOs!
#define PINO_INPUT_B1   16   
#define PINO_INPUT_B2   17
#define PINO_OUTPUT_L1  23
#define PINO_OUTPUT_L2  18

//variaveis globais
int DutyCiclePWM;

//prototypes
void ConfiguraIOs(void);

/**************
Implementacoes
***************/

//Funcao: configura os GPIO (I/Os)
//Parâmetros: nenhum
//Retorno: nenhum
void ConfiguraIOs(void)
{
    //configura os I/O (GPIO) 
    pinMode(PINO_OUTPUT_L2, OUTPUT);     
    pinMode(PINO_OUTPUT_L1, OUTPUT);     
    pinMode(PINO_INPUT_B1, INPUT);   
    pinMode(PINO_INPUT_B2, INPUT);  

    //habilita pull-up nos inputs (portanto, se apertado o botao, a Raspberry Pi lerá 0 como entrada)
    pullUpDnControl(PINO_INPUT_B1, PUD_UP); 
    pullUpDnControl(PINO_INPUT_B2, PUD_UP);
}

//Programa principal
int main( int argc, char *argv[] )
{
    //Inicializacoes
    wiringPiSetupGpio();
    DutyCiclePWM = 0;   
    ConfiguraIOs();
     
    //loop principal   
    while(1)
    {
        //tratamento do botao 1:
        if (digitalRead(PINO_INPUT_B1) == 0) 
        {
            //botao 1 pressionado. Acende LED1
            digitalWrite(PINO_OUTPUT_L1, HIGH);   
        }
        else
        {
            //botao 1 nao esta pressionado. Apaga LED1
            digitalWrite(PINO_OUTPUT_L1, LOW);
        }

        //tratamento do botao 2:
        if (digitalRead(PINO_INPUT_B2) == 0) 
        {
            //botao 2 pressionado. Pisca LED2
            digitalWrite(PINO_OUTPUT_L2, HIGH);
            delay(150); //tempo em ms
            digitalWrite(PINO_OUTPUT_L2, LOW);
            delay(150);  //tempo em ms
        }
        else
        {
            //botao 2 não está pressionado. Apaga LED2            
            digitalWrite(PINO_OUTPUT_L2, LOW); 
        }
    }

    return 0;
}