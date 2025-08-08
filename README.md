# Simulador de Planificación de Procesos

## Descripción

Este proyecto implementa un simulador de planificación de procesos que emula el comportamiento de un sistema operativo básico. El simulador utiliza el algoritmo **Round Robin** para gestionar múltiples procesos y simula la ejecución de instrucciones de máquina en un entorno controlado.

## Arquitectura del Sistema

### Componentes Principales

- **CPU**: Simula la unidad central de procesamiento que ejecuta las instrucciones
- **Proceso**: Representa un proceso con registros (AX, BX, CX), contador de programa (PC) y quantum
- **Sistema**: Coordina la planificación y ejecución de procesos

### Estructura de Archivos

```
Sistemas-operativos/
├── CPU.h/CPU.cpp          # Simulación de la CPU
├── Proceso.h/Proceso.cpp  # Clase Proceso con registros y instrucciones
├── Sistema.cpp            # Lógica principal del simulador
├── makefile              # Configuración de compilación
├── procesos/             # Archivos de procesos
│   ├── procesos.txt      # Lista de procesos a cargar
│   ├── 1.txt            # Instrucciones del proceso 1
│   ├── 2.txt            # Instrucciones del proceso 2
│   └── 3.txt            # Instrucciones del proceso 3
└── RAM/                  # Almacenamiento de contexto (archivos binarios)
    ├── data1.bin
    ├── data2.bin
    └── data3.bin
```

## Funcionamiento

### Algoritmo Round Robin

El simulador implementa el algoritmo Round Robin con las siguientes características:

1. **Cola de Procesos**: Los procesos se ejecutan en orden FIFO
2. **Quantum**: Cada proceso tiene un tiempo de ejecución asignado
3. **Reentrada**: Los procesos que no terminan vuelven al final de la cola

### Instrucciones Soportadas

El simulador reconoce las siguientes instrucciones de máquina:

- `ADD AX, BX` - Suma el valor de BX a AX
- `ADD AX, 5` - Suma el valor 5 a AX
- `SUB AX, BX` - Resta el valor de BX a AX
- `SUB AX, 3` - Resta el valor 3 a AX
- `INC AX` - Incrementa AX en 1
- `MUL AX, BX` - Multiplica AX por BX
- `MUL AX, 2` - Multiplica AX por 2
- `JMP 3` - Salta a la instrucción en la posición 3
- `NOP` - No hace nada (instrucción vacía)

### Formato de Archivos

#### Archivo procesos.txt
Contiene la lista de procesos a cargar con el siguiente formato:
```
PID:1,AX=10,BX=5,Quantum=1
PID:2,AX=12,BX=3,CX=3,Quantum=1
PID:3, AX=2, BX=3, CX=12,Quantum=1
```

#### Archivos de Instrucciones (1.txt, 2.txt, 3.txt)
Cada archivo contiene las instrucciones a ejecutar para un proceso específico:
```
ADD AX, 234
INC BX
SUB AX, BX
NOP
MUL BX, AX
```

## Compilación y Ejecución

### Requisitos

- Compilador C++ (g++)
- Sistema operativo compatible con C++

### Compilación

```bash
make
```

O manualmente:

```bash
g++ -Wall -c Sistema.cpp Proceso.cpp CPU.cpp
g++ Sistema.o Proceso.o CPU.o -o simulador
```

### Ejecución

1. **Compilar el proyecto**:
   ```bash
   make
   ```

2. **Ejecutar el simulador**:
   ```bash
   ./simulador
   ```

3. **El programa automáticamente**:
   - Lee el archivo `procesos/procesos.txt` para cargar los procesos
   - Carga las instrucciones desde los archivos `procesos/1.txt`, `procesos/2.txt`, etc.
   - Ejecuta la simulación Round Robin automáticamente

### Ejemplo de Salida

```
procplanner - Simulación de planificación de procesos.

PID:1,AX=10,BX=5,Quantum=1
PID:2,AX=12,BX=3,CX=3,Quantum=1
PID:3, AX=2, BX=3, CX=12,Quantum=1
Instrucciones cargadas para Proceso 1 desde procesos/1.txt

Instrucciones cargadas para Proceso 2 desde procesos/2.txt

Instrucciones cargadas para Proceso 3 desde procesos/3.txt

Ejecutando instrucción: ADD AX, 234 en el Proceso 1 Estado: Running
AX 10 BX 5 
AX 244 BX 5 
...
```

## Características del Simulador

- **Registros Simulados**: AX, BX, CX para almacenar valores
- **Contador de Programa**: PC que indica la siguiente instrucción a ejecutar
- **Estados de Proceso**: Listo, Ejecutando, Terminado
- **Planificación Round Robin**: Distribución equitativa del tiempo de CPU
- **Manejo de Errores**: Validación de saltos y operaciones
- **Carga Automática**: Los procesos se cargan automáticamente desde archivos

## Estructura de Datos

### Clase Proceso
- **PID**: Identificador único del proceso
- **Registros**: Mapa con registros AX, BX, CX
- **PC**: Contador de programa
- **Quantum**: Tiempo asignado para ejecución
- **Estado**: Estado actual del proceso (Ready, Running, Finished)
- **Instrucciones**: Vector con las instrucciones a ejecutar

### Clase CPU
- **correr()**: Método principal que ejecuta una instrucción del proceso
- **Parsing**: Análisis de instrucciones con soporte para registros y valores literales
- **Ejecución**: Implementación de todas las operaciones aritméticas y de control

## Limpieza

Para limpiar los archivos compilados:

```bash
make clean
```

## Notas Técnicas

- El simulador está diseñado para fines educativos
- Los procesos se ejecutan de forma secuencial en cada quantum
- El sistema muestra el estado de los registros después de cada instrucción
- Los archivos de instrucciones deben estar en la carpeta `procesos/`
- El archivo `procesos.txt` define la configuración inicial de todos los procesos