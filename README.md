---

## 🛠️ Especificaciones Técnicas y Funciones Clave

* **Mapeo de Memoria**: La recolección de estadísticas de memoria se obtiene en concordancia directa con la **MMU** administrada por el núcleo. Proporciona:
  * Memoria Total
  * Memoria Libre
  * Memoria Utilizada
  * Cálculo dinámico de porcentaje de uso.
* **Mapeo de Procesos**: A través del descriptor principal `task_struct`, el bucle extrae:
  * **PID** (`pid_t`)
  * **Nombre del Ejecutable** (`comm`)
  * **Estado del Proceso** (`__state` o `state` dependiendo de la versión del kernel)

---

## ⚙️ Compilación, Instalación y Uso

### Prerrequisitos
Para compilar módulos de kernel externos, es indispensable contar con las herramientas de construcción de software y los encabezados correspondientes a tu versión exacta del Kernel Linux:

```bash
# En distribuciones basadas en Debian/Ubuntu
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)

# En distribuciones basadas en RHEL/Fedora
sudo dnf groupinstall "Development Tools"
sudo dnf install kernel-devel kernel-headers
