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
├── procesos/             # Archivos de procesos de ejemplo
│   ├── proceso1.txt
│   ├── proceso2.txt
│   └── proceso3.txt
└── RAM/                  # Almacenamiento de contexto
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

### Formato de Archivos de Proceso

Cada archivo de proceso debe seguir un formato como el siguiente:

```
PID: 1, AX=6, BX=2, CX=3, Quantum=1
ADD AX, CX
INC BX
SUB AX, BX
NOP
MUL BX, AX
```

- **Primera línea**: Metadatos del proceso (PID, registros iniciales, quantum)
- **Líneas siguientes**: Instrucciones a ejecutar

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

3. **Durante la ejecución**:
   - El programa te pedirá que ingreses los nombres de los archivos de procesos
   - Escribe el nombre del archivo (ej: `proceso1.txt`)
   - Cuando hayas ingresado todos los procesos, escribe `run` para comenzar la simulación

### Ejemplo de Uso

```bash
$ ./simulador
procplanner - Simulación de planificación de procesos.
para ejecutar escribe run
escribe el documento que tiene las instrucciones de un proceso
proceso1.txt
escribe el documento que tiene las instrucciones de un proceso
proceso2.txt
escribe el documento que tiene las instrucciones de un proceso
run
Procesos cargados en "RAM"
Ejecutando instrucción: ADD AX, CX en el Proceso1
AX: 6 Bx: 2 Cx: 3
AX: 9 Bx: 2 Cx: 3
...
```

## Características del Simulador

- **Registros Simulados**: AX, BX, CX para almacenar valores
- **Contador de Programa**: PC que indica la siguiente instrucción a ejecutar
- **Estados de Proceso**: Listo, Ejecutando, Terminado
- **Planificación Round Robin**: Distribución equitativa del tiempo de CPU
- **Manejo de Errores**: Validación de saltos y operaciones

## Limpieza

Para limpiar los archivos compilados:

```bash
make clean
```

## Notas Técnicas

- El simulador está diseñado para fines educativos
- Los procesos se ejecutan de forma secuencial en cada quantum
- El sistema muestra el estado de los registros después de cada instrucción
