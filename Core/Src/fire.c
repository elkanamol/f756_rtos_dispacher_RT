/* fire_fighter.c */

#include "fire.h"
#include <stdio.h>

QueueHandle_t xFireFighterQueue = NULL;


/**
 * @brief Task function for a fire fighter car.
 * 
 * This task function is responsible for handling fire events received from the fire fighter queue.
 * It receives an event, simulates handling the event by delaying for a random amount of time,
 * and then prints a message indicating that the event has been handled.
 * 
 * @param pvParameters The ID of the fire fighter car, passed as a void pointer.
 */
void vFireCarTask(void *pvParameters)
{
    uint8_t carID = (uint8_t)(uintptr_t)pvParameters;
    EventMassage_t recievedEvent;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        if (xQueueReceive(xFireFighterQueue, &recievedEvent, portMAX_DELAY) == pdTRUE)
        {
            DEBUG_INFO("Fire fighter car %d received event %d\n", carID, recievedEvent.eventCode);
            TickType_t handlingTime = ((HAL_RNG_GetRandomNumber(&hrng) % DELADY_RANDOM_LIMIT) + 1) * TIME_FOR_DELAY;
            vTaskDelayUntil(&xLastWakeTime, handlingTime);
            DEBUG_INFO("FireFighter Car %d done in %lu Ticks\n", carID, (unsigned long)handlingTime);
        }
        vTaskDelay(1);
    }
}

/**
 * @brief Starts the fire fighter task.
 *
 * This function creates a queue for fire events and spawns a number of fire fighter car tasks.
 * Each fire fighter car task receives fire events from the queue, simulates handling the event,
 * and prints a message indicating that the event has been handled.
 *
 * @param uxPriority The priority at which the fire fighter car tasks should run.
 * @return BaseType_t pdPASS if all tasks were created successfully, pdFAIL otherwise.
 */
BaseType_t xStartFireFighterTask(UBaseType_t uxPriority)
{
    BaseType_t xReturn = pdPASS;
    if (uxPriority > configMAX_PRIORITIES - 1)
    {
        return pdFAIL;
    }
    xFireFighterQueue = xQueueCreate(FIREFIGHTER_QUEUE_LENGTH, sizeof(EventMassage_t));
    if(xFireFighterQueue == NULL)
    {
        DEBUG_ERROR("Error creating fire fighter queue\n");
        return pdFAIL;
    }

    for (uint8_t i = 0; i < NUM_FIRE_TRUCKS; i++)
    {
        char taskName[16];
        sprintf(taskName, "FireCar%d", i);

        BaseType_t xTaskRetVal = xTaskCreate(vFireCarTask,
                                             taskName,
                                             DEPART_TASK_STACK_SIZE,
                                             (void *)(uintptr_t)i,
                                             uxPriority,
                                             NULL);
        if (xTaskRetVal != pdPASS)
        {
            DEBUG_ERROR("Error creating task %s\n", taskName);
            xReturn = pdFAIL;
            break;
        }
    }
    if (xReturn == pdFAIL)
    {
        vQueueDelete(xFireFighterQueue);
        xFireFighterQueue = NULL;
    }

    return xReturn;
}