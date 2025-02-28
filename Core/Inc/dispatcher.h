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

#define DISPACHER_QUEUE_SIZE 10

extern QueueHandle_t xDispatcherQueue;

/**
 * @brief Starts the dispatcher task, which is responsible for receiving events from the dispatcher queue, processing them, and forwarding them to the appropriate queues.
 *
 * This function creates the dispatcher queue, and then creates the dispatcher task with the specified priority.
 *
 * @param uxPriority The priority at which the dispatcher task should run.
 */
void vStartDispacherTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif

#endif // DISPATCHER_H