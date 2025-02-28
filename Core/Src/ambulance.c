/* ambulance.c */

#include "ambulance.h"
#include <stdio.h> // for snprintf if needed

QueueHandle_t xAmbulanceQueue = NULL;


/**
 * @brief Task function for an individual ambulance car.
 * This task is responsible for receiving events from the ambulance queue,
 * simulating the handling of the event by delaying for a random amount of time,
 * and printing status messages.
 *
 * @param pvParameters The ID of the ambulance car, passed as a void pointer.
 */
static void vAmbulanceCarTask(void *pvParameters)
{
    uint8_t carID = (uint8_t)(uintptr_t)pvParameters;
    EventMassage_t recievedEvent;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // TickType_t handlingTime = 100;

    for (;;)
    {
        if (xQueueReceive(xAmbulanceQueue, &recievedEvent, portMAX_DELAY) == pdTRUE)
        {
            printf("Ambulance car %d received event %d\n"
                , carID
                , recievedEvent.eventCode);

            TickType_t handlingTime = ((HAL_RNG_GetRandomNumber(&hrng) % DELADY_RANDOM_LIMIT) + 1) * TIME_FOR_DELAY;
            vTaskDelayUntil(&xLastWakeTime, handlingTime);

            printf("Ambulance Car %d done in %lu Ticks\n", carID, (unsigned long)handlingTime);

        }
        vTaskDelay(1);
    }
}

/**
 * @brief Starts the ambulance task by creating the ambulance queue and spawning the individual ambulance car tasks.
 *
 * This function is responsible for setting up the necessary infrastructure for the ambulance system.
 * It creates the ambulance queue, which is used to receive events that need to be handled by the ambulance cars.
 * It then spawns the individual ambulance car tasks, each of which will receive events from the queue and simulate the handling of those events.
 *
 * @param uxPriority The priority at which the ambulance car tasks should be executed.
 */
void vStartAmbulanceTask(UBaseType_t uxPriority)
{
    xAmbulanceQueue = xQueueCreate(AMBULANCE_QUEUE_LENGTH, sizeof(EventMassage_t));
    if (xAmbulanceQueue == NULL)
    {
        printf("The xAmbulanceQueue cannot create");
        // return;
    }
        for (uint8_t i = 0; i < NUM_AMBULANCE_CARS; i++)
        {

            char taskName[16];
            sprintf(taskName, "AmbulCar%d", i);

            BaseType_t xTaskRetVal = xTaskCreate(vAmbulanceCarTask, taskName, DEPART_TASK_STACK_SIZE, (void *)(uintptr_t)i, uxPriority, NULL);
            if (xTaskRetVal != pdPASS)
            {
                printf("Error creating task %s\n", taskName);
            }
        }


}