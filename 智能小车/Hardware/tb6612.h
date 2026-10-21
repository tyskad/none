 #ifndef __TB6612_H__
#define __TB6612_H__

void TB6612_Init(void);
void SetForward(uint8_t Duty);
void SetBack(void);
void TurnRight(uint8_t Speed);
void TurnLeft(uint8_t Speed);
//void TurnLeft_continue(uint8_t LSpeed,uint8_t RSpeed);
//void TurnRight_continue(uint8_t LSpeed,uint8_t RSpeed);
void Stop(void);
#endif
