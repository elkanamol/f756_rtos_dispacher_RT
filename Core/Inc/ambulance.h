/* ambulance.h */

#ifndef AMBULANCE_H
#define AMBULANCE_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "FreeRTOS.h"
#include "queue.h"

#define AMBULANCE_QUEUE_LENGTH 10 // Length of the ambulance queue
#define NUM_AMBULANCE_CARS 4      // Number of parallel ambulance cars

    extern QueueHandle_t xAmbulanceQueue; // Ambulance queue handle. set at ambulance.c

    /**
     * @brief Starts the ambulance task by creating the ambulance queue and spawning the individual ambulance car tasks.
     *
     * This function is responsible for setting up the necessary infrastructure for the ambulance system.
     * It creates the ambulance queue, which is used to receive events that need to be handled by the ambulance cars.
     * It then spawns the individual ambulance car tasks, each of which will receive events from the queue and simulate the handling of those events.
     *
     * @param uxPriority The priority at which the ambulance car tasks should be executed.
     * @return BaseType_t `pdPASS` if all tasks were created successfully, `pdFAIL` otherwise.
     */
    BaseType_t xStartAmbulanceTask(UBaseType_t uxPriority);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // AMBULANCE_H