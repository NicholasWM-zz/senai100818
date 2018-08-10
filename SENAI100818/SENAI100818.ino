#include <SoftwareSerial.h>

SoftwareSerial blue(2,3);
String dadoCompleto, led, valorRecebido;
byte valor;

//Portas das Cargas
#define R 5
#define G 6
#define B 9

void setup()
{
  // put your setup code here, to run once:
  declaraComunicacao();
  declaraPortas();
  digitalWrite(R,1);
}

void loop()
{
  // put your main code here, to run repeatedly:
  sinalBlue();
}
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
void declaraPortas()
{
  pinMode(R, 1);
  pinMode(G, 1);
  pinMode(B, 1);
}

void declaraComunicacao()
{

  Serial.begin(9600);
  blue.begin(38400);
  Serial.println("INICIANDO");
}

//Interage com o Sinal Bluetooth
void sinalBlue()
{ //Se o bluetooth enviar algo...
  static char character;
  dadoCompleto = " ";

  while (blue.available() > 0)
  { //Armazena os dados recebidos em umas String
    dadoCompleto += char(blue.read());
    // Serial.println(dadoCompleto);
    delay(1);
  } //Extrai certas informações da String completo, o Led e o valor que é convertido para Int
  led = dadoCompleto.substring(1, (dadoCompleto.lastIndexOf(" ")));
  valor = (dadoCompleto.substring(dadoCompleto.lastIndexOf(" ") + 1)).toInt();
  // Serial.println(led);

  if(dadoCompleto != " "){
    Serial.println(dadoCompleto);
    Serial.println(led);
    Serial.println(valor);
  }
  //Pega apenas a primeira posição do array de chars
  character = led[0];

  // Serial.println(character);
  char character2 = ' ';
  for (int i = 0; i < sizeof(dadoCompleto); i++)
  {
    if (isAlphaNumeric(dadoCompleto[i]))
    {
      character2 = dadoCompleto[i];
    }
  }
  //Verifica qual Slider mandou o sinal
  switch (character)
  { //Dependendo da resposta, aplica o valor no led identificado
    Serial.println(dadoCompleto);
    // --- Controle Manual Neon ---
    case 'R':
      analogWrite(R, valor);
      break;
    case 'G':
      analogWrite(G, valor);
      break;
    case 'B':
      analogWrite(B, valor);
      break;
  }
}
