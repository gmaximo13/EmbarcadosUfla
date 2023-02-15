/*
 Gustavo dos Santos Moreira Máximo 201820512
 Contador de giro -Exercício 6
*/
// Conexoes LCD do kit PICGenios com 18F
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


//Função para resetar a contagem

void resetaContagem(int contadorPulsos, int contadorVoltas, char contatorVoltasStr[12]){
   contadorPulsos = 0;
   contadorVoltas = 0;
   LongToStr(contadorVoltas, contatorVoltasStr);
   Lcd_Out(1,4,contatorVoltasStr);
 }

 void main() {
    long contadorPulsos = 0;
    long contadorVoltas = 0;
    char contatorVoltasStr[12];

    ADCON0 = 0x00; // Configura todos pinos para digital e
    ADCON1 = 0x06; // desabilita o conversor A/D

    trisb = 1; // Configura o push botton rbO como entrada

    trisc = 1; // Entrada: RC0 ; os outros pinos sao saida
    portc.rc2 = 1; // liga a ventoinha


     // Inicia e configura o LCD
    Lcd_Init();
    Delay_ms(100);
    Lcd_Cmd(_LCD_CLEAR);
    Delay_ms(100);
    Lcd_cmd(_LCD_CURSOR_OFF);
    Delay_ms(100);

    while(1) {

            //Se o botão rbo for acionado reseta a contagem
            if(portb.rb0 == 0){
            resetaContagem(contadorPulsos, contadorVoltas, contatorVoltasStr);
            }

            // Monitora os pulsos do sensor
            while (portc.rc0 == 0);
            delay_ms(1);
            while (portc.rc0 == 1);
            delay_ms(1);
            contadorPulsos++;

            // Incrementa a quantidade de voltas
            if(contadorPulsos == 7){
            contadorPulsos = 0;
            contadorVoltas++;
            LongToStr(contadorVoltas, contatorVoltasStr);
            Lcd_Out(1,4,contatorVoltasStr);
            }

        }
}
