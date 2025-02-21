#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
// Pinos dos LEDs
#define red 0    
#define green 1
#define sensorpir 9
// Declarando elas como inteiras
int seg = 0;
int min = 58;
int hora = 8;
int dia = 30;
int mes = 12;
int ano = 2021;
int opcao = -1;
// Pinos do sensor de distância
int trig = 10;
int echo = 9;

// Pino do buzzer 
int buzzer = 8;

// Função para leitura e exibição da temperatura
void exibirTemperatura() {
  int PinoAnalog = analogRead(A0); // Leitura da temperatura
  int NewPinoAnalog = map(PinoAnalog, 20, 358, -40, 125); /* Organiza de maneira 
  ordenada os valores da temperatura*/
  lcd.clear();
  lcd.setCursor(0, 0); // Primeira linha
  lcd.print("Temperatura de:");
  lcd.setCursor(0, 1); // Segunda linha
  lcd.print(NewPinoAnalog);
  lcd.print(" C"); // Exibe o valor da temperatura
  delay(7000);// Permanece por 7 segundos
  lcd.clear();
}

// Função para leitura e exibição do gás
void exibirGas() {
  int MQ2pin = A1; // Pino do sensor de gás
  pinMode(buzzer, OUTPUT);// Define o buzzer como saída
  float sensorValue = analogRead(MQ2pin); // Leitura do sensor de gás

  if (sensorValue >= 450) { // Gás detectado
    digitalWrite(buzzer, HIGH); // Ativa o buzzer
    digitalWrite(red, HIGH);// Ativa a LED vermelha
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Perigo de gas:");
    lcd.setCursor(0, 1);
    lcd.print(sensorValue);
    delay(7000);// Permanece por 7 segundos
    digitalWrite(buzzer, LOW);// Desativa o buzzer
    digitalWrite(red, LOW);// Desativa a LED
    
  } else { // Nenhum gás detectado
    digitalWrite(buzzer, LOW); // Desativa o buzzer
    digitalWrite(red,LOW);   // Desliga o LED vermelho
    digitalWrite(green, HIGH);// Liga o LED verde
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sem perigo:");
    lcd.setCursor(0, 1);
    lcd.print(sensorValue);
    delay(7000);// Permanece por 7 segundos
    digitalWrite(green,LOW);//Desliga o LED verde
  }
  lcd.clear();
}

// Função para leitura e exibição da umidade
void exibirUmidade() {
  int sensor = A2; // Pino do sensor de umidade
  float sensorValueUmidade = analogRead(sensor); // Leitura do sensor de umidade
  lcd.clear();
// Caso o valor da umidade seja inferior a 200, classifica-se como nível seco
  if (sensorValueUmidade < 200) {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("SECO");
// Caso o valor da umidade seja inferior ou igual a 400 classifica-se como muito baixo    
  } else if (sensorValueUmidade <= 400) {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("MUITO BAIXO");
// Caso o valor da umidade seja inferior ou igual a 600 classifica-se como baixo  
  } else if (sensorValueUmidade <= 600) {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("BAIXO");
// Caso o valor da umidade seja inferior ou igual a 800 classifica-se como pouco baixo  
  } else if (sensorValueUmidade <= 800) {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("POUCO BAIXO");
// Caso o valor da umidade seja inferior ou igual a 1000 classifica-se como medio 
  } else if (sensorValueUmidade <= 1000) {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("MEDIO");
// Caso o valor da umidade seja inferior ou igual a 2000 classifica-se como pouco alto  
  } else if (sensorValueUmidade <= 2000) {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("POUCO ALTO");
// Caso o valor da umidade seja inferior ou igual a 3000 classifica-se como alto   
  } else if (sensorValueUmidade <= 3000) {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("ALTO");
// Caso o valor da umidade não se qualifique com nenhum dos outros classifica-se como total 
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de Umidade");
    lcd.setCursor(0, 1);
    lcd.print("TOTAL");
  }
  delay(7000);// Permanece por 7 segundos
  lcd.clear();
}

// Função para leitura e exibição da presença
void exibirPresenca() {
  pinMode(sensorpir,INPUT);// Classifica o sensor PIR como entrada
  digitalWrite(red,LOW);// Desliga a LED vermelha
  Serial.println(sensorpir); 
  if(digitalRead(sensorpir) == HIGH)/* Caso seja identificado movimento
na área do sensor de presença*/
  {
    lcd.setCursor(0, 0);
    lcd.print("Detectado");
    lcd.setCursor(0, 1);
    lcd.print("Movimento");
    digitalWrite(red,HIGH);// Liga LED vermelha
    delay(7000);// Permanece por 7 segundos
    digitalWrite(red,LOW);// Desliga a LED vermelha 
  }
//  Caso não seja identificada nenhuma movimentação 
  else{
    lcd.setCursor(0, 0);
    lcd.print("Sem");
    lcd.setCursor(0, 1);
    lcd.print("Movimento");
    digitalWrite(green,HIGH);// Liga a LED verde
    delay(7000);// Permanece por 7 segundos
    digitalWrite(green,LOW);// Desliga a LED verde
  }
   lcd.clear();
}

// Botão da direita escolhe o que mudar
void escolheOpcao() {
  if (opcao == 5) {
    opcao = -1;
  } else {
    opcao++;
  }
}

// Botão da esquerda muda o que estiver selecionado
void muda() {
// Seleciona a opção do segundo, depois minutos, hora, ano, mês e dia respectivamentte
  if (opcao == 0) {
    seg++;
    if (seg > 59) {
      seg = 0;
    }
  } else if (opcao == 1) {
    min++;
    if (min > 59) {
      min = 0;
    }
  } else if (opcao == 2) {
    hora++;
    if (hora > 23) {
      hora = 0;
    }
  } else if (opcao == 3) {
    ano++;
    if (ano > 2050) {
      ano = 2000;
    }
  } else if (opcao == 4) {
    mes++;
    if (mes > 12) {
      mes = 1;
    }
  } else if (opcao == 5) {
    dia++;
    if (dia > 31) {
      dia = 1;
    }
  }
}

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0, muda, RISING);
  attachInterrupt(1, escolheOpcao, RISING);
  lcd.begin(16, 2);
  pinMode(0, OUTPUT); // Configura o pino 0 como saída
  pinMode(1, OUTPUT); // Configura o pino 1 como saída
  digitalWrite(0, LOW); // Inicializa como desligado
  digitalWrite(1, LOW); // Inicializa como desligado  
      ;
}

void loop() {
  // Exibir data e hora por 60 segundos
  for (int i = 0; i < 60; i++) {
    lcd.setCursor(6, 0); lcd.print(":");
    lcd.setCursor(9, 0); lcd.print(":");

    if (hora <= 9) {
      lcd.setCursor(4, 0); lcd.print("0");
      lcd.setCursor(5, 0); lcd.print(hora);
    } else {
      lcd.setCursor(4, 0); lcd.print(hora);
    }

    if (min <= 9) {
      lcd.setCursor(7, 0); lcd.print("0");
      lcd.setCursor(8, 0); lcd.print(min);
    } else {
      lcd.setCursor(7, 0); lcd.print(min);
    }

    if (seg <= 9) {
      lcd.setCursor(10, 0); lcd.print("0");
      lcd.setCursor(11, 0); lcd.print(seg);
    } else {
      lcd.setCursor(10, 0); lcd.print(seg);
    }

    lcd.setCursor(5, 1); lcd.print("/");
    lcd.setCursor(8, 1); lcd.print("/");

    if (dia <= 9) {
      lcd.setCursor(3, 1); lcd.print("0");
      lcd.setCursor(4, 1); lcd.print(dia);
    } else {
      lcd.setCursor(3, 1); lcd.print(dia);
    }

    if (mes <= 9) {
      lcd.setCursor(6, 1); lcd.print("0");
      lcd.setCursor(7, 1); lcd.print(mes);
    } else {
      lcd.setCursor(6, 1); lcd.print(mes);
    }

    lcd.setCursor(9, 1); lcd.print(ano);

    delay(1000);
    seg++;
    if (seg == 60) {
      seg = 0;
      min++;
      if (min == 60) {
        min = 0;
        hora++;
        if (hora == 24) {
          hora = 0;
          dia++;
          if (dia == 32) {
            dia = 1;
            mes++;
            if (mes == 13) {
              mes = 1;
              ano++;
            }
          }
        }
      }
    }
  }

  /* Chamar funções específicas, 
  com cada uma tendo duração de 7 segundos, 
  após os 60 segundos para configurar o relógio e a data*/
  exibirTemperatura();
  exibirGas();
  exibirUmidade();
  exibirPresenca();
}
