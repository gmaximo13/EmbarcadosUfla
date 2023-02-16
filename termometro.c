/****************************************************************************
Aluno: Gustavo Máximo
Matricula: 201820512
Termometro.c                              */

// Conexoes LCD do kit PICGenios com 18F452
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// Fim das conexoes

//**************** definicao de variaveis ********************************
char         texto[16];        //ponteiro texto
unsigned int valor_AD;         //define variavel
int        temperatura;      // temperatura em graus Celsius
//************************************************************************

//************** programa principal **************************************


void celsius (int temperatura){
     Lcd_Cmd(_LCD_CLEAR);
     IntToStr(temperatura, texto);
     Ltrim(texto);
     while(portb.RB2 == 1){
       Lcd_Out(1,1,"Temperatura[oC]:");
       Lcd_Out(2,1,texto);
       Lcd_Out(2,6, "RB2-VOLTAR");
     }
     Delay_ms(500); //Garante a leitura correta do botão
     Lcd_Cmd(_LCD_CLEAR);
}

void fahrenheit (int temperatura){
     Lcd_Cmd(_LCD_CLEAR);
     temperatura = ((temperatura*9)/5)+32;
     IntToStr(temperatura, texto);
     Ltrim(texto);
     while(portb.RB2 == 1){
       Lcd_Out(1,1,"Temperatura[oF]:");
       Lcd_Out(2,1,texto);
       Lcd_Out(2,6, "RB2-VOLTAR");
     }
     Delay_ms(500); //Garante a leitura correta do botão
     Lcd_Cmd(_LCD_CLEAR);
}

void kelvin (int temperatura){
     Lcd_Cmd(_LCD_CLEAR);
     Delay_ms(50);
     temperatura = temperatura + 273;
     IntToStr(temperatura, texto);
     Ltrim(texto);
     while(portb.RB2 == 1){
       Lcd_Out(1,1,"Temperatura[oK]:");
       Lcd_Out(2,1,texto);
       Lcd_Out(2,6, "RB2-VOLTAR");
     }
     Delay_ms(500); //Garante a leitura correta do botão
     Lcd_Cmd(_LCD_CLEAR);
}

void main() {

   // Desliga CAD
   ADCON0 = 0x00;
   //todos os pinos do porta (AN0-AN4) e porte (AN5-AN7) como i/o de uso geral
   ADCON1 = 0x06;

   trisd = 0x00;     //define portd como saida - LCD
   trise = 0x00;     //define porte como saida - LCD

   trisa = 0x04;     // define RA2/AN2 como entrada, outros pinos como saida
   trisb = 7;

   // Inicializa o LCD
   Lcd_Init();                      //Inicializa o Display
   Delay_ms(100);
   Lcd_Cmd(_LCD_CLEAR);             //limpa o Display
   Delay_ms(100);
   Lcd_Cmd(_LCD_CURSOR_OFF);        //Desabilita o cursor
   Delay_ms(100);

   /*reconfigura e define pinos de A/D - ADCON1
   B7 - 1: justificado a direita
        0: justificado a esquerda
   B6 - 0: fonte de clock oscilador RC interno do ADC
   B5 - NC
   B4 - NC
   B3:B0 = 0b0010 = canais AN0 a AN4, Vref+ = VDD, Vref- = GND  */
   ADCON1 = 0b10000010;

   /*reconfigura A/D - ADCON0
   B7:B6 - 0b11: fonte de clock oscilador RC interno do ADC
   B5:B3 - 0b010: canal 2 - AN2
   B2 - status do CAD
   B1 - NC
   B0 - 1: ADC ligado
        0: ADC desligado    */
   ADCON0 = 0b11010001;

   do
   {
      Lcd_Out(1,1,"RB0-C");
      Lcd_Out(2,1,"RB1-F");
      Lcd_Out(1,7,"RB2-K");

      valor_AD =  adc_read(2);      //le canal 2 e salva

      temperatura = (valor_AD*500)/1024;

      if (portb.rb0 == 0){
         Delay_ms(150); //Garante a leitura correta do botão
         celsius(temperatura);
      }
      if (portb.rb1 == 0){
         Delay_ms(150); //Garante a leitura correta do botão
         fahrenheit(temperatura);
      }
      if (portb.rb2 == 0){
         Delay_ms(150); //Garante a leitura correta do botão
         kelvin(temperatura);
      }
      //Fim do menu
      Delay_ms(100);      //delay de 100ms
   } while (1);
}