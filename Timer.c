
//외부 인터럽트 기능과 Timer 인터럽트를 이용하여 다음 수행조건을 만족하는 주방 타이머를 제작하시오.
//[ 기능 ] :
//- 시계 기능 : 대기상태  or  비동작상태
//- 타이머 기능 : Start / Stop / Restart / Reset - 설정시간 도달시 LED 점멸 (알람기능)
//- 설정 기능 :
//타이머 설정 : 00분 00초 설정 - 세그먼트 단위, UP / DOWN / 확인
//- 동작 시나리오(예시)
//1. 대기상태 : 0000
//2. [START]  : 초단위 카운팅 --> 설정시간 도달시 LED (부저) 점멸
//3. [STOP/RESET] : 카운팅 정지 / 대기상태
//4. [설정] :
//4-1. 설정모드에서 세그먼트별 [UP/DOWN]
//4-2 [확인] : 다음 세그먼트로 이동. 완료시 설정모드 종료. 대기상태


#define F_CPU 16000000L
#include <avr/io.h>   //<>는 시스템 정의 헤더
#include <util/delay.h>
#include <avr/interrupt.h>
#define __delay_t 500


uint8_t digit[]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
char arr[5];  //세그먼트 이미지 정보를 담을 안전영역
char *PC=&PORTC, *PD=&PORTD;

volatile int opmode=0, up=0, next=0; //컴파일 최적화 금지
#define  OPMODEMAX 3
#define  RE_MAX 3

void display(int position, int number)
{

	*PC &=~0x0F;            //나는 세그먼트 타입이 달라서 넣어줘야 하는 값이랑 정 반대로 해줘야함, 원래 PORTC |=0x0F;
	*PC |= (1<<(3-position));    //PORTC &= ~(1<<(3-sel));
	*PD=digit[number];                 //PORTD=c
	_delay_ms(5);
}

void seg(int sel, uint8_t c)
{

	*PC &=~0x0F;            //나는 세그먼트 타입이 달라서 넣어줘야 하는 값이랑 정 반대로 해줘야함, 원래 PORTC |=0x0F;
	*PC |= (1<<(3-sel));    //PORTC &= ~(1<<(3-sel));
	*PD=~c;                 //PORTD=c
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
	
	int n1= num%10;       //A : 문자가 아닌 숫자
	int n2=(num/10) %10;  //B
	int n3=(num/100) %10; //C
	int n4= (num/1000);   //D
	arr[0]=digit[n1];
	arr[1]=digit[n2];
	arr[2]=digit[n3];
	arr[3]=digit[n4];
	
	display(next, up);
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
		//switch(opmode)
		//{
			//case 0:  //reset 
			//up=0;
			//next=0;
			//break;
			//
			//case 1:  //counter start
			//t++; break;
			//case 2:  //counter stop
			//break;
			//default: break;
		//}
		//
		
	
	display(next, up);
	
	if(opmode==1)
	{
		opmode=0;
		up=0;
		next=0;
	}
	

		
		
		
		
		//switch(next)
		//{
			//case 0:
			//Disp(up);
			//break;
			//
			//case 1:
			//Disp(up);
			//break;
			//
			//case 2:
			//Disp(up);
			//break;
			//
			//case 3:
			//Disp(up);
			//break;
			//
		//}
		
		
		
	}
}


ISR(INT4_vect)  //INT4 인터럽트 처리루틴: sw1
{
	opmode++;
	if(opmode>3) opmode=0;
	
}
ISR(INT5_vect)  //up & down
{
	up++;
	if(up>9) up=0;
}
ISR(INT6_vect)  //넘기기
{
	next++;
	if(next>3) next=0;

}

