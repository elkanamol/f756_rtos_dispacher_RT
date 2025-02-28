  #ifndef __PRINT_H
  #define __PRINT_H

  #ifdef __cplusplus
  extern "C" {
  #endif

#include "FreeRTOS.h"
#include "queue.h"

#define PRINT_QUEUE_SIZE 64
#define MAX_PRINT_MSG_LEN 128

typedef struct
{
  char buffer[MAX_PRINT_MSG_LEN];
  uint16_t len;
} PrintMessage_t;

extern QueueHandle_t xPrintQueue;
extern TaskHandle_t xPrintTaskHandle;

/**
 * @brief Initializes the print functionality with thread-safe mutex
 * @note Must be called before using printf/scanf functions
 */
void print_init(UBaseType_t uxPriority);

/**
 * @brief Deinitializes the print functionality and frees the mutex
 */
void print_deinit(void);

/**
 * @brief Prints an error message and enters an infinite loop
 * @param msg The error message to print
 */
void print_error(const char *msg);

/**
 * @brief Low-level character output function (weak)
 * @param ch Character to output
 * @return The character that was output
 * @note This function is called by printf internally
 * @note Can be overridden by user implementation
 */
int __io_putchar(int ch);

/**
 * @brief Low-level write function for stdout (weak)
 * @param file File descriptor (unused)
 * @param ptr Pointer to data buffer
 * @param len Length of data to write
 * @return Number of bytes written
 * @note This function is called by printf internally
 * @note Can be overridden by user implementation
 */
int _write(int file, char *ptr, int len);

/**
 * @brief Low-level read function for stdin (weak)
 * @param file File descriptor (unused)
 * @param ptr Pointer to data buffer
 * @param len Maximum length to read
 * @return Number of bytes read
 * @note This function is called by scanf internally
 * @note Can be overridden by user implementation
 */
int _read(int file, char *ptr, int len);

#ifdef __cplusplus
}
#endif

#endif /* __PRINT_H */
