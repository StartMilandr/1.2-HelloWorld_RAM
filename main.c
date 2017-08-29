#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>

//  �������� ������� ��������, ������������� ����
void Delay(int waitTicks);

#define delayTicks 50000

//  ����� �����, ������ ���������� ���������� ���������
int main()
{
	// ������� ��������� ������������ ������(-��) ����� GPIO
  PORT_InitTypeDef GPIOInitStruct;

  //  �������� ������������ ����� C
  RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC, ENABLE);

  //  �������������� ��������� ������������ ������(-��) ����� ���������� �� ���������
  PORT_StructInit(&GPIOInitStruct);
  
  //  �������� �������� �� ��������� �� ����������� ��� ���������
  GPIOInitStruct.PORT_Pin        = PORT_Pin_0;
  GPIOInitStruct.PORT_OE         = PORT_OE_OUT;
  GPIOInitStruct.PORT_SPEED      = PORT_SPEED_SLOW;
  GPIOInitStruct.PORT_MODE       = PORT_MODE_DIGITAL;
  
  //  ��������� ����������� ���� ��������� ��� PORTC.
  PORT_Init(MDR_PORTC, &GPIOInitStruct);

  //  ��������� ����������� ���� ��������� - �������� ����	
  while (1)
  {
    // ��������� ��������� ���� PD0
    // ���� �� ������ ���������� "0", �� ���������� ����� � ���������� "1"
    if (PORT_ReadInputDataBit (MDR_PORTC, PORT_Pin_0) == 0)
    {	
	PORT_SetBits(MDR_PORTC, PORT_Pin_0);	// LED
    }	
    
    //  ��������
    Delay(delayTicks);

    // ��������� ��������� ���� PD0
    // ���� �� ������ = "1", �� ���������� "0"
    if (PORT_ReadInputDataBit (MDR_PORTC, PORT_Pin_0) == 1)
    {
	PORT_ResetBits(MDR_PORTC, PORT_Pin_0);
    };
    
    //  ��������    
    Delay(delayTicks);
  }      
}

//  ���������� ������� ��������, ������� �� ������� �� �� ���������� ����� ������
void Delay(int waitTicks)
{
  int i;
  for (i = 0; i < waitTicks; i++)
  {
    __NOP();
  }	
}
