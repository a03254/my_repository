//
// Created by Administrator on 2024/7/6.
//

#ifndef SEVOR_h
#define SEVOR_h

#define servo_open __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 2100)
#define servo_close __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1600)
void pickall();
void layall();
void fistpick1();
void fistpick();
void secondpick();
void layin1();
void layin2();
void layin3();
void layout1();
void layout2();
void layout3();
void layout1_temp();
void layout2_temp();
void layout3_temp();
void microposition(volatile uint16_t *x, volatile uint16_t *y);
void microposition0(uint16_t *x, uint16_t *y);
#endif
