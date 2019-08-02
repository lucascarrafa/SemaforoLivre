#include <VirtualWire.h>

//Define pinos Led e Botao
const int pino_botao = 10;

int valor_botao = 0 ;
char Valor_CharMsg[4]; 
//Armazena estado led = ligar/desligar
int estado = 1;

void setup() 
{
  Serial.begin(9600);   
  pinMode(pino_botao,INPUT);
  //Pino ligado ao pino DATA do transmissor RF
  vw_set_tx_pin(4);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(2000);
  Serial.println("Trasmissao modulo RF - Acione o botao...");
}

void loop() 
{
  //Verifica o estado do push-button
  valor_botao = digitalRead(pino_botao);
  //itoa(valor_botao,Valor_CharMsg,10);
  Serial.println(valor_botao);
  //Caso o botao seja pressionado, envia dados
  if (valor_botao == HIGH)
  {
    //Altera o estado do led
    //estado = !estado;
    //Converte valor para envio
    itoa(estado,Valor_CharMsg,10);
    //Liga o led da porta 13 para indicar envio dos dados
    digitalWrite(13, true);
    //Envio dos dados
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    //Aguarda envio dos dados
    vw_wait_tx();
    //Desliga o led da porta 13 ao final da transmissao
    Serial.print("Valor enviado: ");
    Serial.println(Valor_CharMsg);
    delay(500);
  }
}
