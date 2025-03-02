
/* USER CODE BEGIN Header */
/**
 * @file common.h 
 * @brief common header file for all the files in the project
 * 
 * @author Elkana Molson
 * @date 2025-02-27
 * 
 */

 /* USER CODE END Header */
#ifndef __COMMON_H
#define __COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "FreeRTOS.h"
// #include "task.h" // This defines TickType_t
#include "main.h"
#include "stm32f7xx_hal.h"

/**
 * @brief Defines related to event priority and task priority
 * 
 * @define EVENT_SET_PRIORITY If defined, the event manager will generate random priority
 * @define TASK_DEFAULT_PRIORITY Default priority for all the tasks
 * 
 * @brief Defines related to timing and stack size
 * 
 * @define TIME_FOR_DELAY Time for delay between the calls, waiting factors etc. in ms, 100 ms
 * @define STACK_SIZE_TIMES_MINIMAL_STACK_SIZE 2 times the minimal stack size
 * @define DEPART_TASK_STACK_SIZE 2 times the minimal stack size
 * 
 * @brief Defines related to random limits
 * 
 * @define DELADY_RANDOM_LIMIT Random delay limit of 1-5 seconds
 * @define CAR_RANDOM_LIMIT Random car ID limit of 1-4
 */
#define EVENT_SET_PRIORITY         // if defined, the event manager will generate random priority
#define TASK_DEFAULT_PRIORITY 0    // default priority for all the tasks

#define TIME_FOR_DELAY 100                    // time for delay between the calls, wainting factors etc. in ms, 100 ms
#define STACK_SIZE_TIMES_MINIMAL_STACK_SIZE 2 // 2 times the minimal stack size
#define DEPART_TASK_STACK_SIZE configMINIMAL_STACK_SIZE * STACK_SIZE_TIMES_MINIMAL_STACK_SIZE // 2 times the minimal stack size

#define DELADY_RANDOM_LIMIT 5 // 1-5 seconds  
#define CAR_RANDOM_LIMIT 4    // 1-4 carsID

  /**
   * @brief event code enum that holds the event codes for the system
   *
   */
  typedef enum
  {
    EVENT_CODE_POLICE = 1,
    EVENT_CODE_AMBULANCE = 2,
    EVENT_CODE_FIRE = 3,
    EVENT_CODE_CORONA = 4
  } EventCode_t;

  /**
   * @brief enum that holds the priority of the event
   *
   */
  typedef enum
  {
    PRIORITY_LOW = 1,
    PRIORITY_MEDIUM = 2,
    PRIORITY_HIGH = 3,
  } EventPriority_t;

  /**
   * @brief Masasge stucture that holds the message data for events
   *
   */

  typedef struct
  {
    EventCode_t eventCode;
    EventPriority_t eventPriority;
    TickType_t eventTime;
  } EventMassage_t;

/**
 * @brief Holds the resources of the system, including the counts of various emergency vehicles and other resources.
 */
typedef struct
{
    uint8_t ambulanceCount;
    uint8_t policeCount;    
    uint8_t fireCount;      // e.g 2 elements
    uint8_t coronaCount; //e.g 4 elements
    uint8_t barrowCount;    // to complete latter

} ResourceManager_t;


extern RNG_HandleTypeDef hrng;  // RNG handle for random number generation. set at main.c

void vDebugLedInit(void)
{
  DEBUG_LED_TOGGLE(DEBUG_ERROR_LED);
  DEBUG_LED_TOGGLE(DEBUG_DISPATCHER_LED);
  DEBUG_LED_TOGGLE(DEBUG_EVENT_MANAGEMENT_LED);
  HAL_Delay(1000);
  DEBUG_LED_TOGGLE(DEBUG_ERROR_LED);
  DEBUG_LED_TOGGLE(DEBUG_DISPATCHER_LED);
  DEBUG_LED_TOGGLE(DEBUG_EVENT_MANAGEMENT_LED);
}

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H */