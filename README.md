# Emergency Services Dispatcher System

Real-time emergency services dispatcher system implemented on STM32F7 using FreeRTOS.

## Overview

This project implements a multi-threaded emergency response system that coordinates different emergency services (Police, Ambulance, Fire Department, and Corona Response) through a central dispatcher. Built on STM32F756ZG using FreeRTOS for real-time task management.

## Architecture

### Core Components

- **Event Management**: Generates emergency events with different priorities and types
- **Central Dispatcher**: Routes events to appropriate emergency services based on event type
- **Emergency Services**:
  - Police Department
  - Ambulance Service  
  - Fire Department
  - Corona Response Team

### Task Structure

```code
EventManagement --> Dispatcher --> Emergency Services
                                    - Police
                                    - Ambulance
                                    - Fire
                                    - Corona
```

## Hardware Requirements

- NUCLEO-F756ZG board
- ST-Link debugger
- Serial terminal for monitoring (115200 baud)

## Software Requirements

- STM32CubeIDE
- FreeRTOS
- STM32F7 HAL drivers

## Key Features

- Real-time event handling and dispatching
- Priority-based scheduling
- Multiple concurrent emergency response teams
- Queue-based communication between components
- UART-based monitoring and debugging

## Project Structure

```code
├── Core/
│   ├── Inc/                    # Header files
│   └── Src/                    # Source files
├── Drivers/                    # STM32F7 HAL drivers
├── Middlewares/               # FreeRTOS files
└── README.md
```

## Building and Running

1. Clone the repository
2. Open project in STM32CubeIDE
3. Build the project
4. Flash to NUCLEO-F756ZG board
5. Monitor via serial terminal

## Usage

The system automatically generates emergency events which are handled by appropriate services. Monitor the response via UART output.

## Configuration

Key configuration parameters in FreeRTOSConfig.h:

- Task priorities
- Stack sizes
- Queue lengths
- System tick rate

## Contributing

1. Fork the repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Create Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.
