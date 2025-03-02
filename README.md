# Emergency Services Dispatcher System

Real-time emergency services dispatcher system implemented on STM32F7 using FreeRTOS, focusing on robust error handling and FreeRTOS best practices.

## Overview

This project implements a multi-threaded emergency response system that coordinates different emergency services through a central dispatcher. Built on STM32F756ZG using FreeRTOS for real-time task management and CMake for build configuration.

## Architecture

### Core Components

- **Event Management**: Generates emergency events with different priorities and types
- **Central Dispatcher**: Routes events to appropriate emergency services based on event type
- **Emergency Services**:
  - Police Department (Multiple police car tasks)
  - Ambulance Service (Multiple ambulance car tasks)
  - Fire Department (Multiple fire truck tasks)
  - Corona Response Team (Multiple corona response tasks)
- **Print Service**: Handles all UART output through a dedicated queue

### Debug Features

#### GPIO Debug Tracking

- Event Management: PA3 (with LED1 indicator)
- Dispatcher: PC0 (with LED2 indicator)
- Police Events: PC3 (with LED3 indicator)
- Ambulance Events: PF3
- Fire Events: PF5
- Corona Events: PF10

Enable/Disable via `DEBUG_GPIO_TRACKING` in main.h

#### Debug Print System

- Thread-safe printf functionality through print queue
- Enable/Disable via `DEBUG_PRINT_ENABLED` in common.h
- Uses `DEBUG_PRINT()` macro for all debug messages
- Zero overhead when disabled

### Source Files Structure

#### Core/Inc/

- `ambulance.h`: Ambulance service declarations and configurations
- `common.h`: Shared definitions, constants, and debug configurations
- `corona.h`: Corona response team interface
- `dispatcher.h`: Central event dispatcher declarations
- `event_management.h`: Event generation system interface
- `fire.h`: Fire department service declarations
- `police.h`: Police service interface
- `print.h`: UART print service declarations

#### Core/Src/

- `ambulance.c`: Ambulance task and queue management
- `corona.c`: Corona response task implementation
- `dispatcher.c`: Event routing and dispatch logic
- `event_management.c`: Event generation implementation
- `fire.c`: Fire department task handling
- `police.c`: Police service implementation
- `print.c`: Thread-safe print service
- `main.c`: System initialization and task creation

## Hardware Requirements

- NUCLEO-F756ZG board
- ST-Link debugger
- Serial terminal (115200 baud)

## Software Requirements

- Visual Studio Code
- STM32 VSCode Extension
- CMake
- Ninja build system
- ARM GCC toolchain

## Building and Running

1. Clone the repository:

```bash
git clone https://github.com/elkanamol/f756_rtos_dispacher_RT.git
```

1. Open in VSCode:

- Open VSCode
- Install STM32 VSCode Extension
- File -> Open Folder -> Select project folder
- Select "Import CMake Project" when prompted
- Select kit: "GCC ARM"

1. Build:

- Click "Build" button in VSCode status bar
- Or use CMake: Build command

1. Flash:

- Connect NUCLEO-F756ZG
- Click "Run" in VSCode
- Monitor via serial terminal at 115200 baud

## Key Features

- FreeRTOS task management with proper error handling
- Queue-based inter-task communication
- Priority-based scheduling
- Thread-safe printing mechanism
- Robust task creation with configASSERT checks
- CMake-based build system

## Configurations

Key configuration files:

- `FreeRTOSConfig.h`: RTOS settings
- `common.h`: System-wide constants
- `CMakeLists.txt`: Build configuration

## Contributing

1. Fork the repository
2. Create feature branch
3. Follow FreeRTOS coding standards
4. Use provided error handling patterns
5. Submit Pull Request

## Debug Configuration

### GPIO Debug Tracking

1. In main.h, ensure `DEBUG_GPIO_TRACKING` is defined
2. Connect logic analyzer to specified pins
3. Monitor pin state changes for event flow
4. Measure timing between events

### Print Debug System

1. In common.h, ensure `DEBUG_PRINT_ENABLED` is defined
2. Use `DEBUG_PRINT()` for debug messages
3. Monitor via serial terminal at 115200 baud
4. Disable by commenting out `DEBUG_PRINT_ENABLED`

## License

MIT License - See LICENSE file
