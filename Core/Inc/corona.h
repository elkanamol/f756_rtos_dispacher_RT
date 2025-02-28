/* corona.h */

#ifndef CORONA_H
#define CORONA_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "queue.h"
#include "task.h"
#include "FreeRTOS.h"
#include "semphr.h"

#define CORONA_QUEUE_LENGTH 10
#define NUM_CORONA_RESOURCES 4

extern QueueHandle_t xCoronaQueue;

/**
 * @brief Starts the Corona task and creates the Corona queue.
 *
 * This function creates the Corona queue and then creates a number of Corona car tasks equal to NUM_CORONA_RESOURCES.
 * Each Corona car task is responsible for handling events received from the Corona queue.
 *
 * @param uxPriority The priority at which the Corona car tasks should run.
 */
void vStartCoronaTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif
#endif // CORONA_H