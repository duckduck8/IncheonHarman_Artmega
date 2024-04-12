

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t digit[]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71, 0x40};
char arr[5];  //세그먼트 이미지 정보를 담을 안전영역
volatile int opmode=0, state=0, re=0; //컴파일 최적화 금지
#define  OPMODEMAX 3
#define  STATE_MAX 3
#define  RE_MAX 3


void seg(int sel, uint8_t c)
{

	PORTC &=~0x0F;            //나는 세그먼트 타입이 달라서 넣어줘야 하는 값이랑 정 반대로 해줘야함, 원래 PORTC |=0x0F; 
	PORTC |= (1<<(3-sel));    //PORTC &= ~(1<<(3-sel));
	PORTD=~c;                 //PORTD=c
	_delay_ms(1);
}

void FND_4(char*inf)  //segment Image 배열
{
	int i=0;
	for(i=0; i<4; i++)
	{
		seg(i, *(inf+i));
		//seg(i, inf[i]);
		_delay_ms(1);
	}
}

char* Disp(unsigned long num)   //10진 정수 => 16진수 문자열로 56506 => 0xDCBA
{                                //=> 4digit 16진수 segment 출력
	
	int n1= num%16;       //A : 문자가 아닌 숫자
	int n2=(num/16) %16;  //B
	int n3=(num/256) %16; //C
	int n4= (num/4096);   //D
	arr[0]=digit[n1];
	arr[1]=digit[n2];
	arr[2]=digit[n3];
	arr[3]=digit[n4];

	FND_4(arr);
	return arr;

}

int main(void)
{
	
	//7 Segment 사용: 4 module - C_type
	//Pin assign:    PAx: segement image, PBx: module select
	//Interrupt 사용: INT4~INT6 (external interrupt)
	//Pin assign:     PE4~PE6   
	
	//                                                7 6 5 4  3 2 1 0
	EIMSK=0x70; //0111 0000  EIMSK중에 INT 4,5,6 사용  ㅁㅁㅁㅁ ㅁㅁㅁㅁ
	//                                                                 7  6    5   4
	EICRB=0x2a; //0010 1010  EICRB(INT4,5,6,7이 B그룹 -> B그룹 사용)   ㅁㅁㅁㅁ ㅁㅁㅁㅁ  (해당하는 비트를 11 (핀 입력값이 low에서 high로 상승하는 rising edge에서 동작) 또는 10 (high에서 low로 하강하는 falling edge)로 해줘야함)
	SREG |= 0x80;  //status Register- 인터럽트 허용, 최상위 비트를 1로
	sei();         //set interrupt- 인터럽트 시작
	
	DDRD = 0xFF; //세그먼트 제어 핀 8개를 출력으로 설정
	DDRC = 0x0F; //자릿수 전택 핀 4개를 출력으로 설정
    
	long t=0;
	while (1) 
    {
		switch(opmode)
		{
			case 0:  //reset and wait
				t=0; break;
			case 1:  //counter start
				t++; break;
			case 2:  //counter stop
				break;
			default: break;
		}
	
		
		
		//switch(state)
		//{
			//case 0:
				//t=0; break;
			//case 1:
				//t++;
				//if (t>=500)
				//break;
			//case 2:
				//break;
			//default: break;
			//
		//}
		//
		//switch(re)
		//{
			//
		//case 0:
		//}
		
		Disp(t);
		_delay_ms(10);
			
	
    }
}


ISR(INT4_vect)  //INT4 인터럽트 처리루틴: sw1
{
	opmode++;
	if(opmode>=OPMODEMAX) opmode=0;
}
ISR(INT5_vect)  //INT5 인터럽트 처리루틴: sw2
{
	state++;
	if(state>=STATE_MAX) state=0;
}
ISR(INT6_vect)  //INT6 인터럽트 처리루틴: sw3
{
	re++;
	if(re>=RE_MAX) re=0;
}












