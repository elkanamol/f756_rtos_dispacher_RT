// police.c
#include "police.h"
#include "common.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <stdio.h>

QueueHandle_t xPoliceQueue = NULL;

// static uint8_t ucPoliceCarAvilable = 3;
// static SemaphoreHandle_t xPoliceResourceMutex;


/**
 * @brief Task function for a police car that handles events received from the police queue.
 *
 * This task function is responsible for processing events received from the `xPoliceQueue`. When an event is received, the task will print a message indicating which police car received the event, then wait for a random amount of time to simulate the police car handling the event, and finally print a message indicating that the police car is done.
 *
 * @param pvParameters The ID of the police car, passed as a `void *` and cast to `uint8_t`.
 */
static void vPoliceCarTask(void *pvParameters)
{

    uint8_t carID = (uint8_t)(uintptr_t)pvParameters;
    EventMassage_t recievedEvent;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    TickType_t handlingTime = 100;
    for (;;)
    {
        if (xQueueReceive(xPoliceQueue, &recievedEvent, portMAX_DELAY) == pdTRUE)
        {
            printf("Police car %d received event %d\n"
                 ,carID
                 , recievedEvent.eventCode);
            handlingTime = ((HAL_RNG_GetRandomNumber(&hrng) % DELADY_RANDOM_LIMIT) + 1) * TIME_FOR_DELAY;
            vTaskDelayUntil(&xLastWakeTime, handlingTime);
            printf("Police Car %d done in %lu Ticks\n", carID, (unsigned long)handlingTime);
        }
        vTaskDelay(1);
    }

}

/**
 * @brief Starts the police task and creates the police car tasks.
 *
 * This function creates the police queue and then creates a number of police car tasks equal to NUM_POLICE_CARS. Each police car task is given a unique name and is started with the specified priority.
 *
 * @param uxPriority The priority at which the police car tasks should be executed.
 */
void vStartPoliceTask(UBaseType_t uxPriority)
{
    xPoliceQueue = xQueueCreate(POLICE_QUEUE_SIZE, sizeof(EventMassage_t));
    if (xPoliceQueue == NULL)
    {
        printf("Error creating police queue\n");
    }

    for (uint8_t i = 0; i < NUM_POLICE_CARS; i++)
    {
        char taskName[16];
        snprintf(taskName, sizeof(taskName), "PoliceCar%d", i);

        BaseType_t xTaskRetVal = xTaskCreate(vPoliceCarTask, taskName, DEPART_TASK_STACK_SIZE, (void *)(uintptr_t)i, uxPriority, NULL);
        if (xTaskRetVal != pdPASS)
        {
            printf("Error creating task %s\n", taskName);
        }
    }
}
