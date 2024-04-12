/*
 * test001.c
 *
 * Created: 2024-03-20 오전 11:42:06
 * Author : SYSTEM-00
 */ 

#define  F_CPU 16000000L  //아트메가 CPU Frequency 설정, 16MHz로
#include <avr/io.h>
#include <AVR/delay.h>  //delay 쓰려면 이거 헤더파일 선언해줘야함

const int _delay_t = 500;
void TogglePinA(int n) // n : n번째 비트, dl : delay in mili-sende
{
	char b = 1 << n; //첫번째의 비트를 왼쪽으로 n칸 이동
	
	PORTA |= b; // PortA의 n번째 비트를 high로 출력
	_delay_ms(_delay_t); //0.5초 대기,_delay_t
	
	PORTA &= ~b;// PortA의 n번째 비트를 Low로 출력
	_delay_ms (_delay_t); //0.5초 대기
}

void TogglePin(int n)  //n: n번째 비트, dl: delay in m-second
{
		char b=1<<n;  //0001을 왼쪽으로 n칸 이동, 2<<n 이면 0010 이 2니까 0010을 왼쪽으로 n칸 이동
		PORTA |=b;      
		_delay_ms(500);
		PORTA &= ~b; 
		_delay_ms(500);
}

int main(void)
{
	//DDRA: 입출력 설정 레지스터
    //PORTA: 포트 레지스터
	
	
	//DDRA=0x01;  //portA 의 0번째 비트를 출력용으로 사용, 나머지는 입력 => 기존값 상관없이 걍 0000 0001 로 만든다
	//DDRA=0x02;  //portA 의 1번째 비트를 출력용으로 사용, 나머지는 입력
	
	// -> 둘이 합치기
	//DDRA=0x03;  //portA 의 0,1번째 비트를 출력용으로 사용, 나머지는 입력
	
	DDRA |= 0x07;  //portA의 0,1,2번째 비트를 출력용으로 사용
	DDRB &= ~0x01;  //portB의 0번째 비트를 입력용으로 사용, 나머지는 그대로 유지 
	
	int i=0;
    while (1)  //embedded 프로그래밍은 무한루프가 기본이다. 무한루프 해놓고 거기에 내용 넣어야한다
    {
		
		//LED 1개 켰다 껐다
		//PORTA =0x01;   //8bit 출력 Register, 출력용이니까 최하위 비트가 1이어야함 -> ㅁㅁㅁㅁ ㅁㅁㅁ1 => portA의 0번째 비트를 HIGH로 출력
		//_delay_ms(1000);
		//PORTA=0x00;    //portA의 모든 비트를 LOW로 출력   
		//_delay_ms(1000);
		
		
		//PORTA |= 0x04;  //3번째 비트를 무조건 1로 만듦    ㅁㅁㅁㅁ ㅁㅁㅁㅁ or 0000 0100 -> ㅁㅁㅁㅁ ㅁ1ㅁㅁ
		//PORTA &= ~0x04;   //3번째 비트를 무조건 0으로 만듦   ㅁㅁㅁㅁ ㅁㅁㅁㅁ and 1111 1011 -> ㅁㅁㅁㅁ ㅁ0ㅁㅁ
		
		
		
		////LED 동시에 2개 켰다 껐다
		//PORTA |=0x01;    //portA의 0번째 비트를 HIGH로 출력
		//PORTA |=0x02;    //portA의 1번째 비트를 HIGH로 출력
		//_delay_ms(1000);
		//PORTA &= ~0x01;  //portA의 0번째 비트를 LOW로 출력
		//PORTA &= ~0x02;  //portA의 1번째 비트를 LOW로 출력
		//_delay_ms(1000);
		
		
		
		//LED 2개 동시에 켰다 껐다
		//PORTA |=0x03;  //portA의 0,1번째 비트를 HIGH로 출력
		 //_delay_ms(1000);
		//PORTA &= ~0x03;  //portA의 0,1번째 비트를 LOW로 출력
		//_delay_ms(1000);
		
		
		
		//LED 3개 순차적으로 켰다껐다
		//PORTA |=0x01;   
		//_delay_ms(1000);
		//PORTA &= ~0x01;	 
		//PORTA |=0x02;    
		//_delay_ms(1000);
		//PORTA &= ~0x02;  
		//PORTA |=0x04;
		//_delay_ms(1000);
		//PORTA &=~0x04;
		
		
		
		//on/off 스위치 연결할때는 풀업저항도 (Vcc에)연결해줘야함
		//입력값 0이나 1주면 입력핀의 디지털 신호가 0도 1도아닌 번갈아가며 아무도 알 수 없는 값의 형태를 띄는데 이를 플로팅 현상이라고 한다.
		//입력값이 high일때 high로 유지 시키기 위해 입력핀이 Vcc의 전압값을 읽게 하기 위한 것
		//입력값이 low일땐 low로 유지시켜주기 위해 입력핀이 GND의 전압값을 읽게 하기 위한 것
		//스위치 눌러야 0이고, 안눌러야 1이다.
		
		if(PINB & 0x01 == 1)
		{
			TogglePin(0); //PORTA의 0번째 비트를 점멸
			TogglePin(1); //PORTA의 1번째 비트를 점멸
			TogglePin(2); //PORTA의 2번째 비트를 점멸
		}
	}
		
}

