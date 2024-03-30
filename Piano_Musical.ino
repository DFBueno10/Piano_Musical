 /*
 * Piano Musical
 * Autor: Danilo Di Fabio Bueno
*/

#define VSOM 340 // Velocidade do som no ar (mm/ms)
#define TRIG 8  // Pino conectador ao Trig 
#define ECHO 7  // Pino conectado ao Echo

#define MINDIST 30  // Distancia minima da escala de operacao
#define MAXDIST 480 // Distancia maxima da escala de operacao

#define NOTAS 7 // Numero de notas musicais utilizadas

#define TA 50 // Taxa de atualizacao do programa
/* TA e importante para que o software execute em uma frequencia conehcida, 
   bem como limite a aquisicao de dados, ja que os proprios sensores nao fazem medicoes continuas,
   mas sim discretas com uma determinada frequencia de aquisicao
*/

int x0 = -1, x1;  // Variaveis para as distancias (anterior e atual)

int distancia (); // Prototipo da funcao

void setup() 
{
  pinMode(TRIG, OUTPUT);  // TRIG ( gatilho ) como saida
  pinMode(ECHO, INPUT);   // ECHO ( receptor ) como entrada 
  Serial.begin(9600);     // Inicia a comunicacao Serial a 9600 bauds
}


void loop() 
{ 
  int nota; // Variavel para a nota musical
  x1 = distancia(); // Armazena a distancia atual na variavel x1
  if ( x1 > MINDIST && x1 < MAXDIST) // Dentro da escala de operacao
    nota = map(x1, MINDIST, MAXDIST, 0, NOTAS); // Conversao da escala de distancia para a musical
  else // Fora da escala de operacao 
    nota = -1; // Nao existe nota atual
  Serial.print( char( nota+66 )); // Envia a nota como caractere
  /*
   * Obs: Se nota = -1, o caractere enviado corresponde ao 'A'
   * Esse caractere deve corresponder a ausencia sonora do PureData
   */
   
  //Serial.print(x1);           // Imprime a distancia
  //Serial.print(" mm \n");       // Imprime a unidade e quebra uma linha 
  delay(TA);                    // Aguarda TA para a proxima medicao
}

int distancia ()   // Funcao que calcula e retorna a distancia em milimetros (mm)
{
  digitalWrite(TRIG, LOW);        // Desliga o trig
  delayMicroseconds(2);           // Aguarda 2 us
  digitalWrite(TRIG, HIGH);       // Dispara um pulso ultrassonico
  delayMicroseconds(2);           // Aguarda 2 us
  digitalWrite(TRIG, LOW);        // Desliga o trig
  delayMicroseconds(1);           // Aguarda 1 us
  // ECHO ficara em nivel logico alto pelo mesma quantidade de tempo que o pulso demorou para voltar
  unsigned long tempo = pulseIn(ECHO, HIGH, 20000);  //  Calcula o tempo que o pulso demorou para voltar em us
  int distancia = VSOM*tempo/2000;  // Calcula a distancia em milimetros (mm) e armazena da variaval distancia
  return distancia;   // Retorna o valor da distancia 
}
