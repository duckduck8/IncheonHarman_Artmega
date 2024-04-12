
#include "myHeader.h" //"" ->내가 정의 헤더
unsigned long cnt=0; 
unsigned long tcnt=0;
#include <avr/interrupt.h>

int main(void)
{
	
	DDRD = 0xFF; //세그먼트 제어 핀 8개를 출력으로 설정
	DDRC = 0x0F; //자릿수 전택 핀 4개를 출력으로 설정
	
	//TIMSK |=0x01;  //0000 0001 -> TOIE0 오버플로 인터럽트 사용  Timer 0 TCNT over flow interrupt(8비트)
	//TCCR0=0x04;  //0000 0100 -> 분주비 64로 설정
	
	TIMSK |= 0x04;  //0000 0100 -> TOIE1 오버플로 인터럽트 사용  Timer 1 TCNT over flow interrupt(16비트)
	TCCR1B=0x04;    //0000 0100 -> 분주비 64로 설정
	
	//TIMSK |=0x40;  //0100 0000 -> TOIE2 오버플로 인터럽트 사용  Timer 2 TCNT over flow interrupt(8비트)
	//TCCR2=0x04;    //0000 0100 -> 분주비 64로 설정
	
	
	SREG |= 0x80;  //status Register- 인터럽트 허용, 최상위 비트를 1로
	sei();         //set interrupt- 인터럽트 시작
	
	while (1)
	{
		if(cnt>=0x10000) cnt=0;  //FFFF에 1더하면 10000이니까 4자리 넘어가면 다시 0으로 
		Disp(cnt);
	}
}

//ISR(TIMER0_OVF_vect)
//{
	//tcnt++;
	//if(tcnt>=1000)
	//{
		//cnt++; tcnt=0;
	//}
//}

ISR(TIMER2_OVF_vect)
{
	tcnt++;
	{
		cnt++; tcnt=0;
	}
}

//ISR(TIMER2_OVF_vect)
//{
	//tcnt++;
	//if(tcnt>=500)
	//{
		//cnt++; tcnt=0;
	//}
//}
