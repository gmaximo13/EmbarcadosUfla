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

void main(){
  ADCON0 = 0X00 ;
  ADCON1 = 0X06 ; // desabilita conversor A/D.
  INTCON = 0; // desabilita interrupcoes .
  TRISA = 0; // configura portA como saida .
  PORTA = 0;
  TRISD = 0; // configura portD como saida .
  PORTD = 0;
  while (1){ // inicio do loop infinito .
    // Escreve valor 1 no display 1 em codigo 7 segmentos .
    PORTD = mask(1) ;
    porta.f2 = 1; // Ativa display 1.
    Delay_ms (tempo) ;
    porta.f2 = 0; // Desativa display 1.

    // Escreve valor 2 no display 2 em codigo 7 segmentos .
    PORTD = mask(2);
    porta.f3 = 1; // Ativa display 2.
    Delay_ms ( tempo );
    porta . f3 = 0; // Desativa display 2.

    // Escreve valor 3 no display 3 em codigo 7 segmentos
    PORTD = mask(3);
    porta.f4 = 1; // Ativa display 3.
    Delay_ms ( tempo );
    porta.f4 = 0; // Desativa display 3.

    // Escreve valor 4 no display 4 em codigo 7 segmentos .
    PORTD = mask (4);
    porta.f5 = 1; // Ativa display 4.
    Delay_ms ( tempo );
    porta.f5 = 0; // desativa display 4.
    } // Fim do loop infinito
}