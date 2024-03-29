// Este arquivo cont�m as defini��es dos
// registradores SFR do PIC16F887

#BYTE INDF      = 0x00
#BYTE TMR0      = 0x01
#BYTE PCL      = 0x02

#BYTE STATUS   = 0x03
   #BIT IRP   = STATUS.7
   #BIT RP1   = STATUS.6
   #BIT RP0   = STATUS.5
   #BIT TO   = STATUS.4
   #BIT PD   = STATUS.3
   #BIT Z   = STATUS.2
   #BIT DC   = STATUS.1
   #BIT C   = STATUS.0
#BYTE FSR      = 0x04

#BYTE PORTA      = 0x05
   #BIT RA0    = PORTA.0
   #BIT RA1    = PORTA.1
   #BIT RA2    = PORTA.2
   #BIT RA3    = PORTA.3
   #BIT RA4    = PORTA.4
   #BIT RA5    = PORTA.5

#BYTE PORTB      = 0x06
      #BIT RB0    = PORTB.0
      #BIT RB1    = PORTB.1
   #BIT RB2    = PORTB.2
   #BIT RB3    = PORTB.3
   #BIT RB4    = PORTB.4
   #BIT RB5    = PORTB.5
   #BIT RB6    = PORTB.6
   #BIT RB7    = PORTB.7

#BYTE PORTC      = 0x07
      #BIT RC0    = PORTC.0
   #BIT RC1    = PORTC.1
   #BIT RC2    = PORTC.2
      #BIT RC3    = PORTC.3
      #BIT RC4    = PORTC.4
      #BIT RC5    = PORTC.5
      #BIT RC6    = PORTC.6
      #BIT RC7    = PORTC.7

#BYTE PORTD      = 0x08
      #BIT RD0    = PORTD.0
      #BIT RD1    = PORTD.1
      #BIT RD2    = PORTD.2
      #BIT RD3    = PORTD.3
      #BIT RD4    = PORTD.4
      #BIT RD5    = PORTD.5
      #BIT RD6    = PORTD.6
      #BIT RD7    = PORTD.7

#BYTE PORTE      = 0x09
      #BIT RE0    = PORTE.0
      #BIT RE1    = PORTE.1
      #BIT RE2    = PORTE.2

#BYTE PCLATH   = 0x0A
#BYTE INTCON   = 0x0B
   #BIT GIE   = INTCON.7
   #BIT PEIE   = INTCON.6
   #BIT TMR0IE = INTCON.5
   #BIT T0IE   = INTCON.5
   #BIT INTE   = INTCON.4
   #BIT RBIE   = INTCON.3
   #BIT TMR0IF = INTCON.2
   #BIT T0IF   = INTCON.2
   #BIT INTF   = INTCON.1
   #BIT RBIF   = INTCON.0

#BYTE PIR1      = 0x0C
   #BIT PSPIF    = PIR1.7
   #BIT ADIF    = PIR1.6
   #BIT RCIF    = PIR1.5
   #BIT TXIF    = PIR1.4
   #BIT SSPIF    = PIR1.3
   #BIT CCP1IF = PIR1.2
   #BIT TMR2IF = PIR1.1
   #BIT TMR1IF = PIR1.0

#BYTE PIR2      = 0x0D

#BYTE TMR1L      = 0x0E
#BYTE TMR1H      = 0x0F
#BYTE T1CON      = 0x10
   #BIT T1CKPS1= T1CON.5
   #BIT T1CKPS0= T1CON.4
   #BIT T1OSCEN= T1CON.3
   #BIT T1SYNC   = T1CON.2
   #BIT TMR1CS   = T1CON.1
   #BIT TMR1ON   = T1CON.0

#BYTE TMR2      = 0x11
#BYTE T2CON      = 0x12
   #BIT TOUTPS3= T2CON.6
   #BIT TOUTPS2= T2CON.5
   #BIT TOUTPS1= T2CON.4
   #BIT TOUTPS0= T2CON.3
   #BIT TMR2ON   = T2CON.2
   #BIT T2CKPS1= T2CON.1
   #BIT T2CKPS0= T2CON.0

#BYTE SSPBUF   = 0X13
#BYTE SSPCON   = 0X14
   #BIT WCOL   = SSPCON.7
   #BIT SSPOV   = SSPCON.6
   #BIT SSPEN   = SSPCON.5
   #BIT CKP   = SSPCON.4
   #BIT SSPM3   = SSPCON.3
   #BIT SSPM2   = SSPCON.2
   #BIT SSPM1   = SSPCON.1
   #BIT SSPM0   = SSPCON.0

#BYTE CCPR1L   = 0x15
#BYTE CCPR1H   = 0x16
#BYTE CCP1CON   = 0x17
   #BIT CCP1X   = CCP1CON.5
   #BIT CCP1Y   = CCP1CON.4
   #BIT CCP1M3   = CCP1CON.3
   #BIT CCP1M2   = CCP1CON.2
   #BIT CCP1M1   = CCP1CON.1
   #BIT CCP1M0   = CCP1CON.0

#BYTE RCSTA      = 0x18
   #BIT SPEN   = RCSTA.7
   #BIT RX9   = RCSTA.6
   #BIT SREN    = RCSTA.5
   #BIT CREN   = RCSTA.4
   #BIT ADDEN   = RCSTA.3
   #BIT FERR   = RCSTA.2
   #BIT OERR    = RCSTA.1
   #BIT RX9D   = RCSTA.0

#BYTE TXREG      = 0x19
#BYTE RCREG      = 0x1A

#BYTE CCPR2L   = 0x1B
#BYTE CCPR2H   = 0x1C
#BYTE CCP2CON   = 0x1D
   #BIT CCP2X   = CCP2CON.5
   #BIT CCP2Y   = CCP2CON.4
   #BIT CCP2M3   = CCP2CON.3
   #BIT CCP2M2   = CCP2CON.2
   #BIT CCP2M1   = CCP2CON.1
   #BIT CCP2M0   = CCP2CON.0

#BYTE ADRESH        = 0x1E      #BYTE ADRESL  = 0x9E
#BYTE ADCON0   = 0x1F
   #BIT ADCS1  = ADCON0.7
   #BIT ADCS0    = ADCON0.6
   #BIT CHS3     = ADCON0.5
   #BIT CHS2     = ADCON0.4
   #BIT CHS1     = ADCON0.3
   #BIT CHS0   = ADCON0.2
   #BIT GO_DONE= ADCON0.1
   #BIT ADON   = ADCON0.0

#BYTE OPTION   = 0x81
   #BIT RBPU   = OPTION.7
   #BIT INTEDG = OPTION.6
   #BIT T0CS   = OPTION.5
   #BIT T0SE   = OPTION.4
   #BIT PSA   = OPTION.3
   #BIT PS2   = OPTION.2
   #BIT PS1   = OPTION.1
   #BIT PS0   = OPTION.0

#BYTE TRISA      = 0x85
#BYTE TRISB      = 0x86
#BYTE TRISC      = 0x87
#BYTE TRISD      = 0x88
#BYTE TRISE      = 0x89
   #BIT IBF   = TRISE.7
   #BIT OBF   = TRISE.6
   #BIT IBOV   = TRISE.5
   #BIT PSPMODE   = TRISE.4

#BYTE PIE1      = 0x8C
   #BIT PSPIE    = PIE1.7
   #BIT ADIE    = PIE1.6
   #BIT RCIE    = PIE1.5
   #BIT TXIE    = PIE1.4
   #BIT SSPIE    = PIE1.3
   #BIT CCP1IE   = PIE1.2
   #BIT TMR2IE = PIE1.1
   #BIT TMR1IE = PIE1.0

#BYTE PIE2      = 0x8D
#BYTE PCON      = 0x8E
   #BIT OSCF   = PCON.3
   #BIT POR   = PCON.1
   #BIT BOD   = PCON.0

#BYTE SSPCON2   = 0x91
   #BIT GCEN    = SSPCON2.7
   #BIT ACKSTAT = SSPCON2.6
   #BIT ACKDT   = SSPCON2.5
   #BIT ACKEN   = SSPCON2.4
   #BIT RCEN    = SSPCON2.3
   #BIT PEN     = SSPCON2.2
   #BIT RSEN    = SSPCON2.1
   #BIT SEN     = SSPCON2.0   
   
#BYTE PR2      = 0x92
#BYTE SSPADD   = 0X93
#BYTE SSPSTAT   = 0X94
   #BIT SMP   = SSPSTAT.7
   #BIT CKE   = SSPSTAT.6
   #BIT DA    = SSPSTAT.5
   #BIT P     = SSPSTAT.4
   #BIT S     = SSPSTAT.3
   #BIT RW    = SSPSTAT.2
   #BIT UA    = SSPSTAT.1
   #BIT BF    = SSPSTAT.0

#BYTE WPUB      = 0x95
#BYTE IOCB      = 0x96
#BYTE ADRESL     = 0x9E
#BYTE ADCON1     = 0x9F
   #BIT ADFM     = ADCON1.7
   #BIT VCFG1    = ADCON1.5
   #BIT VCFG0    = ADCON1.4

#BYTE EEDAT    = 0x10C
#BYTE EEADR    = 0x10D
#BYTE EEDATH   = 0x10E
#BYTE EEADRH   = 0x10F

#BYTE BAUDCTL   = 0x187
   #BIT ABDOVF = BAUDCTL.7
   #BIT RCIDL  = BAUDCTL.6
   #BIT SCKP   = BAUDCTL.4
   #BIT BRG16  = BAUDCTL.3
   #BIT WUE    = BAUDCTL.1
   #BIT ABDEN  = BAUDCTL.0

#BYTE ANSEL   = 0x188
   #BIT ANS7 = ANSEL.7
   #BIT ANS6 = ANSEL.6
   #BIT ANS5 = ANSEL.5
   #BIT ANS4 = ANSEL.4
   #BIT ANS3 = ANSEL.3
   #BIT ANS2 = ANSEL.2
   #BIT ANS1 = ANSEL.1
   #BIT ANS0 = ANSEL.0
   
#BYTE ANSELH   = 0x189
   #BIT ANS13 = ANSELH.5
   #BIT ANS12 = ANSELH.4
   #BIT ANS11 = ANSELH.3
   #BIT ANS10 = ANSELH.2
   #BIT ANS9  = ANSELH.1
   #BIT ANS8  = ANSELH.0

#BYTE EECON1   = 0x18C
   #BIT EEPGD  = EECON1.7
   #BIT EEIF   = EECON1.4
   #BIT WRERR  = EECON1.3
   #BIT WREN   = EECON1.2
   #BIT WR   = EECON1.1
   #BIT RD   = EECON1.0

#BYTE EECON2   = 0x18D

#BYTE TXSTA      = 0x98
   #BIT CSRC   = TXSTA.7
   #BIT TX9   = TXSTA.6
   #BIT TXEN    = TXSTA.5
   #BIT SYNC   = TXSTA.4
   #BIT SENDB   = TXSTA.3
   #BIT BRGH   = TXSTA.2
   #BIT TRMT    = TXSTA.1
   #BIT TX9D   = TXSTA.0

#BYTE SPBRG      = 0x99
#BYTE SPBRGH      = 0x9A


