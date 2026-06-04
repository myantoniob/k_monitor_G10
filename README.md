# K-Monitor

## Descripción General

**K-Monitor** es un módulo cargable para Linux (*Loadable Kernel Module - LKM*) desarrollado en lenguaje C, cuyo propósito es obtener información relacionada con la memoria del sistema y los procesos activos directamente desde las estructuras internas del kernel.

La información recopilada es expuesta al usuario mediante una entrada personalizada dentro del sistema de archivos virtual **/proc**, permitiendo consultar métricas del sistema en tiempo real sin necesidad de modificar permanentemente el núcleo del sistema operativo.

Este proyecto fue desarrollado con fines académicos para profundizar en conceptos fundamentales de sistemas operativos, administración de memoria, gestión de procesos y desarrollo de módulos del kernel Linux.

---

# Objetivos

* Comprender la arquitectura interna del Kernel Linux.
* Implementar un módulo cargable (LKM) utilizando lenguaje C.
* Obtener información de memoria directamente desde estructuras internas del kernel.
* Recorrer y analizar la tabla global de procesos activos.
* Exponer información del kernel mediante el sistema de archivos virtual `/proc`.
* Aplicar conceptos de programación a bajo nivel en sistemas Linux.

---

# Marco Teórico

## Kernel Linux

El Kernel Linux es el componente principal del sistema operativo Linux y actúa como intermediario entre las aplicaciones de usuario y los recursos físicos del equipo.

Entre sus principales funciones se encuentran:

* Administración de procesos.
* Gestión de memoria.
* Control de dispositivos.
* Administración de sistemas de archivos.
* Gestión de seguridad y permisos.
* Comunicación entre hardware y software.

---

# Arquitectura de la Solución

## Descripción General

K-Monitor implementa una arquitectura basada en la interacción entre:

* **User Space (Espacio de Usuario)**
* **Kernel Space (Espacio del Kernel)**

El módulo obtiene información directamente desde las estructuras internas del kernel y la expone mediante una entrada personalizada dentro del sistema de archivos virtual `/proc`.

```text
+---------------------+
|     Usuario         |
|  cat /proc/...      |
+----------+----------+
           |
           v
+---------------------+
| Sistema de Archivos |
|       /proc         |
+----------+----------+
           |
           v
+---------------------+
|      K-Monitor      |
|   Módulo Kernel     |
+----------+----------+
           |
           v
+---------------------+
| Kernel Linux        |
| Memoria y Procesos  |
+---------------------+
```

---

# Componentes de la Arquitectura

## Módulo del Kernel

El archivo principal `kmonitor.c` contiene toda la lógica del proyecto.

Responsabilidades:

* Inicializar el módulo mediante `insmod`.
* Crear la entrada `/proc/kmonitor_Grupo_10`.
* Obtener estadísticas de memoria.
* Recorrer la tabla global de procesos.
* Mostrar información al usuario.
* Liberar recursos mediante `rmmod`.

---

## Archivo de Cabecera

El archivo `kmonitor.h` centraliza las bibliotecas necesarias para el funcionamiento del módulo.

Proporciona acceso a:

* Interfaces para módulos del kernel.
* Gestión de procesos.
* Gestión de memoria.
* Sistema de archivos `/proc`.
* Funciones `seq_file`.

---

## Sistema de Archivos Proc

El directorio `/proc` es un sistema de archivos virtual administrado por el kernel.

Permite exponer información interna del sistema operativo mediante archivos que pueden ser consultados por los usuarios.

Ejemplo:

```bash
cat /proc/kmonitor_Grupo_10
```

Cuando se ejecuta este comando, el kernel genera dinámicamente la información proporcionada por el módulo.

---

## Subsistema de Memoria

La información de memoria es obtenida utilizando:

```c
si_meminfo()
```

junto con la estructura:

```c
struct sysinfo
```

Permitiendo consultar:

* Memoria total.
* Memoria libre.
* Memoria utilizada.
* Porcentaje de uso.

---

## Subsistema de Procesos

La lista de procesos activos es obtenida utilizando la macro:

```c
for_each_process()
```

Por cada proceso se recopila:

* PID.
* Nombre.
* Estado.

La información proviene de la estructura:

```c
task_struct
```

---

# Flujo de Funcionamiento

## 1. Carga del Módulo

Comando:

```bash
sudo insmod kmonitor.ko
```

Proceso:

1. El kernel carga el módulo en memoria.
2. Se ejecuta `iniciar_kmonitor()`.
3. Se crea `/proc/kmonitor_Grupo_10`.
4. El módulo queda disponible para consultas.

---

## 2. Consulta de Información

Comando:

```bash
cat /proc/kmonitor_Grupo_10
```

Proceso:

1. Se abre el archivo virtual.
2. Se ejecuta `abrir_kmonitor()`.
3. Se invoca `mostrar_kmonitor()`.
4. Se recopilan estadísticas de memoria.
5. Se recorre la tabla global de procesos.
6. La información es enviada al buffer secuencial.
7. Los datos son mostrados al usuario.

---

## 3. Descarga del Módulo

Comando:

```bash
sudo rmmod kmonitor
```

Proceso:

1. Se ejecuta `salir_kmonitor()`.
2. Se elimina `/proc/kmonitor_Grupo_10`.
3. Se liberan los recursos asociados.
4. El módulo desaparece completamente del kernel.

---

# Compilación

```bash
make
```

El proceso genera el archivo:

```text
kmonitor.ko
```

---

# Instalación

Cargar el módulo:

```bash
sudo insmod kmonitor.ko
```

Verificar que se encuentre cargado:

```bash
lsmod | grep kmonitor
```

Consultar la información:

```bash
cat /proc/kmonitor_Grupo_10
```

Descargar el módulo:

```bash
sudo rmmod kmonitor
```

---

# Tecnologías Utilizadas

* Lenguaje C
* Linux Kernel Modules (LKM)
* Sistema de archivos virtual `/proc`
* Estructura `task_struct`
* Estructura `sysinfo`
* API `seq_file`
* GNU Make

---

# Resultados Esperados

Al consultar el archivo:

```bash
cat /proc/kmonitor_Grupo_10
```

el usuario podrá visualizar información en tiempo real sobre:

* Uso de memoria del sistema.
* Memoria libre y utilizada.
* Porcentaje de utilización.
* Procesos activos.
* PID de cada proceso.
* Estado de ejecución de los procesos.

---

# Autor

Proyecto académico desarrollado como parte del curso de Sistemas Operativos utilizando módulos del Kernel Linux.
