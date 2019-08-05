#use delay(clock=4MHz)

signed char teclado (void)
   {
   signed char tecla='x';
   while(tecla=='x')
      {
      RC3=0; RC0=1;
      if(RB1) {tecla = 7; delay_ms(200);}
      if(RB2) {tecla = 4; delay_ms(200);}
      if(RB3) {tecla = 1; delay_ms(200);}
      if(RB4) {tecla =19; delay_ms(200);} //caracter *

      RC1 = 1; RC0 = 0;
      if(RB1) {tecla = 8; delay_ms(200);}
      if(RB2) {tecla = 5; delay_ms(200);}
      if(RB3) {tecla = 2; delay_ms(200);}
      if(RB4) {tecla = 0; delay_ms(200);}

      RC2 = 1; RC1 = 0;
      if(RB1) {tecla = 9; delay_ms(200);}
      if(RB2) {tecla = 6; delay_ms(200);}
      if(RB3) {tecla = 3; delay_ms(200);}
      if(RB4) {tecla =13; delay_ms(200);} //caracter #
      
      RC3 = 1; RC2 = 0;
      if(RB1) {tecla = 205; delay_ms(200);}
      if(RB2) {tecla = -6; delay_ms(200);}
      if(RB3) {tecla = -3; delay_ms(200);}
      if(RB4) {tecla =-5; delay_ms(200);} //caracter #
      }
   return tecla;
   }

signed char teclado2 (void)
   {
   signed char tecla=0;
   
      
      RC3=0; RC0=1;
      if(RB1) {tecla = 7; delay_ms(200);}
      if(RB2) {tecla = 4; delay_ms(200);}
      if(RB3) {tecla = 1; delay_ms(200);}
      if(RB4) {tecla =19; delay_ms(200);} //caracter *

      RC1 = 1; RC0 = 0;
      if(RB1) {tecla = 8; delay_ms(200);}
      if(RB2) {tecla = 5; delay_ms(200);}
      if(RB3) {tecla = 2; delay_ms(200);}
      if(RB4) {tecla = 0; delay_ms(200);}

      RC2 = 1; RC1 = 0;
      if(RB1) {tecla = 9; delay_ms(200);}
      if(RB2) {tecla = 6; delay_ms(200);}
      if(RB3) {tecla = 3; delay_ms(200);}
      if(RB4) {tecla =13; delay_ms(200);} //caracter #
      
      RC3 = 1; RC2 = 0;
      if(RB1) {tecla = 205; delay_ms(200);}
      if(RB2) {tecla = -6; delay_ms(200);}
      if(RB3) {tecla = -3; delay_ms(200);}
      if(RB4) {tecla =-5; delay_ms(200);} //caracter #
      
   return tecla;
   }

