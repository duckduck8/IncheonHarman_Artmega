
/*
 * segment.c
 *
 * Created: 2024-03-22 오전 9:43:37
 *  Author: SYSTEM-00
 */ 

//#define  F_CPU 16000000L  //아트메가 CPU Frequency 설정, 16MHz로
//#include <avr/io.h>
//#include <util/delay.h>  //delay 쓰려면 이거 헤더파일 선언해줘야함
//
//uint8_t numbers[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71};
	////uint8_t: 부호없는 0부터 255까지 (unsigned integer) ㅁㅁㅁㅁ ㅁㅁㅁㅁ,   unit16_t: 0부터 65535까지 ㅁㅁㅁㅁ ㅁㅁㅁㅁ ㅁㅁㅁㅁ ㅁㅁㅁㅁ
	////int8_t: 부호있는거 -128부터 127까지(integer)
//
//char arr[5];
	//
//
//void seg(int sel, uint8_t c)
//{
	//
	//PORTC |=0x0F;
	//PORTC &= ~(1<<(3-sel));
	//PORTD=c;
	//_delay_ms(10);
//}
//
//void FND_4(char*inf)  //segment Image 배열
//{
	//for(int i=0; i<4; i++)
	//{
		//seg(i, *(inf+i));
		////seg(i, inf[i]);
	//}
//}
//
//char* Trans(int num)   //10진 정수 => 16진수 문자열로 56506 => 0xDCBA
//{                                //=> 16진수 segment Image 배열
	//int n1= num%16;       //A : 문자가 아닌 숫자
	//int n2=(num/16) %16;  //B
	//int n3=(num/256) %16; //C
	//int n4= (num/4096);   //D
	//arr[0]=numbers[n1];
	//arr[1]=numbers[n2];
	//arr[2]=numbers[n3];
	//arr[3]=numbers[n4];
	//
	//return arr;
	//
//}
//
//
//void LED(char*p, int n) // p: portx의 포인터, n : n번째 비트
//{
	//char b = 1 << n; //첫번째의 비트를 왼쪽으로 n칸 이동
		//
	//*p |= b; // PortA의 n번째 비트를 high로 출력
	//_delay_ms(500); //0.5초 대기
		//
	//*p &= ~b;// PortA의 n번째 비트를 Low로 출력
	//_delay_ms (5000); //0.5초 대기
//}
//
//int main(void)
//{
	//int i, j=0;
//
	//DDRD = 0xFF;	//세그먼트 제어 핀 8개를 출력으로 설정(~a~g+dot의 LED제어)
	//DDRC = 0x0F;	//자릿수 선택 핀 4개를 출력으로 설정
	//
		//
	//while(1)
	//{
		//FND_4(Trans(j++));
		//_delay_ms(10);
	//}
	//
	//
	//
	//
	//
	//
	//
	////segment 동작
	//
	////uint8_t numbers[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71};
	////uint8_t: 부호없는 0부터 255까지 (unsigned integer) ㅁㅁㅁㅁ ㅁㅁㅁㅁ,   unit16_t: 0부터 65535까지 ㅁㅁㅁㅁ ㅁㅁㅁㅁ ㅁㅁㅁㅁ ㅁㅁㅁㅁ
	////int8_t: 부호있는거 -128부터 127까지(integer)
	//
	////while (1)  //embedded 프로그래밍은 무한루프가 기본이다. 무한루프 해놓고 거기에 내용 넣어야한다
	////{
		////
		////for(i=0; i<4; i++)
		////{
			//////해당 자리에만 0(GNO)를 출력하고 나머지에는 1을 출력하여 자리 선택
			////PORTC |= 0x0F;
			////PORTC &= ~(1<<i);
			////for (j=0; j<10; j++)
			////{
				////PORTD = numbers[j]; //숫자데이터 출력
				////_delay_ms(100);		//0.5초 간격
			////}
		////}
	////}
	//
	//
	//
	//return 0;
//}
	





//STOP WATCH
//1. 모드1은 대기상태 ( -	-	-	-)
//2. 모드2는 작동(카운팅)
//3. 모드3는 현재 상태에서 정지
//4. 모드4는 모드1로 회귀

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
uint8_t numbers[]
= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71, 0x40, 0x00};


void display(int *d)
{
	int i;
	for(i = 0; i < 4 ; i++)
	{
		PORTC |= 0x0f;
		PORTC &= ~(0x08 >> i);
		PORTD = numbers[d[i]];
		_delay_ms(100);
	}
}

void reset()
{
	int i = 0;
	PORTC = 0x00;
	//PORTE &= ~(1<<i);
	PORTD = numbers[17];
}
//PORTE에 0이 출력 1이 출력 안함

int main(void)
{
	
	DDRD = 0xFF; //세그먼트 제어 핀 8개를 출력으로 설정
	DDRC = 0x0F; //자릿수 전택 핀 4개를 출력으로 설정
	DDRB &= ~0x01; //PORTB의 스위치를 입력으로 설정
	
	int i = 0, count = 0;
	int start = 0; // 0 stop     1 start     2 pause
	int d[4] = {0,0,0,0};
	reset();
	while (1)
	{
		if(!(PINB & 1) == 1)
		{
			_delay_ms(200);
			switch(start)
			{
				case 0:
				start = 1;
				break;
				
				case 1:
				start = 2;
				break;
				
				case 2:
				reset();
				start = 0;
				count = 0;
				break;
			}
		}
		
		switch(start)
		{
			case 1:
			
			d[0] = count%10;
			d[1] = (count%100)/10;
			d[2] = (count%1000)/100;
			d[3] = count/1000;//count max 9999
			
			if(!(count/1000)) {    //숫자가 작을시에 무표시 해주는 if문
				
				d[3]=17;
				
				if(!(count/100)) {
					
					d[2]=17;
					
					if(!(count/10)) {
						
						d[1]=17;
						
					}
				}
			}

			display(d);
			//_delay_ms(200);
			count ++;
			if(count>=10000) { // 9999까지 돌았을 때 다시 0부터 돌게 해주는 if문
				count = 0;
			}
			break;
			
			case 2:
			display(d);
			break;
			
			default:
			start = 0;
			reset;
			break;
		}
		
		
	}
	return 0;
}

