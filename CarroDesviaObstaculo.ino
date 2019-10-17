#include <AFMotor.h> //Declaração da inclusão da biblioteca do motor
#include <Servo.h> //Declaração da inclusão da biblioteca do servo

AF_DCMotor motor1 (3); //Declaração do pino que está ligado o motor 1
AF_DCMotor motor2 (4); //Declaração do pino que está ligado o motor 2

const int trig = A0; //Pino TRIG declarado em A0
const int echo = A1; //Pino ECHO declarado em A1
const int buzzer = A2; //Pino Buzzer declarado em A2
float tempo; //Declaração da variável tempo, relacionada ao tempo de ida e volta do sinal
int distancia; //Declaração da distância do obstáculo
int Velocidade = 255; //Declarado velocidade máxima dos motores
Servo ServoMotor; //Servo nomeado como ServoMotor

void setup() {
 pinMode(trig, OUTPUT); //Trig declarado como saída
 pinMode(echo, INPUT); //Echo declarado como entrada
 pinMode(buzzer, OUTPUT); //Buzzer declarado como saída
 digitalWrite(trig, LOW); //Trig sendo inicializado em LOW
 delayMicroseconds(10); //Delay de 10 microsegundos
 
 ServoMotor.attach(10); //Servo declarado no pino 10
 ServoMotor.write(115); //Servo posicionado na posição de 115º
 delay(1000); //Delay de 1 segundo para o servo se posicionar
 
 Serial.begin(9600); //Serial inicializado
}
  
void loop() {
int DistanciaDireita = 0; //Declaração da DistanciaDireita 
int DistanciaEsquerda = 0; //Declaração da DistanciaDireita 

distancia = LerDistancia(); //distancia vai receber o valor da função LerDistancia()
if (distancia <= 20){ //Se a distância for menor ou igual a 20cm
  PararMotor(); //Chama a função PararMotor
  
  DistanciaEsquerda = LadoEsquerdo(); //DistanciaEsquerda recebe o valor da distancia da função LadoEsquerdo()
  DistanciaDireita = LadoDireito(); //DistanciaDireita recebe o valor da distancia da função LadoDireito()
      if(DistanciaDireita >= DistanciaEsquerda){ //Se a DistanciaDireita for maior ou igual a DistanciaEsquerda
        VireDireita(); //Chama a função VireDireita()
        PararMotor(); //Chama a função PararMotor()
      }
      else{ //Senão
        VireEsquerda(); //Chama a função VireEsquerda
        PararMotor(); //Chama a função PararMotor
          }
} 
else{ //Senão
  MoverFrente(); //Chama a função MoverFrente
    }
}

int LerDistancia(){ //Inicialização da função LerDistancia
 digitalWrite(trig, HIGH); //Declara Trig como HIGH
 delayMicroseconds(10); //Delay de 10 Microsegundos em nível alto
 digitalWrite(trig, LOW); //Declara trig em LOW
 tempo = pulseIn(echo, HIGH); //A variável Tempo recebe o valor do tempo que demorou para o sinal ir e voltar
 distancia = tempo / 29.4 / 2; //É necessário 29.4ms para o som percorrer 1s
 //Tempo é dividido por 2 pois o som vai e volta
 
 delayMicroseconds(200); //Delay para realizar novamente o mesmo processo
 Serial.println(distancia); //Impressão da distância no monitor serial em centímetros
 delay(50); //Delay para impressão da distância
 return distancia; //retorna o valor da distância
}

int LadoEsquerdo(){ //Função para o Servo virar para o lado esquerdo
  ServoMotor.write(170); //Move o servo motor para o ângulo de 170º
  delay(500); //Delay de 0.5s para realizar a movimentação
  int distancia = LerDistancia(); //Faz a leitura da distância do lado esquerdo
  delay(100); //Delay de 0.1s para realizar a leitura da distância
  ServoMotor.write(115); //Retorna o servo motor para a posição inicial de 115º
  return distancia; //Retorna o valor da distância do lado esquerdo
}
  
int LadoDireito(){ //Função para o Servo virar para o lado direito
  ServoMotor.write(80); //Move o servo motor para o ângulo de 80º
  delay(500); //Delay de 0.5s para realizar a movimentação
  int distancia = LerDistancia(); //Faz a leitura da distância do lado direito
  delay(100); //Delay de 0.1s para realizar a leitura da distância
  ServoMotor.write(115); //Retorna o servo motor para a posição inicial de 115º
  return distancia; //Retorna o valor da distância do lado direito
}

void MoverFrente(){ //Função para mover para frente o carro
  motor1.run(FORWARD); //Faz como que o motor 1 se movimente para frente
  motor1.setSpeed(Velocidade); //Declara velocidade máxima para o motor 1
  motor2.run(FORWARD); //Faz como que o motor 2 se movimente para frente
  motor2.setSpeed(Velocidade); //Declara velocidade máxima para o motor 2
}

void PararMotor(){ //Função para parar o motor caso apareça algum obstáculo
  motor1.run(RELEASE); //Desliga o motor 1
  motor2.run(RELEASE); //Desliga o motor 2
  delay(1000); //Motores permanecem 1 segundo desligados
}

void VireDireita(){ //Função para fazer o carro virar para a direita
  motor1.run(BACKWARD); //Faz com que o motor 1 se movimente para trás
  motor1.setSpeed(Velocidade); //Define o motor 1 com velocidade máxima
  motor2.run(FORWARD); //Faz com que o motor 2 se movimente para frente
  motor2.setSpeed(Velocidade); //Define o motor 2 com velocidade máxima
  tone(buzzer, 262, 200); //Buzzer apita nesta frequência quando ocorrer a movimentação para a direita
  delay(250); //Delay de 0.25s para que seja realizada a movimentação para o lado direito
}

void VireEsquerda(){ //Função para fazer o carro virar para a esquerda
  motor1.run(FORWARD); //Faz com que o motor 1 se movimente para frente
  motor1.setSpeed(Velocidade); //Define o motor 1 com velocidade máxima
  motor2.run(BACKWARD); //Faz com que o motor 2 se movimente para trás
  motor2.setSpeed(Velocidade); //Define o motor 2 com velocidade máxima
  tone(buzzer, 294, 300); //Buzzer apita nesta frequência quando ocorrer a movimentação para a esquerda
  delay(250); //Delay de 0.25s para que seja realizada a movimentação para o lado esquerdo
}
