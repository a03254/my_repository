/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//平滑切分??
void turnleft_pid(void);
void car_right_pid(unsigned int gom);
void car_left_pid(unsigned int gom);
void normal_pid(float target_data);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//?????????á????

//??????????×é


//??????????×é


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t USART1_RXbuff[20];
uint8_t code[3];
uint8_t IMU_RxBuffer[4];
uint8_t QRCODE[6];
//int16_t error_k230_x;
//int16_t error_k230_y;
union un{
    uint8_t buff[4];
    float data;
};
union un IMU_data;
 float initial_angel;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t color;
volatile uint16_t X=0;
volatile uint16_t Y=0;

uint16_t r;
uint8_t motionflag;
uint8_t k230_RxBuffer[1];   //????????????
uint16_t RxLine = 0;   //?????¤??
uint8_t DataBuff[200]; //????????

float last_data,error_data,delta_data;
float expect_data=90.00;
float k230_kp=0.5;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  LCD_Init();
  MX_UART4_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_UART5_Init();
  /* USER CODE BEGIN 2 */
    // HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
    HAL_UART_Receive_IT(&huart1,(uint8_t *)USART1_RXbuff, 7);
    HAL_UART_Receive_IT(&huart3,(uint8_t *)k230_RxBuffer, 1);
    HAL_UART_Receive_IT(&huart5,(uint8_t *)IMU_RxBuffer, 4);

    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
    RetargetInit(&huart4);

    //HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    delay_init(480);
    HAL_GPIO_WritePin(motor3_dir_GPIO_Port,motor3_dir_Pin,SET);
    HAL_GPIO_WritePin(motor4_dir_GPIO_Port,motor4_dir_Pin,SET);
    delay_ms(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//    QRCODE[0]=3;
//    QRCODE[1]=2;
//    QRCODE[2]=1;
    while (1) {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


        LCD_DrawLine(80, 40, 80, 80);//????+
        LCD_DrawLine(70, 60, 90, 60);


        delay_ms(3000);
        position0;
        while (QRCODE[0] == 0);//等待二维码识别
        while (color != QRCODE[0]);
////      {
////      // printf("color:%d\n",color);
////      }
        microposition(&X, &Y);
        fistpick();
        for(;;);
        servo_open;
        initial_angel = IMU_data.data;


        car_left_pid(1000);
        normal_pid(0);



//        while (QRCODE[0] == 0)//等待二维码识别
//        {
//            microforward(1);
//        }

        
        gotarget_s(9225);
        normal_pid(0);
        car_right_pid(400);
        normal_pid(0);

        while (color != QRCODE[0]);
//      {
//      // printf("color:%d\n",color);
//      }

        microposition(&X, &Y);
        fistpick();
        switch (QRCODE[0]) {
            case 1:
                layin1();
//                position1;
                break;
            case 2:
                layin2();
//                position2;
                break;
            case 3:
                layin3();
//                position3;
                break;
        }

        position0;
        delay_ms(100);
        for (uint8_t i = 1; i < 3; i++) {
            while (color != QRCODE[i]);

            fistpick();
            switch (QRCODE[i]) {
                case 1:
                    layin1();
//                    position1;
                    break;
                case 2:
                    layin2();
//                    position2;
                    break;
                case 3:
                    layin3();
//                    position3;
                    break;
            }

            position0;
            delay_ms(100);
        }

        car_left_pid(400);
        normal_pid(0);

        gotarget_s(2560);
        normal_pid(0);

        turnleft(2060);
        normal_pid(90);
        initial_angel = IMU_data.data;

        gotarget_s(4850);
        normal_pid(0);
        car_right_pid(800);
        normal_pid(0);

        if (QRCODE[0] == 1 && QRCODE[1] == 2 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(950);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
            fistpick();
            layin3();
            position0;
        }

        if (QRCODE[0] == 1 && QRCODE[1] == 3 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
        }

        if (QRCODE[0] == 2 && QRCODE[1] == 1 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
        }

        if (QRCODE[0] == 2 && QRCODE[1] == 3 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);

        }

        if (QRCODE[0] == 3 && QRCODE[1] == 1 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
        }

        if (QRCODE[0] == 3 && QRCODE[1] == 2 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);

        }

        car_left_pid(800);
        normal_pid(0);
        gotarget_s(3800);
        normal_pid(0);
        turnleft_pid();
        normal_pid(90);
        initial_angel=IMU_data.data;
        gotarget_s(4000);
        normal_pid(0);
        car_right_pid(300);
        normal_pid(0);


        if (QRCODE[0] == 1 && QRCODE[1] == 2 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
        }

        if (QRCODE[0] == 1 && QRCODE[1] == 3 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);

        }

        if (QRCODE[0] == 2 && QRCODE[1] == 1 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);

        }

        if (QRCODE[0] == 2 && QRCODE[1] == 3 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();



        }

        if (QRCODE[0] == 3 && QRCODE[1] == 1 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
        }

        if (QRCODE[0] == 3 && QRCODE[1] == 2 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();

        }

        car_left_pid(300);
        normal_pid(0);
        gotarget_s_back(4000);
        normal_pid(0);
        turnright(2070);
        delay_ms(100);
        normal_pid(90);
        initial_angel=IMU_data.data;

        gotarget_s_back(10550);
        normal_pid(0);
        turnright(2070);
        delay_ms(100);
        normal_pid(90);
        initial_angel=IMU_data.data;
        gotarget_s_back(2560);
        normal_pid(0);
        car_right_pid(400);

        while (color != QRCODE[4]);
//      {
//      // printf("color:%d\n",color);
//      }

        microposition(&X, &Y);
        fistpick();
        switch (QRCODE[4]) {
            case 1:
                layin1();
//                position1;
                break;
            case 2:
                layin2();
//                position2;
                break;
            case 3:
                layin3();
//                position3;
                break;
        }

        position0;
        delay_ms(100);
        for (uint8_t i = 5; i < 7; i++) {
            while (color != QRCODE[i]);

            fistpick();
            switch (QRCODE[i]) {
                case 1:
                    layin1();
//                    position1;
                    break;
                case 2:
                    layin2();
//                    position2;
                    break;
                case 3:
                    layin3();
//                    position3;
                    break;
            }

            position0;
            delay_ms(100);
        }

        car_left_pid(400);
        normal_pid(0);

        gotarget_s(2560);
        normal_pid(0);

        turnleft(2060);
        normal_pid(90);
        initial_angel = IMU_data.data;

        gotarget_s(4850);
        normal_pid(0);
        car_right_pid(800);
        normal_pid(0);

        if (QRCODE[0] == 1 && QRCODE[1] == 2 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(950);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
            fistpick();
            layin3();
            position0;
        }

        if (QRCODE[0] == 1 && QRCODE[1] == 3 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
        }

        if (QRCODE[0] == 2 && QRCODE[1] == 1 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
        }

        if (QRCODE[0] == 2 && QRCODE[1] == 3 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);

        }

        if (QRCODE[0] == 3 && QRCODE[1] == 1 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s(950);
        }

        if (QRCODE[0] == 3 && QRCODE[1] == 2 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            fistpick();
            layin3();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin2();
            position0;
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            fistpick();
            layin1();
            position0;
            normal_pid(0);
            gotarget_s(1900);

        }

        car_left_pid(800);
        normal_pid(0);
        gotarget_s(3800);
        normal_pid(0);
        turnleft_pid();
        normal_pid(90);
        initial_angel=IMU_data.data;
        gotarget_s(4000);
        normal_pid(0);
        car_right_pid(300);
        normal_pid(0);


        if (QRCODE[0] == 1 && QRCODE[1] == 2 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
        }

        if (QRCODE[0] == 1 && QRCODE[1] == 3 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);

        }

        if (QRCODE[0] == 2 && QRCODE[1] == 1 && QRCODE[2] == 3) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);

        }

        if (QRCODE[0] == 2 && QRCODE[1] == 3 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();



        }

        if (QRCODE[0] == 3 && QRCODE[1] == 1 && QRCODE[2] == 2) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(1900);
            microposition(&X, &Y);
            layout1();
            normal_pid(0);
            gotarget_s(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
        }

        if (QRCODE[0] == 3 && QRCODE[1] == 2 && QRCODE[2] == 1) {
            microposition(&X, &Y);
            normal_pid(0);
            gotarget_s(1900);
            microposition(&X, &Y);
            layout3();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout2();
            normal_pid(0);
            gotarget_s_back(950);
            microposition(&X, &Y);
            layout1();

        }

        car_left_pid(300);
        normal_pid(0);

        gotarget_s(6000);
        turnleft_pid();
        normal_pid(90);
        initial_angel=IMU_data.data;
        gotarget_s(11000);
        normal_pid(0);





        for (;;);
        delay_ms(500);
        car_left_pid(2000);
        turnleft_pid();
        servo_open;
        for (;;);

        for (;;);
        delay_ms(1000);
        car_left_pid(1000);
        gotarget_s(4900);
        gotarget_s(4425);
        car_right_pid(200);
        fistpick();
        layin1();
        for (;;);
        servo_open;
        layout1_temp();
        gotarget_s(1000);
        layout2_temp();
        gotarget_s(1000);
        layout3_temp();

        for(;;);
        secondpick();
        layin1();
        position0;
        delay_ms(50);
        secondpick();
        layin2();
        position0;
        delay_ms(50);
        secondpick();
        layin3();
        position0;
        for(;;);
        position1;
        servo_open;
        elevator_down(4000);
        servo_close;

        elevator_up(4000);

        for(;;);
        servo_open;
        elevator_down(7000);
        servo_close;
        delay_ms(10);
        elevator_up(7000);
        position1;
        servo_open;
        delay_ms(10);
        for(;;);

        servo_open;
        car_left(700);//左移出场
        gotarget_s(4900);//第一段路
        delay_ms(500);//二维码

        gotarget_s(4420);//第二段路

        delay_ms(50);//准备夹物料
        elevator_down(1700);
        car_right(200);//靠近物料



    }


  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


uint16_t data_Integer_calculate(uint8_t data_Integer_len, uint8_t data_Start_Num) {
    // ????????????
    uint16_t data_return = 0;			 // ????????
    if(data_Integer_len != 0)//?????????±
    {
        if (data_Integer_len == 1)
        {
            data_return  = (DataBuff[data_Start_Num] - 48);
        }
        else if (data_Integer_len == 2)
        {
            data_return = (DataBuff[data_Start_Num] - 48) * 10 + (DataBuff[data_Start_Num + 1] - 48);
        }
        else if (data_Integer_len == 3)
        {
            data_return = (DataBuff[data_Start_Num] - 48) * 100 + (DataBuff[data_Start_Num + 1] - 48)*10 +
                          (DataBuff[data_Start_Num + 2] - 48);
        }
        else if (data_Integer_len == 4)
        {
            data_return = (DataBuff[data_Start_Num] - 48) * 1000 + (DataBuff[data_Start_Num + 1] - 48)*100 +
                          (DataBuff[data_Start_Num + 3] - 48) * 10 + (DataBuff[data_Start_Num + 4] - 48);
        }
    }
    return data_return;  // ·???????????????????

}
void Get_Data(void)
{

    uint8_t data_X_S = 0;
    uint8_t data_X_E = 0;
    uint8_t data_X_len = 0;
    uint8_t data_Y_S = 0;
    uint8_t data_Y_E = 0;
    uint8_t data_Y_len = 0;
    uint8_t data_r_S = 0;
    uint8_t data_r_E = 0;  // ???????á??????
    uint8_t data_r_len = 0;


    // ?é????????????????????????????
    for (uint8_t i = 0; i < 200; i++)
    {
        if (DataBuff[i] == 'h') // ????h?ó????????×÷??????
            color = DataBuff[i + 1] - '0';

        else if(DataBuff[i] == 'x')
        {
            data_X_S = i + 1;
        }
        else if(DataBuff[i] == 'y')
        {
            data_X_E = i - 1;
            data_Y_S = i + 1;
        }
        else if(DataBuff[i] == 'r')
        {
            data_Y_E = i - 1;
            data_r_S = i + 1;
        }
        else if (DataBuff[i] == 'i')
        {
            data_r_E = i - 1;;  // ???????????°????????×÷???????á????
            break;
        }
    }

    data_X_len = data_X_E - data_X_S + 1;
    data_Y_len = data_Y_E - data_Y_S + 1;
    data_r_len = data_r_E - data_r_S + 1;
    X = data_Integer_calculate(data_X_len, data_X_S);
    Y = data_Integer_calculate(data_Y_len, data_Y_S);
    r = data_Integer_calculate(data_r_len, data_r_S);
    // printf("%d,%d,%d,%d\r\n", color,X,Y, r);
}
void turnleft_pid(void){

    last_data = initial_angel;
    turnleft(2060);
    delay_ms(100);
    delta_data = IMU_data.data - last_data;
    if (last_data > 0 && IMU_data.data < 0 &&  delta_data<-180) {
        delta_data += 360;//解决跨越0度的问题
    }
    error_data = delta_data - expect_data;//计算误差

    while ((error_data > 0.5 || error_data < -0.5)) {
        if(motionflag) {
            motionflag = 0;
            if (error_data > 0) {
                //microturnright(5);
                microturnright(error_data * 10);
            } else {
                //microturnleft(5);
                microturnleft((-error_data) * 10);
            }


            //printf("error_data：%f\n", error_data);
        }
        delta_data = IMU_data.data - last_data;//做差
        if (last_data > 0 && IMU_data.data < 0 && delta_data<-180) {
            delta_data += 360;//解决跨越0度的问题
        }
        error_data = delta_data - expect_data;//计算误差
    }
}



void normal_pid(float target_data) {
    last_data = initial_angel + target_data;
    delta_data = IMU_data.data - last_data;
    if (last_data > 0 && IMU_data.data < 0 && delta_data<-180) {
        delta_data += 360;//解决跨越0度的问题
    }
    error_data = delta_data;//计算误差
    while (error_data > 0.1 || error_data < -0.1) {
        if (motionflag) {
            motionflag = 0;
            printf("%f\n",error_data);
            if (error_data > 0) {
                //microturnright(5);
                microturnright(error_data * 12);
            } else {
                //microturnleft(5);
                microturnleft((-error_data) * 12);
            }
            //printf("error_data：%f\n", error_data);
        }
        delta_data = IMU_data.data - last_data;//做差
        if (last_data > 0 && IMU_data.data < 0 && delta_data<-180) {
            delta_data += 360;//解决跨越0度的问题
        }
        error_data = delta_data;//计算误差
    }
}
void car_right_pid(unsigned int gom){
    last_data = IMU_data.data;
    car_right(gom);
    delta_data = IMU_data.data - last_data;
    if (last_data > 0 && IMU_data.data < 0) {
        delta_data += 360;//解决跨越0度的问题
    }
    error_data = delta_data;//计算误差
    while ((error_data > 0.1 || error_data < -0.1)) {
        if(motionflag) {
            motionflag = 0;
            if (error_data > 0) {
                //microturnright(5);
                microturnright(error_data * 10);
            } else {
                //microturnleft(5);
                microturnleft((-error_data) * 10);
            }


        }
        delta_data = IMU_data.data - last_data;//做差
        if (last_data > 0 && IMU_data.data < 0 && delta_data<-180) {
            delta_data += 360;//解决跨越0度的问题
        }
        error_data = delta_data;//计算误差
        //printf("error_data：%f\n", error_data);
    }
}
void car_left_pid(unsigned int gom){
    last_data = IMU_data.data;
    car_left(gom);
    delta_data = IMU_data.data - last_data;
    if (last_data > 0 && IMU_data.data < 0) {
        delta_data += 360;//解决跨越0度的问题
    }
    error_data = delta_data;//计算误差
    while ((error_data > 0.1 || error_data < -0.1)) {
        if(motionflag) {
            motionflag = 0;
            if (error_data > 0) {
                //microturnright(5);
                microturnright(error_data * 10);
            } else {
                //microturnleft(5);
                microturnleft((-error_data) * 10);
            }


        }
        delta_data = IMU_data.data - last_data;//做差
        if (last_data > 0 && IMU_data.data < 0&&delta_data<-180) {
            delta_data += 360;//解决跨越0度的问题
        }
        error_data = delta_data;//计算误差
        //printf("error_data：%f\n", error_data);
    }
}
// ???????????????÷????

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)//openmv识别到二维码
    {
        code[0]=USART1_RXbuff[0]-48;
        code[1]=USART1_RXbuff[1]-48;

        code[2]=USART1_RXbuff[2]-48;
        if(USART1_RXbuff[0]-48 == 1)
        {
            LCD_DrawLine(10, 20, 10, 100);//????1
            if(USART1_RXbuff[1]-48 == 2)
            {
                QRCODE[0]=1;
                QRCODE[1]=2;
                QRCODE[2]=3;

                LCD_DrawLine(20, 20, 35, 20);//????2
                LCD_DrawLine(35, 20, 35, 60);
                LCD_DrawLine(20, 60, 35, 60);
                LCD_DrawLine(20, 60, 20, 100);
                LCD_DrawLine(20, 100, 35, 100);
                LCD_DrawLine(45, 20, 60, 20);//????3
                LCD_DrawLine(60, 20, 60, 60);
                LCD_DrawLine(45, 60, 60, 60);
                LCD_DrawLine(60, 60, 60, 100);
                LCD_DrawLine(45, 100, 60, 100);
            }
            if(USART1_RXbuff[1]-48 == 3)
            {
                QRCODE[0]=1;
                QRCODE[1]=3;
                QRCODE[2]=2;

                LCD_DrawLine(20, 20, 35, 20);//????2
                LCD_DrawLine(35, 20, 35, 60);
                LCD_DrawLine(20, 60, 35, 60);
                LCD_DrawLine(35, 60, 35, 100);
                LCD_DrawLine(20, 100, 35, 100);
                LCD_DrawLine(45, 20, 60, 20);//????3
                LCD_DrawLine(60, 20, 60, 60);
                LCD_DrawLine(45, 60, 60, 60);
                LCD_DrawLine(45, 60, 45, 100);
                LCD_DrawLine(45, 100, 60, 100);
            }

        }
        if(USART1_RXbuff[0]-48 == 2)
        {
            LCD_DrawLine(10, 20, 25, 20);//????2
            LCD_DrawLine(25, 20, 25, 60);
            LCD_DrawLine(10, 60, 25, 60);
            LCD_DrawLine(10, 60, 10, 100);
            LCD_DrawLine(10, 100, 25, 100);
            if(USART1_RXbuff[1]-48 == 1)
            {
                QRCODE[0]=2;
                QRCODE[1]=1;
                QRCODE[2]=3;

                LCD_DrawLine(35, 20, 35, 100);//????1
                LCD_DrawLine(45, 20, 60, 20);//????3
                LCD_DrawLine(60, 20, 60, 60);
                LCD_DrawLine(45, 60, 60, 60);
                LCD_DrawLine(60, 60, 60, 100);
                LCD_DrawLine(45, 100, 60, 100);
            }
            if(USART1_RXbuff[1]-48 == 3)
            {
                QRCODE[0]=2;
                QRCODE[1]=3;
                QRCODE[2]=1;

                LCD_DrawLine(60, 20, 60, 100);//????1
                LCD_DrawLine(35, 20, 50, 20);//????3
                LCD_DrawLine(50, 20, 50, 60);
                LCD_DrawLine(35, 60, 50, 60);
                LCD_DrawLine(50, 60, 50, 100);
                LCD_DrawLine(35, 100, 50, 100);
            }
        }
        if(USART1_RXbuff[0]-48 == 3)
        {
            LCD_DrawLine(10, 20, 25, 20);//????3
            LCD_DrawLine(25, 20, 25, 60);
            LCD_DrawLine(10, 60, 25, 60);
            LCD_DrawLine(25, 60, 25, 100);
            LCD_DrawLine(10, 100,25, 100);
            if(USART1_RXbuff[1]-48 == 1)
            {
                QRCODE[0]=3;
                QRCODE[1]=1;
                QRCODE[2]=2;

                LCD_DrawLine(35, 20, 35, 100);//????1
                LCD_DrawLine(45, 20, 60, 20);//????2
                LCD_DrawLine(60, 20, 60, 60);
                LCD_DrawLine(45, 60, 60, 60);
                LCD_DrawLine(45, 60, 45, 100);
                LCD_DrawLine(45, 100, 60, 100);
            }
            if(USART1_RXbuff[1]-48 == 2)
            {
                QRCODE[0]=3;
                QRCODE[1]=2;
                QRCODE[2]=1;

                LCD_DrawLine(60, 20, 60, 100);//????1
                LCD_DrawLine(35, 20, 50, 20);//????2
                LCD_DrawLine(50, 20, 50, 60);
                LCD_DrawLine(35, 60, 50, 60);
                LCD_DrawLine(35, 60, 35, 100);
                LCD_DrawLine(35, 100, 50, 100);
            }
        }

        if(USART1_RXbuff[4]-48 == 1)
        {
            LCD_DrawLine(10+90, 20, 10+90, 100);//????1
            if(USART1_RXbuff[5]-48 == 2)
            {
                QRCODE[3]=1;
                QRCODE[4]=2;
                QRCODE[5]=3;

                LCD_DrawLine(20+90, 20, 35+90, 20);//????2
                LCD_DrawLine(35+90, 20, 35+90, 60);
                LCD_DrawLine(20+90, 60, 35+90, 60);
                LCD_DrawLine(20+90, 60, 20+90, 100);
                LCD_DrawLine(20+90, 100, 35+90, 100);
                LCD_DrawLine(45+90, 20, 60+90, 20);//????3
                LCD_DrawLine(60+90, 20, 60+90, 60);
                LCD_DrawLine(45+90, 60, 60+90, 60);
                LCD_DrawLine(60+90, 60, 60+90, 100);
                LCD_DrawLine(45+90, 100, 60+90, 100);
            }
            if(USART1_RXbuff[5]-48 == 3)
            {
                QRCODE[3]=1;
                QRCODE[4]=3;
                QRCODE[5]=2;

                LCD_DrawLine(20+90, 20, 35+90, 20);//????2
                LCD_DrawLine(35+90, 20, 35+90, 60);
                LCD_DrawLine(20+90, 60, 35+90, 60);
                LCD_DrawLine(35+90, 60, 35+90, 100);
                LCD_DrawLine(20+90, 100, 35+90, 100);
                LCD_DrawLine(45+90, 20, 60+90, 20);//????3
                LCD_DrawLine(60+90, 20, 60+90, 60);
                LCD_DrawLine(45+90, 60, 60+90, 60);
                LCD_DrawLine(45+90, 60, 45+90, 100);
                LCD_DrawLine(45+90, 100, 60+90, 100);
            }

        }
        if(USART1_RXbuff[4]-48 == 2)
        {
            LCD_DrawLine(10+90, 20, 25+90, 20);//????2
            LCD_DrawLine(25+90, 20, 25+90, 60);
            LCD_DrawLine(10+90, 60, 25+90, 60);
            LCD_DrawLine(10+90, 60, 10+90, 100);
            LCD_DrawLine(10+90, 100, 25+90, 100);
            if(USART1_RXbuff[5]-48 == 1)
            {
                QRCODE[3]=2;
                QRCODE[4]=1;
                QRCODE[5]=3;

                LCD_DrawLine(35+90, 20, 35+90, 100);//????1
                LCD_DrawLine(45+90, 20, 60+90, 20);//????3
                LCD_DrawLine(60+90, 20, 60+90, 60);
                LCD_DrawLine(45+90, 60, 60+90, 60);
                LCD_DrawLine(60+90, 60, 60+90, 100);
                LCD_DrawLine(45+90, 100, 60+90, 100);
            }
            if(USART1_RXbuff[5]-48 == 3)
            {
                QRCODE[3]=2;
                QRCODE[4]=3;
                QRCODE[5]=1;

                LCD_DrawLine(60+90, 20, 60+90, 100);//????1
                LCD_DrawLine(35+90, 20, 50+90, 20);//????3
                LCD_DrawLine(50+90, 20, 50+90, 60);
                LCD_DrawLine(35+90, 60, 50+90, 60);
                LCD_DrawLine(50+90, 60, 50+90, 100);
                LCD_DrawLine(35+90, 100, 50+90, 100);
            }
        }
        if(USART1_RXbuff[4]-48 == 3)
        {
            LCD_DrawLine(10+90, 20, 25+90, 20);//????3
            LCD_DrawLine(25+90, 20, 25+90, 60);
            LCD_DrawLine(10+90, 60, 25+90, 60);
            LCD_DrawLine(25+90, 60, 25+90, 100);
            LCD_DrawLine(10+90, 100,25+90, 100);
            if(USART1_RXbuff[5]-48 == 1)
            {
                QRCODE[3]=3;
                QRCODE[4]=1;
                QRCODE[5]=2;

                LCD_DrawLine(35+90, 20, 35+90, 100);//????1
                LCD_DrawLine(45+90, 20, 60+90, 20);//????2
                LCD_DrawLine(60+90, 20, 60+90, 60);
                LCD_DrawLine(45+90, 60, 60+90, 60);
                LCD_DrawLine(45+90, 60, 45+90, 100);
                LCD_DrawLine(45+90, 100, 60+90, 100);
            }
            if(USART1_RXbuff[5]-48 == 2)
            {
                QRCODE[3]=3;
                QRCODE[4]=2;
                QRCODE[5]=1;

                LCD_DrawLine(60+90, 20, 60+90, 100);//????1
                LCD_DrawLine(35+90, 20, 50+90, 20);//????2
                LCD_DrawLine(50+90, 20, 50+90, 60);
                LCD_DrawLine(35+90, 60, 50+90, 60);
                LCD_DrawLine(35+90, 60, 35+90, 100);
                LCD_DrawLine(35+90, 100, 50+90, 100);
            }
        }
        LCD_DrawLine(80, 40, 80, 80);//????+
        LCD_DrawLine(70, 60, 90, 60);

        //HAL_UART_Receive_IT(&huart1,(uint8_t *)USART1_RXbuff, 7);
    }
    if (huart->Instance == USART3)  // ??????·???????2?ú?ú??????
    {

        RxLine++;                        // ???????????????????????¤????1
        DataBuff[RxLine - 1] = k230_RxBuffer[0];  // ????????????????????????×é

        if (k230_RxBuffer[0] == 'i')         // ??????·????????á??±ê???¨??????0x21???????????ù???????é????????
        {
              // ?????????????????¤??

            Get_Data();  // ????????????????????±????¨????????????????1?????ù???????é????????
            memset(DataBuff, 0, sizeof(DataBuff));  // ????????????
            RxLine = 0;  // ?????????¤??????
        }

        k230_RxBuffer[0] = 0;  // ????????????
        HAL_UART_Receive_IT(&huart3, (uint8_t *)k230_RxBuffer, 1);  // ??????????????????????????×???

    }

    if (huart->Instance == UART5)  // IMU
    {
        IMU_data.buff[0] = IMU_RxBuffer[0];
        IMU_data.buff[1] = IMU_RxBuffer[1];
        IMU_data.buff[2] = IMU_RxBuffer[2];
        IMU_data.buff[3] = IMU_RxBuffer[3];
        motionflag = 1;
        printf("IMU_data:%f\n",IMU_data.data);
        HAL_UART_Receive_IT(&huart5, (uint8_t *)IMU_RxBuffer, 4);  // ??????????????????????????×???
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
