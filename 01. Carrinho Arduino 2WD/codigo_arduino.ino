// Pinos do Motor A

int MOTOR_A_VELOCIDADE = 5;
int MOTOR_A1 = 6;
int MOTOR_A2 = 7;

// Pinos do Motor B

int MOTOR_B_VELOCIDADE = 10;
int MOTOR_B1 = 9;
int MOTOR_B2 = 8;

// Ponte H é azul?
bool PONTE_H_AZUL = true;

// Configuração dos Sentidos

bool FRENTE = false;
bool TRAS = true;
bool ESQUERDA = false;
bool DIREITA = true;

// Tempo entre comandos
int TEMPO = 500;

void setup() {
  // Configura pinos do Motor A
  pinMode(MOTOR_A1,OUTPUT);
  pinMode(MOTOR_A2,OUTPUT);
  pinMode(MOTOR_A_VELOCIDADE,OUTPUT);

  // Configura pinos do Motor B
  pinMode(MOTOR_B1,OUTPUT);
  pinMode(MOTOR_B2,OUTPUT);
  pinMode(MOTOR_B_VELOCIDADE,OUTPUT);
}

// Inserir as instruções para movimentar o carrinho
void loop() {
//movimento(sentido, velocidade 0-255, duração);
  andar(FRENTE, 255,1000);
  andar(TRAS, 255,1000);
  virar(DIREITA, 255, 1000);
  virar(ESQUERDA, 255, 1000);
}

void parar(int tempo) {
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);

  velocidadeWrite(0, 0);

  delay(tempo);
}

void andar(bool sentido, int velocidade, int tempo) {
  digitalWrite(MOTOR_A1, sentido);
  digitalWrite(MOTOR_A2, !sentido);
  
  digitalWrite(MOTOR_B1, sentido);
  digitalWrite(MOTOR_B2, !sentido);

  if(sentido) {
    velocidade = 255 - normalizaVelocidade(velocidade);
  }

  velocidadeWrite(velocidade, velocidade);

  delay(tempo);
  parar(TEMPO);
}

void virar(bool sentido, int velocidade, int tempo) {
  motorWrite(sentido, !sentido, !sentido, sentido);

  if(sentido) {
    velocidadeWrite(255-normalizaVelocidade(velocidade), velocidade);
  } else {
    velocidadeWrite(velocidade, 255-normalizaVelocidade(velocidade));
  }

  delay(tempo);
  parar(TEMPO);
}

void motorWrite(bool SENTIDO_A1, bool SENTIDO_A2, bool SENTIDO_B1, bool SENTIDO_B2) {
  digitalWrite(MOTOR_A1, SENTIDO_A1);
  digitalWrite(MOTOR_A2, SENTIDO_A2);
  
  digitalWrite(MOTOR_B1, SENTIDO_B1);
  digitalWrite(MOTOR_B2, SENTIDO_B2);
}

void velocidadeWrite(int velocidadeA, int velocidadeB) {
  analogWrite(MOTOR_A_VELOCIDADE, normalizaVelocidade(velocidadeA));
  analogWrite(MOTOR_B_VELOCIDADE, normalizaVelocidade(velocidadeB));
}

int normalizaVelocidade(int velocidade) {
  if(velocidade < 0) {
    velocidade = 0;
  } else if(velocidade > 255) {
    velocidade = 255;
  }

  return velocidade;
}
