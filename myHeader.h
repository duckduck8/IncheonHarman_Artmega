

//#ifndef INCFILE1_H_  //중복방지-다른데 중복된 것 있으면 endif까지 건너 뛰어라
//#endif
//#define INCFILE1_H_

#define F_CPU 16000000L
#include <avr/io.h>   //<>는 시스템 정의 헤더
#include <util/delay.h>
#include <avr/interrupt.h>
#define __delay_t 500


uint8_t digit[]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
char arr[5];  //세그먼트 이미지 정보를 담을 안전영역
char *PC=&PORTC, *PD=&PORTD;




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
	
	FND_4(arr);
	return arr;
}