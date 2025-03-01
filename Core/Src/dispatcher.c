#include "dispatcher.h"
#include "police.h"
#include "ambulance.h"
#include "fire.h"
#include "corona.h"
#include "common.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"



QueueHandle_t xDispacherQueue = NULL;

extern QueueHandle_t xPoliceQueue;
extern QueueHandle_t xAmbulanceQueue;
extern QueueHandle_t xFireFighterQueue;
extern QueueHandle_t xCoronaQueue;

/**
 * @brief The dispatcher task that receives events from the dispatcher queue and forwards them to the appropriate queues.
 *
 * This task is responsible for receiving events from the dispatcher queue, processing them, and forwarding them to the appropriate queues (police, ambulance, fire, or corona). It also toggles an LED to indicate that the task is running.
 *
 * @param pvParameters Unused parameter required by the FreeRTOS task API.
 */
void vDispacherTask(void *pvParameters)
{
    printf("Dispatcher Task Started\n");
    EventMassage_t recievedEvent;

    for(;;)
    {
        if (xQueueReceive(xDispacherQueue, &recievedEvent, portMAX_DELAY) == pdTRUE)
        {
            HAL_GPIO_TogglePin(GPIOB, LD2_Pin);

            printf("Event recieved from dispacher queue: %d, %d, %ld\n"
                , recievedEvent.eventCode
                , recievedEvent.eventPriority
                , recievedEvent.eventTime);
            
            switch (recievedEvent.eventCode)
            {
                case EVENT_CODE_POLICE:
                    xQueueSend(xPoliceQueue, &recievedEvent, portMAX_DELAY);
                    printf("Dispatcher: sent event to police queue\n");
                    break;
                case EVENT_CODE_AMBULANCE:
                    xQueueSendToBack(xAmbulanceQueue, &recievedEvent, portMAX_DELAY);
                    printf("Dispatcher: sent event to ambulance queue\n");
                    break;
                case EVENT_CODE_FIRE:
                    xQueueSend(xFireFighterQueue, &recievedEvent, portMAX_DELAY);
                    printf("Dispatcher: sent event to fire fighter queue\n");
                    break;
                case EVENT_CODE_CORONA:
                    xQueueSend(xCoronaQueue, &recievedEvent, portMAX_DELAY);
                    printf("Dispatcher: sent event to corona queue\n");
                    break;
                default:
                    printf("Error: Invalid event code\n");
                    break;
            }

        }
        vTaskDelay(1);
    }
}

/**
 * @brief Starts the dispatcher task.
 *
 * This function creates the dispatcher queue and the dispatcher task. The dispatcher task is responsible for receiving events from the dispatcher queue, processing them, and forwarding them to the appropriate queues (police, ambulance, fire, or corona).
 *
 * @param uxPriority The priority at which the dispatcher task should run.
 * @return `pdPASS` if the task was created successfully, `pdFAIL` otherwise.
 */
BaseType_t xStartDispacherTask(UBaseType_t uxPriority)
{
    BaseType_t xReturn = pdPASS;

    xDispacherQueue = xQueueCreate(DISPACHER_QUEUE_SIZE, sizeof(EventMassage_t));
    if (xDispacherQueue == NULL)
    {
        printf("Error: Failed to create dispacher queue\n");
        return pdFAIL;
    }

    BaseType_t xTaskRetVal = xTaskCreate(vDispacherTask,
                                         "DispacherTask",
                                         DEPART_TASK_STACK_SIZE,
                                         NULL,
                                         uxPriority,
                                         NULL);
    if (xTaskRetVal != pdPASS)
    {
        printf("Error creating task DispacherTask\n");
        xReturn = pdFAIL;
    }

    return xReturn;
}