
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

/* Priority Macros Configurations */
#define EVENT_SET_PRIORITY         // if defined, the event manager will generate random priority
#define TASK_DEFAULT_PRIORITY 0    // default priority for all the tasks

/* Task and Stack Size Configurations */
#define TIME_FOR_DELAY 100                    // time for delay between the calls, wainting factors etc. in ms, 100 ms
#define STACK_SIZE_TIMES_MINIMAL_STACK_SIZE 2 // 2 times the minimal stack size
#define DEPART_TASK_STACK_SIZE configMINIMAL_STACK_SIZE * STACK_SIZE_TIMES_MINIMAL_STACK_SIZE // 2 times the minimal stack size

/* Car and delay random values */
#define DELADY_RANDOM_LIMIT 5 // 1-5 seconds  
#define CAR_RANDOM_LIMIT 4    // 1-4 carsID

  /* Debug Print Configuration */
#define DEBUG_PRINT_ENABLED // Comment out to disable all debug prints

  // Debug levels
  typedef enum
  {
    DEBUG_LEVEL_ERROR = 0,
    DEBUG_LEVEL_WARNING = 1,
    DEBUG_LEVEL_INFO = 2
  } DebugLevel_t;

/**
 * @brief Enables or disables all debug print statements in the project.
 *
 * When DEBUG_PRINT_ENABLED is defined, all debug print statements (DEBUG_ERROR, DEBUG_WARNING, DEBUG_INFO)
 * will be enabled and printed. When it is not defined, all debug print statements will be disabled.
 */
#ifdef DEBUG_PRINT_ENABLED
#define DEBUG_PRINT_LEVEL(level, fmt, ...)                                                   \
  do                                                                                         \
  {                                                                                          \
    TickType_t currentTime = xTaskGetTickCount();                                            \
    const char *taskName = pcTaskGetName(NULL);                                              \
    printf("[%lu][%s][%s] " fmt,                                                             \
           currentTime,                                                                      \
           (level == DEBUG_LEVEL_ERROR) ? "ERROR" : (level == DEBUG_LEVEL_WARNING) ? "WARN"  \
                                                                                   : "INFO", \
           taskName,                                                                         \
           ##__VA_ARGS__);                                                                   \
  } while (0)

/**
 * @brief Prints an error-level debug message with the current task name and timestamp.
 *
 * This macro is used to print error-level debug messages. It includes the current task name and the timestamp
 * of when the message was printed. The message is formatted using the provided format string and arguments.
 *
 * @param fmt The format string for the debug message.
 * @param ... The arguments to be formatted and printed.
 */
#define DEBUG_ERROR(fmt, ...) DEBUG_PRINT_LEVEL(DEBUG_LEVEL_ERROR, fmt, ##__VA_ARGS__)

/**
 * @brief Prints a warning-level debug message with the current task name and timestamp.
 *
 * This macro is used to print warning-level debug messages. It includes the current task name and the timestamp
 * of when the message was printed. The message is formatted using the provided format string and arguments.
 *
 * @param fmt The format string for the debug message.
 * @param ... The arguments to be formatted and printed.
 */
#define DEBUG_WARNING(fmt, ...) DEBUG_PRINT_LEVEL(DEBUG_LEVEL_WARNING, fmt, ##__VA_ARGS__)

/**
 * @brief Prints an info-level debug message with the current task name and timestamp.
 *
 * This macro is used to print info-level debug messages. It includes the current task name and the timestamp
 * of when the message was printed. The message is formatted using the provided format string and arguments.
 *
 * @param fmt The format string for the debug message.
 * @param ... The arguments to be formatted and printed.
 */
#define DEBUG_INFO(fmt, ...) DEBUG_PRINT_LEVEL(DEBUG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ERROR(fmt, ...) ((void)0)   // set to `NULL` to disable all debug prints
#define DEBUG_WARNING(fmt, ...) ((void)0) // set to `NULL` to disable all debug prints
#define DEBUG_INFO(fmt, ...) ((void)0)    // set to `NULL` to disable all debug prints

#endif // DEBUG_PRINT_ENABLED

  // event code enum that holds the event codes for the system
  typedef enum
  {
    EVENT_CODE_POLICE = 1,
    EVENT_CODE_AMBULANCE = 2,
    EVENT_CODE_FIRE = 3,
    EVENT_CODE_CORONA = 4
  } EventCode_t;

  // enum that holds the priority of the event
  typedef enum
  {
    PRIORITY_LOW = 1,
    PRIORITY_MEDIUM = 2,
    PRIORITY_HIGH = 3,
  } EventPriority_t;

  // Masasge stucture that holds the message data for events
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
    uint8_t fireCount;   // e.g 2 elements
    uint8_t coronaCount; // e.g 4 elements
    uint8_t barrowCount; // to complete latter

  } ResourceManager_t;

  extern RNG_HandleTypeDef hrng; // RNG handle for random number generation. set at main.c


#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H */