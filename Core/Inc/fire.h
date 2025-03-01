/* fire.h */

#ifndef FIRE_H
#define FIRE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "FreeRTOS.h"
#include "queue.h"

#define FIREFIGHTER_QUEUE_LENGTH 10 // Length of the fire fighter queue
#define NUM_FIRE_TRUCKS 2           // Number of fire trucks

    extern QueueHandle_t xFireFighterQueue; // Declare the queue for fire events in common.h

    /**
     * @brief Starts the fire fighter task.
     *
     * This function creates a queue for fire events and spawns a number of fire fighter car tasks.
     * Each fire fighter car task receives fire events from the queue, simulates handling the event,
     * and prints a message indicating that the event has been handled.
     *
     * @param uxPriority The priority at which the fire fighter car tasks should run.
     * @return BaseType_t `pdPASS` if all tasks were created successfully, `pdFAIL` otherwise.
     */
    BaseType_t xStartFireFighterTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif
#endif // FIRE_H