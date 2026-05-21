#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>

#define NOMBRE_PROC "kmonitor_proyecto"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grupo Proyecto");
MODULE_DESCRIPTION("Modulo de monitoreo del sistema - Proyecto");
MODULE_VERSION("1.0");

//  Puntero del /proc
static struct proc_dir_entry *entrada_proc;

//  Traducción de estados de procesos
static const char *estado_proceso(long estado)
{
    if (estado == TASK_RUNNING)
        return "En ejecucion";
    else if (estado & TASK_INTERRUPTIBLE)
        return "Suspendido";
    else if (estado & TASK_UNINTERRUPTIBLE)
        return "Bloqueado";
    else if (estado == EXIT_ZOMBIE)
        return "Zombie";
    else
        return "Desconocido";
}

//  Mostrar información en /proc
static int mostrar_kmonitor(struct seq_file *m, void *v)
{
    struct sysinfo info_sistema;
    struct task_struct *proceso;

    unsigned long memoria_total, memoria_libre, memoria_usada;
    int porcentaje_uso;

    si_meminfo(&info_sistema);

    memoria_total = info_sistema.totalram * 4;
    memoria_libre = info_sistema.freeram * 4;
    memoria_usada = memoria_total - memoria_libre;

    porcentaje_uso = (memoria_total) ? (memoria_usada * 100) / memoria_total : 0;

    seq_printf(m, "===== MEMORIA DEL SISTEMA =====\n");
    seq_printf(m, "Memoria total: %lu KB\n", memoria_total);
    seq_printf(m, "Memoria libre: %lu KB\n", memoria_libre);
    seq_printf(m, "Uso de memoria: %d%%\n\n", porcentaje_uso);

    seq_printf(m, "===== LISTA DE PROCESOS =====\n");
    seq_printf(m, "%-10s %-25s %-15s\n", "PID", "NOMBRE", "ESTADO");

    for_each_process(proceso) {
        seq_printf(m, "%-10d %-25s %-15s\n",
                   proceso->pid,
                   proceso->comm,
                   estado_proceso(proceso->state));
    }

    return 0;
}

//  open del proc
static int abrir_kmonitor(struct inode *inode, struct file *file)
{
    return single_open(file, mostrar_kmonitor, NULL);
}

//  operaciones del proc
static const struct proc_ops operaciones_proc = {
    .proc_open = abrir_kmonitor,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

//  INIT del módulo
static int __init iniciar_kmonitor(void)
{
    entrada_proc = proc_create(NOMBRE_PROC, 0444, NULL, &operaciones_proc);

    if (!entrada_proc) {
        printk(KERN_ERR "kmonitor_proyecto: error al crear /proc\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "kmonitor_proyecto: modulo cargado\n");
    return 0;
}

//  EXIT del módulo
static void __exit salir_kmonitor(void)
{
    if (entrada_proc)
        proc_remove(entrada_proc);

    printk(KERN_INFO "kmonitor_proyecto: modulo eliminado\n");
}

module_init(iniciar_kmonitor);
module_exit(salir_kmonitor);