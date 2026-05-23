#ifndef KMONITOR_H
#define KMONITOR_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>

#define NOMBRE_PROC "kmonitor_proyecto"

//funciones declaras para el kmonitor.c
/*static const char *estado_proceso(long estado);
static int mostrar_kmonitor(struct seq_file *m, void *v);
static int abrir_kmonitor(struct inode *inode, struct file *file);
static int __init iniciar_kmonitor(void);
static void __exit salir_kmonitor(void);*/    //NO BORRAR ESTO

#endif 
//kmonitor.h
