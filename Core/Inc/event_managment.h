// event_management.h
#ifndef EVENT_MANAGEMENT_H
#define EVENT_MANAGEMENT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "main.h"
#include "stm32f7xx_hal.h"
#include <stm32f7xx_hal_rng.h>

    /**
     * @brief Starts the Event Management Task.
     *
     * This function creates the Event Management Task with the specified priority.
     * If the task creation fails, an error message is printed.
     *
     * @param uxPriority The priority at which the Event Management Task should run.
     * @return pdPASS if the task was created successfully, pdFAIL otherwise.
     */
    BaseType_t xStartEventManagementTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif

#endif // EVENT_MANAGEMENT_H