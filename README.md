# Emergency Services Dispatcher System

## About

A real-time emergency services dispatcher system implemented on STM32F756ZG using FreeRTOS. The system simulates emergency response coordination with multiple services (Police, Ambulance, Fire, Corona) handling events based on priorities. It demonstrates robust task management, inter-task communication, and hardware-specific features like RNG for realistic event timing.

![ScreenRecording2025-03-02113321-ezgif com-optimize](https://github.com/user-attachments/assets/df630574-1ffd-4aa5-ba58-a85d36387ce1)

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

## Key Features

- FreeRTOS task management with comprehensive error handling
- Hardware RNG-based random timing for realistic event simulation
- Multi-level debug system with GPIO tracking
- Memory management monitoring and overflow protection
- Queue-based inter-task communication
- Priority-based scheduling
- Thread-safe printing mechanism

## System Architecture

![Dispacher_diagram_2](https://github.com/user-attachments/assets/d9148a29-4992-4ed5-af31-a311da39eb7d)


![nucleo_f746zg_zio_left_2022_10_19_V6L6hlp](https://github.com/user-attachments/assets/eac6f072-31c2-4fd9-a0fb-a08c030781f6)

### Core Components

- **Event Management**: Generates emergency events with different priorities and types
- **Central Dispatcher**: Routes events to appropriate emergency services based on event type
- **Emergency Services**:
  - Police Department (Multiple police car tasks)
  - Ambulance Service (Multiple ambulance car tasks)
  - Fire Department (Multiple fire truck tasks)
  - Corona Response Team (Multiple corona response tasks)
- **Print Service**: Handles all UART output through a dedicated queue

### Random Number Generation

The system uses STM32F7's hardware RNG module to generate random delays between events, making the simulation more realistic:

```c
const TickType_t xDelay = ((HAL_RNG_GetRandomNumber(&hrng) % DELADY_RANDOM_LIMIT) + 1) * portTICK_RATE_MS * TIME_FOR_DELAY;
```

## Debug Features

### Memory Management

- Stack overflow detection enabled via `configCHECK_FOR_STACK_OVERFLOW`
- Memory allocation failure handling
- Runtime stack usage monitoring
- Located in:
  - Implementation: `main.c` (lines 443-491)
  - Configuration: `FreeRTOSConfig.h` (lines 155-156)

### Multi-Level Debug System

Debug output format: `[TickCount][TaskName][Level] Message`

Example outputs:

```bash
[1234][DispatchTask][ERROR] Stack overflow detected
[5678][EventTask][WARNING] Queue nearly full: 80% capacity
[9012][PrintTask][INFO] Processing event type: EMERGENCY_HIGH
```

Configuration in `common.h`:

```c
#define DEBUG_PRINT_ENABLED
#define DEBUG_GPIO_TRACKING
```

- Three severity levels: ERROR, WARNING, INFO
- Automatic timestamps and task names
- Enable/Disable via `DEBUG_PRINT_ENABLED` in common.h
- Zero overhead when disabled

### GPIO Debug Tracking

- Event Management: PA3 (with LED1 indicator)
- Dispatcher: PC0 (with LED2 indicator)
- Police Events: PC3 (with LED3 indicator)
- Ambulance Events: PF3
- Fire Events: PF5
- Corona Events: PF10

Enable/Disable via `DEBUG_GPIO_TRACKING` in main.h

## Hardware Requirements

- NUCLEO-F756ZG board
- ST-Link debugger
- Serial terminal (115200 baud)
- Logic Analyzer at least 8 I/O ports (Optional)

## Setup Instructions

### Prerequisites

- Visual Studio Code
- ARM GCC toolchain
- CMake
- Ninja build system

## Building and Running

1. Clone the repository:

```bash
git clone https://github.com/elkanamol/f756_rtos_dispacher_RT.git
```

1. Open in VSCode:

- Open VSCode
- Open STM32 VSCode Extension (If isn't insalled yet, follow "Installing STM32 VS Code Extension" instructions)
- Select "Import CMake Project" when prompted
- File -> Open Folder -> Select project folder
- Select kit: "GCC ARM"

1. Build:

- Click "Build" button in VSCode status bar
- Or use CMake: Build command

1. Flash:

- Connect NUCLEO-F756ZG
- Click "Run" in VSCode
- Monitor via serial terminal at 115200 baud

### Installing STM32 VS Code Extension

1. Visit [STM32 VS Code Extension](https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension)
2. Install the extension following marketplace instructions

### Project Import Process

1. Use STM32 VS Code Extension's "Import CMake Project" feature
2. The extension will:
   - Check for required JSON files
   - Generate configuration if needed
   - Present project summary
3. Choose project opening method:
   - Add to current window
   - Open in new VS Code session
   - Add to existing workspace

## Contributing

1. Fork the repository
2. Create feature branch
3. Follow FreeRTOS coding standards
4. Use provided error handling patterns
5. Submit Pull Request

## License

MIT License - See LICENSE file
