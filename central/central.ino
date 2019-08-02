#include <VirtualWire.h>

//Define pino led
int pino_1 = 8;
int pino_2 = 9;
int pino_3 = 10;
int sensor = 0;

int valor_recebido_RF;
char recebido_RF_char[4]; 

void setup() 
{
  Serial.begin(9600);
  pinMode(sensor,INPUT);
  pinMode(pino_1, OUTPUT);
  pinMode(pino_2, OUTPUT);
  pinMode(pino_3, OUTPUT);
  //Pino ligado ao pino DATA do receptor RF
  vw_set_rx_pin(7);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(2000); 
  //Inicia a recepcao  
  vw_rx_start();
  Serial.println("Recepcao modulo RF - Aguardando...");
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    digitalWrite(pino_1, LOW);
    digitalWrite(pino_1, LOW);
    digitalWrite(pino_1, LOW);
    if (vw_get_message(buf, &buflen)) 
    {
    int i;
        for (i = 0; i < buflen; i++)
       {            
          //Armazena os caracteres recebidos  
          recebido_RF_char[i] = char(buf[i]);
       }
       recebido_RF_char[buflen] = '\0';
       
       //Converte o valor recebido para integer
       valor_recebido_RF = atoi(recebido_RF_char);
         
       //Mostra no serial monitor o valor recebido
       Serial.print("Recebido: ");
       Serial.print(valor_recebido_RF);
       
       //Altera o estado do led conforme o numero recebido
       if (valor_recebido_RF == 1)
       {
         digitalWrite(pino_1, HIGH);
         digitalWrite(pino_2, HIGH);
         digitalWrite(pino_3, HIGH);
         Serial.println(" - Ambulancia na pista !");
       }
    }
    
}


