/* corona.c */

#include "common.h"
#include "corona.h"
#include <stdio.h>


QueueHandle_t xCoronaQueue = NULL;

/**
 * @brief Task function for a single Corona car.
 *
 * This task function is responsible for handling events received from the Corona queue.
 * It receives the car ID as a parameter, and then waits for events to be received from the queue.
 * When an event is received, it prints a message and then delays for a random amount of time to simulate
 * the car handling the event. Finally, it prints a message indicating that the car has finished handling the event.
 *
 * @param pvParameters The car ID, passed as a void pointer.
 */
static void vCoronaCarTask(void *pvParameters)
{
    uint8_t carID = (uint8_t)(uintptr_t)pvParameters;
    EventMassage_t recievedEvent;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        if (xQueueReceive(xCoronaQueue, &recievedEvent, portMAX_DELAY) == pdTRUE)
        {
            DEBUG_PRINT("Corona car %d received event %d\n", carID, recievedEvent.eventCode);
            TickType_t handlingTime = ((HAL_RNG_GetRandomNumber(&hrng) % DELADY_RANDOM_LIMIT) + 1) * TIME_FOR_DELAY;
            vTaskDelayUntil(&xLastWakeTime, handlingTime);
            DEBUG_PRINT("Corona Car %d done in %lu Ticks\n", carID, (unsigned long)handlingTime);
        }
        vTaskDelay(1);
    }
}

/**
 * @brief Starts the Corona task and creates the Corona queue.
 *
 * This function creates the Corona queue and then creates a number of Corona car tasks equal to NUM_CORONA_RESOURCES.
 * Each Corona car task is responsible for handling events received from the Corona queue.
 *
 * @param uxPriority The priority at which the Corona car tasks should run.
 * @return BaseType_t pdPASS if all tasks were created successfully, pdFAIL otherwise.
 */
BaseType_t xStartCoronaTask(UBaseType_t uxPriority)
{
    if (uxPriority > configMAX_PRIORITIES - 1)
    {
        return pdFAIL;
    }
    BaseType_t xReturn = pdPASS;

    xCoronaQueue = xQueueCreate(CORONA_QUEUE_LENGTH, sizeof(EventMassage_t));
    if (xCoronaQueue == NULL)
    {
        DEBUG_PRINT("Error creating corona queue\n");
        return pdFAIL;
    }

    for (int i = 0; i < NUM_CORONA_RESOURCES; i++)
    {
        char taskName[16];
        snprintf(taskName, sizeof(taskName), "Corona%d", i);

        BaseType_t xTaskRetVal = xTaskCreate(vCoronaCarTask,
                                           taskName,
                                           DEPART_TASK_STACK_SIZE,
                                           (void *)(uintptr_t)i,
                                           uxPriority,
                                           NULL);
        if (xTaskRetVal != pdPASS)
        {
            DEBUG_PRINT("Error creating task %s\n", taskName);
            xReturn = pdFAIL;
            break;
        }
    }

    if (xReturn == pdFAIL)
    {
        vQueueDelete(xCoronaQueue);
        xCoronaQueue = NULL;
    }
    return xReturn;
}