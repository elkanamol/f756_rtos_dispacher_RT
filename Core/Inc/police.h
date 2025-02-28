// police.h
#ifndef POLICE_H
#define POLICE_H

#ifdef __cplusplus
extern "C" 
{
#endif

#include "common.h"
#include "queue.h"
#include "task.h"
#include "FreeRTOS.h"
#include "semphr.h"

// Define the queue size and number of police cars
#define POLICE_QUEUE_SIZE 10
// Define the number of police cars
#define NUM_POLICE_CARS 3

/**
 * @brief the queue to receive events from the event queue, declated in common.h
 * 
 */
extern QueueHandle_t xPoliceQueue;

/**
 * @brief Starts the police task and creates the police car tasks.
 *
 * This function creates the police queue and then creates a number of police car tasks equal to NUM_POLICE_CARS. Each police car task is given a unique name and is started with the specified priority.
 *
 * @param uxPriority The priority at which the police car tasks should be executed.
 */
void vStartPoliceTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif

#endif // POLICE_H