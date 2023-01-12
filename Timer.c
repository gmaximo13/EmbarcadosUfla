/* ****************************************************************
** Atividade 05 **
** Gustavo dos Santos Moreira Máximo **
** Matricula: 201820512 **
** **
** Código para a implementação de um timer **
** Utilizando o microcontrolador PIC18F452 **
** E 4 displays de 7 segmentos **
** **
** Compilador : MikroC PRO PIC v .6.4.0 **
** **
** **
** UFLA - Lavras /MG - 12/01/2023 **
***************************************************************** */
 // Define o tempo para a multiplexação dos displays.
 # define tempo 5

 // Converte valor numerico decimal para codigo 7 segmentos
 unsigned short mask ( unsigned short num ){

   switch (num){
     case 0: return 0x3F;
     case 1: return 0x06;
     case 2: return 0x5B;
     case 3: return 0x4F;
     case 4: return 0x66;
     case 5: return 0x6D;
     case 6: return 0x7D;
     case 7: return 0x07;
     case 8: return 0x7F;
     case 9: return 0x6F;
   }
 }

//Função responsavel por acionar os displays
//mostrando os segungos ao usuario.

void exibicao(int segundos){

    PORTA = 0;
    PORTD = mask((segundos/1000)%10) ;
    porta.f2 = 1; // Ativa display 1.
    Delay_ms (tempo) ;
    porta.f2 = 0; // Desativa display 1.
    
    PORTD = mask((segundos/100)%10);
    porta.f3 = 1; // Ativa display 2.
    Delay_ms ( tempo );
    porta.f3 = 0; // Desativa display 2.
    

     PORTD = mask((segundos/10)%10);
     porta.f4 = 1; // Ativa display 3.
     Delay_ms ( tempo );
     porta.f4 = 0; // Desativa display 3.

     PORTD = mask(segundos%10);
     porta.f5 = 1; // Ativa display 4.
     Delay_ms ( tempo );
     porta.f5 = 0; // desativa display 4.

}

//Função responsavel por acionar o Buzzer
//O buzzer por 10 segundos ou até que o botão rb2 seja acionado

void acionaBuzzer(int segundos){
       int i = 0;
       while((portb.rb2 != 0) && (i<10)){
           exibicao(segundos);
           portc.rc1 = 1;
           delay_ms(500);
           exibicao(segundos);
           portc.rc1 = 0;
           delay_ms(500);
           i++;
       }
}
void main(){
  
  int segundos = 0;
  
  ADCON0 = 0X00 ;
  ADCON1 = 0X06 ; // desabilita conversor A/D.
  INTCON = 0; // desabilita interrupcoes.
  TRISA = 0; // configura portA como saida.
  PORTA = 0;
  TRISD = 0; // configura portD como saida.
  PORTD = 0;
  TRISB = 7; // Configura os pinos rb0, rb1 e rb2 como entrada.
  trisc = 0xFD; //Configura o pino rc1 como saída.
  
  portc.rc1 = 0; //Inicia o buzzer desligado
  
  while (1){ // inicio do loop infinito.
    
    exibicao(segundos);
    
    if(segundos >= 0 && segundos < 9999){ // Condição de limite do timer
      
      if(portb.rb0 == 0){ //Incrementa segundos quando o botão rb0 é acionado
          Delay_ms(80); //Delay para garantir o incremento de um segundo por vez
          segundos++;
          exibicao(segundos);
      }

      if(portb.rb1 == 0){   //Decrementa segundos quando o botão rb1 é acionado
         if(segundos != 0){ //Impede que a variavel segundo seja menor que zero
             Delay_ms(80);  //Delay para garantir o decremento de um segundo por vez
             segundos--;
         }
         exibicao(segundos);
      }

      if(portb.rb2 == 0){  //Aciona o timer quando o botão rb2 é pressionado
         while(segundos != 0){
             int i;
             segundos--;
             
             //Para cada chamada da função exibição são gastados 20ms por conta
             //da multiplexação, logo 50*20 = 1000ms (1 segundo).
             //Essa estrutura de repetição garante que todos os displays se manteram ativos
             //durante a contagem regressiva.
             
             for(i=0; i<=50; i++){
                 exibicao(segundos);
             }
         }
         acionaBuzzer(segundos);
      }
    }
  }
}