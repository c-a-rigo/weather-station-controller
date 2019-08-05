#include <16f887.h>
#include <regs_887.h>
#use delay(clock=4MHz)
#include <display.h>
#include <teclado.h>
#fuses INTRC_IO

void inicializa_ad(void);
void inicializa_timer1(void);
void menu (void);
void mostra_umidd (void);
void mostra_temp (void);
void mostra_press (void);
void mostra_vent (void);
void interrupcao_externa (void);
void interrupcao_timer1 (void);
void apaga_memoria (void);
void config_hora(void);
void interrrupcao_RB (void);
void teclado_INT (void);
void config_tcoleta(void);
void coleta_dados(void);
void  mostra_dadoscoletados (void);
void mostra_hora(void);
void mostra_dados(void);

int16 t0, t1, t2, t3, t4, t_coleta=10, j=0, tecla=0, t_total=0, t_anterior=0;
int8  r=0, r1=0, r2=0, r3=0, r4=0, l1=0, l2=0, l3=0, l4=0, endereco=0x00;
int o=0;
char texto[21], digitado[5], senha[5]={0x31, 0x31, 0x31, 0x31, 0x31};

void main(void)
{
TRISA=0x0F; TRISB=0XFF; TRISD=0; TRISE=0;  TRISC=0b11110000;  PORTC=0;

inicializa_display();
inicializa_ad();

INTEDG=1; INTE=1; GIE=1;  //Habilitação da interrupção externa
TMR1IE=1; PEIE=1; //Habilitação interrupção do timer1, para relógio.
RBIE=1; // Habilita interrupção na porta B.
WPUB=0xFF;
IOCB=0xFE;

inicializa_timer1();

coleta_dados();

while (true)
{
menu();

t_anterior=t_total;

teclado_INT();

switch (tecla){
 case 1: // Usuário quer ver dados em tempo real.
    limpa();
    mostra_dados();
  break;
  
  case 2: // Usuário quer ver dados adquiridos na ultima coleta.
    limpa();
    mostra_dadoscoletados();
  break;
    
  case 3: // Usuário quer configurar a hora.
     config_hora();  
  break;
  
  case 4: // Usuário quer configurar tempo de coleta.
     config_tcoleta(); 
  break;}
}
}

void menu (void)
{
strcpy(texto,"1-Dados agora ");
escreve (0x80,texto);
strcpy(texto,"2-Dado ultima coleta");
escreve (0xC0,texto);
strcpy(texto,"3-Conf. da hora   ");
escreve (0x94,texto);
strcpy(texto,"4-Conf. t. de coleta");
escreve (0xD4,texto);
}

void mostra_dados(void)
{
int16 palavra=0, valor=0; float vad=0;
o=0;
while (o==0)
{
PEIE=0;
CHS3=0;CHS2=0;CHS1=0;CHS0=0; // Seleciona canal 0 (RA0) para conversão.


//********DADOS********
for (j=0; j<4; j++)
{

 //adquire dados
  GO_DONE=1; // Inicia conversão.
  while (GO_DONE); // Aguarda conversão terminar.
  palavra=ADRESH*256+ADRESL;
  ADCON0=ADCON0+4; //seleciona próximo canal para conversão.
  o=teclado2();

if (j==0) // TEMPERATURA
 {
    vad=((10.0*palavra)/1023)*1000; // Obtem valor correspondente a leitura em escala de 0 à 100.
    t4=0x20; // Define temperatura sem sinal.
    if (vad>5000)
    {
    vad=(vad-4995); // Retifica a leitura de escala 50 -- 100 para escala 0 -- 50.
    t4=0x2B; // Inclui o sinal "+" na temperatura.
    }
    else if (vad<4994)
    {
    vad=(vad-4995); // Retifica a leitura de escala 0 -- 50 para escala -50 -- 0. 
    vad=-vad;
    t4=0x2D;  // Inclui o sinal "-" na temperatura.
    }
    else vad=0; // Se a leitura for "50" define a temperatura como "0".
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_temp (); //chama função que mostra temperatura.
 }

 else if (j==1) //  UMIDADE
 {
    vad=((1.0*palavra)/1023)*1000; // Obtem valor correspondente a leitura em escala de 0 à 100.
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_umidd ();
 }
 
 else if (j==2)  // PRESSÃO
 {
    vad=((257.0*(palavra-54))/968)*10 ; 
    /* palavra - 54 é desvio de offset inicial, pois 0KPa não é 0V na saída do sensor.
       assim, o novo escopo é 1023 - 54 = 968
       como na saída do sensor não é 0V com 250KPa, tem-se somar a 250, 7. */
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_press ();
 }
 
 else if (j==3)  // VELOCIDADE DO VENTO
 {
    vad=((3.0*palavra)/1023)*1000; // Obtem valor correspondente a leitura em escala de 0 à 100.
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_vent (); 
 }
}
}
o=0;
PEIE=1;
tecla=0;
}

void inicializa_timer1(void)
{
TMR1CS=0; // uso do clock de máquina.
T1OSCEN=0; // circuito oscilador desligado.
T1CKPS1=1; T1CKPS0=1; // prescaler 1:8.
TMR1H=0x0B; TMR1L=0xDC; // timer1 valor inicial 3036 (sobra 62500).
TMR1ON=1; // liga timer.
}

void teclado_INT (void)
{
o=1;
while(o)
      {
      l4=0; l1=1; RC3=0; RC0=1;
      delay_ms(200);
     
      l1=0; l2=1; RC1=1; RC0=0;
      delay_ms(200);
      
      l2=0; l3=1; RC2=1; RC1=0;
      delay_ms(200);
           
      l3=0; l4=1; RC3=1; RC2=0;
      delay_ms(200);
      }
}

void  mostra_dadoscoletados(void)
{
GIE=0;
int16 palavra=0, valor=0; float vad=0;
endereco=endereco-12; //retorna 8 posições, para ler os ultimos 4 dados gravados.

for (j=0;j<4;j++)
{
  EEPGD=0; //seleciona memoria eeprom
  EEADR=endereco;
  RD=1; //inicia leitura
  while(RD==1); //aguarda leitura
  palavra=EEDAT*256;
  endereco++;
  EEADR=endereco;
  RD=1; //inicia leitura
  while(RD==1); //aguarda leitura
  palavra=palavra+EEDAT;
  endereco++;

 if (j==0) // TEMPERATURA
 {
    vad=((10.0*palavra)/1023)*1000; // Obtem valor correspondente a leitura em escala de 0 à 100.
    t4=0x20; // Define temperatura sem sinal.
    if (vad>5000)
    {
    vad=(vad-4995); // Retifica a leitura de escala 50 -- 100 para escala 0 -- 50.
    t4=0x2B; // Inclui o sinal "+" na temperatura.
    }
    else if (vad<4994)
    {
    vad=(vad-4995); // Retifica a leitura de escala 0 -- 50 para escala -50 -- 0. 
    vad=-vad;
    t4=0x2D;  // Inclui o sinal "-" na temperatura.
    }
    else vad=0; // Se a leitura for "50" define a temperatura como "0".
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_temp (); //chama função que mostra temperatura.
 }

 else if (j==1) //  UMIDADE
 {
    vad=((1.0*palavra)/1023)*1000; // Obtem valor correspondente a leitura em escala de 0 à 100.
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_umidd ();
 }
 
 else if (j==2)  // PRESSÃO
 {
    vad=((257.0*(palavra-54))/968)*10 ; 
    /* palavra - 54 é desvio de offset inicial, pois 0KPa não é 0V na saída do sensor.
       assim, o novo escopo é 1023 - 54 = 968
       como na saída do sensor não é 0V com 250KPa, tem-se somar a 250, 7. */
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_press ();
 }
 
 else if (j==3)  // VELOCIDADE DO VENTO
 {
    vad=((3.0*palavra)/1023)*1000; // Obtem valor correspondente a leitura em escala de 0 à 100.
    valor=(int16)vad; // Casting.
    t3=valor/1000;
    t2=(valor%1000)/100;
    t1=(valor%100)/10;
    t0=(valor%10);
    palavra=0;
    mostra_vent (); 
 }
}
mostra_hora();
GIE=1;
delay_ms(20000);
tecla=0;
limpa();
}

void coleta_dados(void)
{
GIE=0;

if (endereco==48) endereco=0x00; // para a memória ciclica.
CHS3=0;CHS2=0;CHS1=0;CHS0=0; // Seleciona canal 0 (RA0) para conversão.


//********DADOS********
for (j=0; j<4; j++)
{

 //adquire dados
  GO_DONE=1; // Inicia conversão.
  while (GO_DONE); // Aguarda conversão terminar.

 //salva na memória
  EEPGD=0;// seleciona EEPROM.
  WREN=1; // habilita escrita.
  EEADR=endereco; // endereço.
  EEDAT=ADRESH; // dado a ser gravado.
  EECON2=0x55; // sequencia de sincronização.
  EECON2=0xAA;
  WR=1; // incia escrita.
  while(WR); //aguarda fim da escrita.
  endereco++; //acrescenta endereço.
  EEADR=endereco; // endereço.
  EEDAT=ADRESL; // dado a ser gravado.
  EECON2=0x55; // sequencia de sincronização.
  EECON2=0xAA;
  WR=1; // incia escrita.
  while(WR); //aguarda fim da escrita.
  endereco++; //acrescenta endereço.
 
  WREN=0; // desabilita escrita.
  ADCON0=ADCON0+4; //seleciona próximo canal para conversão.

}

//********HORA********
  EEPGD=0;// seleciona EEPROM.
  WREN=1; // habilita escrita.
  EEADR=endereco; // endereço.
  EEDAT=r1; // dado a ser gravado.
  EECON2=0x55; // sequencia de sincronização.
  EECON2=0xAA;
  WR=1; // incia escrita.
  while(WR); //aguarda fim da escrita.
  endereco++; //acrescenta endereço.

  EEADR=endereco; // endereço.
  EEDAT=r2; // dado a ser gravado.
  EECON2=0x55; // sequencia de sincronização.
  EECON2=0xAA;
  WR=1; // incia escrita.
  while(WR); //aguarda fim da escrita.
  endereco++; //acrescenta endereço.
  
  EEADR=endereco; // endereço.
  EEDAT=r3; // dado a ser gravado.
  EECON2=0x55; // sequencia de sincronização.
  EECON2=0xAA;
  WR=1; // incia escrita.
  while(WR); //aguarda fim da escrita.
  endereco++; //acrescenta endereço.
  
  EEADR=endereco; // endereço.
  EEDAT=r4; // dado a ser gravado.
  EECON2=0x55; // sequencia de sincronização.
  EECON2=0xAA;
  WR=1; // incia escrita.
  while(WR); //aguarda fim da escrita.
  endereco++; //acrescenta endereço.
  
o=0;
GIE=1;
}

void inicializa_ad(void)
{
ANSEL=0x0F; // Define RA como entrada analógica.
ADCS1=1; ADCS0=1; // RC interno.
ADFM=1; // Justifica à direita.
VCFG1=0; // Vref- => VSS.
VCFG0=0; // Vref+ => VCC.
ADON=1; // Liga sistema AD.
}

void mostra_temp (void)
{
strcpy(texto,"TMP:");
escreve (0x80,texto);
RS=0; DADO=0x84; tempo(); DADO=swap(DADO); tempo(); RS=1;
DADO=t4; tempo(); DADO=swap(DADO); tempo();
DADO=t3+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t2+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=','; tempo(); DADO=swap(DADO); tempo();
DADO=t1+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t0+0x30; tempo(); DADO=swap(DADO); tempo();
strcpy(texto," gC");
escreve (0x8A,texto);
}

void mostra_umidd (void)
{
strcpy(texto,"UMD:");
escreve (0xC0,texto);
RS=0; DADO=0xC5; tempo(); DADO=swap(DADO); tempo(); RS=1;
DADO=t3+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t2+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t1+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=','; tempo(); DADO=swap(DADO); tempo();
DADO=t0+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=' '; tempo(); DADO=swap(DADO); tempo();
DADO=0x25; tempo(); DADO=swap(DADO); tempo();
}

void mostra_press (void)
{
strcpy(texto,"PRS:");
escreve (0x94,texto);
RS=0; DADO=0x99; tempo(); DADO=swap(DADO); tempo(); RS=1;
DADO=t3+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t2+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t1+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=','; tempo(); DADO=swap(DADO); tempo();
DADO=t0+0x30; tempo(); DADO=swap(DADO); tempo();
strcpy(texto," KPa");
escreve (0x9E,texto);
}

void mostra_vent (void)
{
strcpy(texto,"VNT:");
escreve (0xD4,texto);
RS=0; DADO=0xD9; tempo(); DADO=swap(DADO); tempo(); RS=1;
DADO=t3+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t2+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=','; tempo(); DADO=swap(DADO); tempo();
DADO=t1+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=t0+0x30; tempo(); DADO=swap(DADO); tempo();
strcpy(texto," m/s");
escreve (0xDE,texto);
}

void mostra_hora(void)
{
  
RS=0; DADO=0xCF; tempo(); DADO=swap(DADO); tempo(); RS=1;
for(j=0;j<4;j++)
 {
 EEPGD=0; //seleciona memoria eeprom
  EEADR=endereco;
  RD=1; //inicia leitura
  while(RD==1); //aguarda leitura
  DADO=EEDAT+0x30; tempo(); DADO=swap(DADO); tempo();
  if (j==1) {DADO=':'; tempo(); DADO=swap(DADO); tempo();}
  endereco++;
 }
}

void apaga_memoria (void)
{
EEPGD=0;// seleciona EEPROM.
WREN=1; // habilita escrita.
EEADR=0x00; // endereço inicial.
for (j=0; j<=255; j++)
{
EEDAT=0xFF; // dado a ser gravado.
EECON2=0x55; // sequencia de sincronização.
EECON2=0xAA;
WR=1; // incia escrita.
while(WR); //aguarda fim da escrita.
EEADR++; //acrescenta endereço.
}
j=6;
WREN=0; // desabilita escrita.
}

void config_hora(void)
{
PEIE=0;
limpa();
strcpy(texto,"Digite a hora no");
escreve (0xC0,texto);
strcpy(texto,"formato hhmm");
escreve (0x94,texto);
strcpy(texto,"=>");
escreve (0xD4,texto);

r1=teclado();
DADO=r1+0x30; tempo();
DADO=swap(DADO); tempo();

r2=teclado();
DADO=r2+0x30; tempo();
DADO=swap(DADO); tempo();

r3=teclado();
DADO=r3+0x30; tempo();
DADO=swap(DADO); tempo();

r4=teclado();
DADO=r4+0x30; tempo();
DADO=swap(DADO); tempo();

tecla=0;
PEIE=1;
}

void config_tcoleta(void)
{
limpa();
strcpy(texto,"Pressione:  1=1min");
escreve (0xC0,texto);
strcpy(texto,"2=10min ou 3=1hora");
escreve (0x94,texto);
strcpy(texto,"=>");
escreve (0xD4,texto);

t_coleta=teclado();
RS=0; DADO=0xD7; tempo(); DADO=swap(DADO); tempo(); RS=1;
DADO=t_coleta+0x30; tempo();
DADO=swap(DADO); tempo();
delay_ms(800);

if (t_coleta==2) t_coleta=10;
else if (t_coleta==3) t_coleta=60;

limpa();
strcpy(texto,"Tempo alterado! ");
escreve (0x94,texto);
delay_ms(2000);
tecla=0;
}


// tratamento da interrupção externa
#INT_EXT
void interrupcao_externa (void)
{
GIE=0;
INTF=0;
limpa();
strcpy(texto,"Digite a senha");
escreve (0x80,texto);
strcpy(texto,"=>");
escreve (0xC0,texto);
o=0;
j=0;

while (j<6)
 {
 digitado[j]=teclado()+0x30;
 DADO=digitado[j]; tempo();
 DADO=swap(DADO); tempo();
 j++;

  if (j==5)
     {
        for (j=0; j <5; j++)
        {
        if (senha[j] == digitado[j])
        o++;
        }
     
     if (o==5) 
     {apaga_memoria();
     limpa();
     strcpy(texto," RESET COMPLETO!");
     escreve (0xC0,texto);
     tecla=0;
     delay_ms(1000);
     limpa(); 
     menu();
     GIE=1;
     j=7;} // apaga eeprom.
     
     else {
     limpa();
     strcpy(texto," FALHA!");
     escreve (0xC0,texto);
     delay_ms(1000);
     GIE=1;  
     j=7;} 
     }
 }
}


// tratamento interrupção timer1
#INT_TIMER1
void interrupcao_timer1 (void)
{
TMR1ON=0; // desliga timer.
TMR1IF=0; // zera a flag.
TMR1H=0x0B; TMR1L=0xDC; // timer1 valor inicial 3036 (sobra 62500).
TMR1ON=1; // liga timer.


// escreve a hora.
RS=0; DADO=0x8F; tempo(); DADO=swap(DADO); tempo(); RS=1;
DADO=r1+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=r2+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=':'; tempo(); DADO=swap(DADO); tempo();
DADO=r3+0x30; tempo(); DADO=swap(DADO); tempo();
DADO=r4+0x30; tempo(); DADO=swap(DADO); tempo();

if ((t_total-t_coleta)==t_anterior)
      {
      t_anterior=t_total;
      coleta_dados();
      }
      

r++;

if (r==1)
{
t_total++;
r=0;
r4++;
if (r4==10)
{
r4=0;
r3++;
if (r3==6)
{
r3=0;
r2++;
if (r2==10)
{
r2=0;
r1++;
}
}
}
if (r1==2 && r2==4)
{r1=0; r2=0; r3=0; r4=0;}
}
}


#INT_RB
// tratamento interrupção em RB.
void interrrupcao_RB (void)
{o=0;
     if (l1)
     {if(RB1) {tecla = 7;}
      if(RB2) {tecla = 4;}
      if(RB3) {tecla = 1;}
      if(RB4) {tecla =19;} //caracter *
      }

     else if (l2)
     {if(RB1) {tecla = 8;}
      if(RB2) {tecla = 5;}
      if(RB3) {tecla = 2;}
      if(RB4) {tecla = 0;}}

     else if (l3)
     {if(RB1) {tecla = 9;}
      if(RB2) {tecla = 6;}
      if(RB3) {tecla = 3;}
      if(RB4) {tecla =13;} //caracter #
      }
      
     else if (l4)
     {if(RB1){tecla=205;}
      if(RB2) {tecla=-6;}
      if(RB3) {tecla=-3;}
      if(RB4) {tecla=-5;} //caracter #
      }
      
      else {o=1;}
      
   RBIF=0;
}
