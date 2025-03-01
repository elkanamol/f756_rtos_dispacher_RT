// dispatcher.h
#ifndef DISPATCHER_H
#define DISPATCHER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "FreeRTOS.h"
#include "queue.h"

#define DISPACHER_QUEUE_SIZE 10          // Size of the dispatcher queue

extern QueueHandle_t xDispatcherQueue;   // Dispatcher queue handle. set at dispatcher.c

/**
 * @brief Starts the dispatcher task.
 *
 * This function creates the dispatcher queue and the dispatcher task. The dispatcher task is responsible for receiving events from the dispatcher queue, processing them, and forwarding them to the appropriate queues (police, ambulance, fire, or corona).
 *
 * @param uxPriority The priority at which the dispatcher task should run.
 * @return `pdPASS` if the task was created successfully, `pdFAIL` otherwise.
 */
BaseType_t xStartDispacherTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif

#endif // DISPATCHER_H