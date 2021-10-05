static void init_pushButton() // pc1 push button > turns on pd3 led
 {	  
    PORTC.DIR &= ~(PIN1_bm);	  PORTC.PIN1CTRL |= PORT_PULLUPEN_bm; // pc7 as push button to be debounced with timer B1 one shot 10ms delay
	  
	  PORTD.DIR |= PIN3_bm; PORTD.OUT |= PIN3_bm; // pd3 as Led output
	  
	 EVSYS.CHANNEL3 = EVSYS_CHANNEL3_PORTC_PIN1_gc;
	 EVSYS.USERTCB1CAPT = EVSYS_USER_CHANNEL3_gc;

// TCB_1_init(void) ...keeping tcb0 free , since i am using it for millis
	 TCB1.CCMP = 0xFFFF;
	 TCB1.CTRLB = TCB_CNTMODE_SINGLE_gc;
	 TCB1.EVCTRL = TCB_CAPTEI_bm | TCB_EDGE_bm;
	 TCB1.CTRLA = TCB_CLKSEL0_bm | TCB_ENABLE_bm;
	 TCB1.CTRLA   |= TCB_CLKSEL_DIV2_gc;
	 TCB1.CNT = 0xFFFF;
	 TCB1.INTCTRL = TCB_CAPT_bm;
 }
 
 ISR(TCB1_INT_vect)
 {	 if (PORTC.IN & PIN1_bm) {
		  PORTD.OUTSET |= PIN3_bm;
	 }
	 else	 {
		 PORTD.OUTCLR |= PIN3_bm;
	 }
	 TCB1.INTFLAGS = TCB_CAPT_bm;
 }
