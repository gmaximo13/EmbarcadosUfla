/* ****************************************************************
2** Exemplo 05 **
3** **
**Exemplo para utilizacao do display de 7 segmentos **
** presente no kit PIC 18 F452 . Cada um dos 4 displays **
** sao acessos , um de cada , vez , exibindo seu indice **
** Ex: display 1 = 1 , display 2 = 2 , etc ... **
** **
** Arquivo : display7seg .c **
** Compilador : MikroC PRO PIC v .6.4.0 **
** **
** Obs: Ativar dips switchs : DISP1 a DISP4 **
** **
** UFLA - Lavras /MG - 12/07/2017 **
***************************************************************** */

 // Define o tempo de acendimento do display em ms.
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

void exibicao(int segundos){

    PORTA = 0;

  //  if(segundos > 999){
      PORTD = mask((segundos/1000)%10) ;
      porta.f2 = 1; // Ativa display 1.
      Delay_ms (tempo) ;
      porta.f2 = 0; // Desativa display 1.
    //}
    
    //if(segundos > 99){
      PORTD = mask((segundos/100)%10);
      porta.f3 = 1; // Ativa display 2.
      Delay_ms ( tempo );
      porta.f3 = 0; // Desativa display 2.
    //}
    
    //if(segundos > 9){
      PORTD = mask((segundos/10)%10);
      porta.f4 = 1; // Ativa display 3.
      Delay_ms ( tempo );
      porta.f4 = 0; // Desativa display 3.
    //}

    PORTD = mask(segundos%10);
    porta.f5 = 1; // Ativa display 4.
    Delay_ms ( tempo );
    porta.f5 = 0; // desativa display 4.

}

void main(){
  
  int segundos = 0;
  
  ADCON0 = 0X00 ;
  ADCON1 = 0X06 ; // desabilita conversor A/D.
  INTCON = 0; // desabilita interrupcoes .
  TRISA = 0; // configura portA como saida .
  PORTA = 0;
  TRISD = 0; // configura portD como saida .
  PORTD = 0;
  TRISB = 7; // Configura os pinos rb0, rb1 e rb2 como entrada
  
  while (1){ // inicio do loop infinito .
    
    exibicao(segundos);
    
    if(segundos >= 0 && segundos < 9999){
      if(portb.rb0 == 0){
          segundos++;
          exibicao(segundos);
          delay_ms(50);
      }

      if(portb.rb1 == 0){
         segundos--;
         exibicao(segundos);
      }

      if(portb.rb2 == 0){
         while(segundos != 0){
             segundos--;
             exibicao(segundos);
             Delay_ms(1000);
         }
      }
    }
  
  }
}