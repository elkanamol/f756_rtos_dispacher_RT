// #include "cmsis_os.h"
#include "stm32f7xx_hal.h"

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "print.h"

#include "FreeRTOS.h"
#include "semphr.h"

/* USER CODE BEGIN 0 */
  // this is thread safe impllementation of printf and scanf ussing UART3.
  // this is works only if using with freeRTOS and UART3. 
  // you need to call print_init() before using printf and scanf.

  // replace your uart handle with your uart handle.
  extern UART_HandleTypeDef huart3;

  QueueHandle_t xPrintQueue = NULL;
  TaskHandle_t xPrintTaskHandle = NULL;

  static void vStartPrintTask(void *pvParameters)
  {
      PrintMessage_t message;
    
      for(;;) {
          if(xQueueReceive(xPrintQueue, &message, portMAX_DELAY) == pdTRUE) {
              HAL_UART_Transmit(&huart3, (uint8_t*)message.buffer, message.len, HAL_MAX_DELAY);
          }
          vTaskDelay(1);
      }
  }

  void print_init(UBaseType_t uxPriority) {
      xPrintQueue = xQueueCreate(PRINT_QUEUE_SIZE, sizeof(PrintMessage_t));
      xTaskCreate(vStartPrintTask, "PrintTask", configMINIMAL_STACK_SIZE * 8, NULL, uxPriority, &xPrintTaskHandle);
  }

  void print_deinit(void) {
      if (xPrintQueue != NULL) {
          vQueueDelete(xPrintQueue);
          xPrintQueue = NULL;
      }
      if (xPrintTaskHandle != NULL) {
          vTaskDelete(xPrintTaskHandle);
          xPrintTaskHandle = NULL;
      }
  }

  void print_error(const char * msg)
  {
      printf("ERROR: %s\n", msg);
      for(;;);
  }

//   int __io_putchar(int ch)
//   {
//       char c = (char)ch;
//       _write(0, &c, 1);
//       return ch;
//   }

  int _write(int __attribute__((unused)) file, char *ptr, int len) {
    PrintMessage_t message;
    
    if(len > MAX_PRINT_MSG_LEN) len = MAX_PRINT_MSG_LEN;
    
    memcpy(message.buffer, ptr, len);
    message.len = len;
    
    xQueueSend(xPrintQueue, &message, 10);
    return len;
}
//   // for scanf
//   int _read(int file, char *ptr, int len)
//   {
//       int ch = 0;

//       HAL_UART_Receive(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//       HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);

//       if (ch == 13)
//       {
//           ch = 10;
//           HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//       }
//       else if (ch == 8)
//       {
//           ch = 0x30;
//           HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//       }

//       *ptr = ch;
//       return 1;
//   }

int __io_putchar(int ch) {
    PrintMessage_t message;
    message.buffer[0] = ch;
    message.len = 1;
    
    xQueueSend(xPrintQueue, &message, 10);
    return ch;
}
