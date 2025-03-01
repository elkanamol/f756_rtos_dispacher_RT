#include "common.h"
#include "event_managment.h"
#include "dispatcher.h"
#include <stdio.h>
#include "main.h"


/**
 * @brief external dispacher queue handler
 * 
 */
extern QueueHandle_t xDispacherQueue;


/**
 * @brief The event management task responsible for creating events and sending them to the dispatcher task.
 * 
 * This task generates random events with varying priority and sends them to the dispatcher queue. It uses the
 * HAL_RNG_GetRandomNumber() function to generate random event codes and priorities. The events are then sent to
 * the dispatcher queue, with high priority events being sent to the front of the queue and low priority events
 * being sent to the back. The task also toggles an LED (LD1_Pin) to indicate its activity.
 * 
 * @param pvParameters Unused parameter, should be set to NULL when calling vStartEventManagementTask().
 */
void vEventManagementTask(void *pvParameters)
{
    printf("Event Management Task Started\n");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        BaseType_t xStasus = pdFALSE;
        HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
        // starting with random delay time of 1-5 seconds
        const TickType_t xDelay = ((HAL_RNG_GetRandomNumber(&hrng) % DELADY_RANDOM_LIMIT) + 1) * portTICK_RATE_MS * TIME_FOR_DELAY;
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        // creating the event as random.
        EventMassage_t event;
        event.eventCode = (EventCode_t)(HAL_RNG_GetRandomNumber(&hrng) % CAR_RANDOM_LIMIT + 1); // to get 1..4
#ifdef EVENT_SET_PRIORITY
        event.eventPriority = (EventPriority_t)(HAL_RNG_GetRandomNumber(&hrng) % PRIORITY_HIGH + 1); // to get 1..3
#else
        event.eventPriority = PRIORITY_LOW;
        #endif
        event.eventTime = xTaskGetTickCount();

        if (xDispacherQueue != NULL)
        {
            if (event.eventPriority == PRIORITY_HIGH)
            {
                xStasus = xQueueSendToFront(xDispacherQueue, &event, portMAX_DELAY);
            }
            else
            {
                xStasus = xQueueSendToBack(xDispacherQueue, &event, portMAX_DELAY);
            }
            if (xStasus == pdTRUE)
            {
                printf("Event sent to dispacher queue: %d, %d, %ld\n", event.eventCode, event.eventPriority, event.eventTime);
            }
            else
            {
                printf("Error: Failed to send event to dispacher queue\n");
            }
        }
        vTaskDelay(xDelay);
    }
}

/**
 * @brief Starts the Event Management Task.
 *
 * This function creates the Event Management Task with the specified priority.
 * If the task creation fails, an error message is printed.
 *
 * @param uxPriority The priority at which the Event Management Task should run.
 * @return pdPASS if the task was created successfully, pdFAIL otherwise.
 */
BaseType_t xStartEventManagementTask(UBaseType_t uxPriority)
{
    if (uxPriority > configMAX_PRIORITIES - 1)
    {
        return pdFAIL;
    }
    BaseType_t xReturn = pdPASS;

    BaseType_t xTaskRetVal = xTaskCreate(vEventManagementTask,
                                         "EventMnmntTask",
                                         DEPART_TASK_STACK_SIZE,
                                         NULL,
                                         uxPriority,
                                         NULL);
    if (xTaskRetVal != pdPASS)
    {
        printf("Error creating task EventManagementTask\n");
        xReturn = pdFAIL;
    }

    return xReturn;
}