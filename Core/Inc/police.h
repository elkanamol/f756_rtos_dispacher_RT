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

#define POLICE_QUEUE_SIZE 10 // Define the queue size and number of police cars
#define NUM_POLICE_CARS 3    // Define the number of police cars

    extern QueueHandle_t xPoliceQueue;

    /**
     * @brief Starts the police task and creates the police queue.
     *
     * This function creates the police queue and spawns the police car tasks. It returns the result of the task creation, which can be either `pdPASS` or `pdFAIL`.
     *
     * @param uxPriority The priority at which the police car tasks should run.
     * @return `pdPASS` if the police tasks were created successfully, `pdFAIL` otherwise.
     */
    BaseType_t xStartPoliceTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif

#endif // POLICE_H