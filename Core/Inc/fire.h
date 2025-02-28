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

#define FIREFIGHTER_QUEUE_LENGTH 10
#define NUM_FIRE_TRUCKS 2

extern QueueHandle_t xFireFighterQueue; // Declare the queue for fire events in common.h

/**
 * @brief Starts the fire fighter task.
 *
 * This function creates a queue for fire events and spawns a number of fire fighter car tasks.
 * Each fire fighter car task receives fire events from the queue, simulates handling the event,
 * and prints a message indicating that the event has been handled.
 *
 * @param uxPriority The priority at which the fire fighter car tasks should run.
 */
void vStartFireFighterTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif
#endif // FIRE_H