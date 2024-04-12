/*
 * segment.c
 *
 * Created: 2024-03-22 오전 9:43:37
 *  Author: SYSTEM-00
 */ 

#define  F_CPU 16000000L  //아트메가 CPU Frequency 설정, 16MHz로
#include <avr/io.h>
#include <util/delay.h>  //delay 쓰려면 이거 헤더파일 선언해줘야함

const int __delay_t = 500;
void LED(char*p, int n) // p: portx의 포인터, n : n번째 비트
{
	char b = 1 << n; //첫번째의 비트를 왼쪽으로 n칸 이동
		
	*p |= b; // PortA의 n번째 비트를 high로 출력
	_delay_ms(__delay_t); //0.5초 대기,_delay_t
		
	*p &= ~b;// PortA의 n번째 비트를 Low로 출력
	_delay_ms (__delay_t); //0.5초 대기
}

int main1(void)
{

	uint8_t numbers[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71};
	//uint8_t: 부호없는 0부터 255까지 (unsigned integer) ㅁㅁㅁㅁ ㅁㅁㅁㅁ,   unit16_t: 0부터 65535까지 ㅁㅁㅁㅁ ㅁㅁㅁㅁ ㅁㅁㅁㅁ ㅁㅁㅁㅁ
	//int8_t: 부호있는거 -128부터 127까지(integer)
	
	
	DDRD = 0xFF;	//~a~g+dot의 LED제어
	DDRC = 0x0F;	//자릿수 제어
	
		
	int i, j;
	while (1)  //embedded 프로그래밍은 무한루프가 기본이다. 무한루프 해놓고 거기에 내용 넣어야한다
	{
		
		for(i=0; i<4; i++)
		{
			//해당 자리에만 0(GNO)를 출력하고 나머지에는 1을 출력하여 자리 선택
			PORTC |= 0x0F;
			PORTC &= ~(1<<i);
			for (j=0; j<16; j++)
			{
				PORTD = numbers[j]; //숫자데이터 출력
				_delay_ms(500);		//0.5초 간격
			}
		}
	}
	return 0;
}
	

//1. 모드1은 대기상태 ( -	-	-	-)
//
//2. 모드2는 작동(카운팅)
//
//3. 모드3는 현재 상태에서 정지
//
//4. 모드4는 모드1로 회귀

