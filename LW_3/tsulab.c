// Подключение необходимых заголовочных файлов
#include <linux/module.h>  // Для работы с модулями ядра
#include <linux/kernel.h>  // Для использования функций ядра (pr_info, printk)
#include <linux/init.h>    // Для макросов __init и __exit

// Макросы для лицензии и автора модуля
MODULE_LICENSE("GPL");  // Лицензия модуля (General Public License)
MODULE_AUTHOR("Tomsk State University");  // Автор модуля
MODULE_DESCRIPTION("Simple kernel module example");  // Краткое описание модуля

// Функция инициализации модуля
// Выполняется при загрузке модуля в ядро
static int __init tsu_module_init(void) {
    pr_info("Welcome to the Tomsk State University\n");  // Вывод сообщения в журнал ядра
    return 0;  // Возвращаем 0 при успешной инициализации
}

// Функция очистки модуля
// Выполняется при выгрузке модуля из ядра
static void __exit tsu_module_exit(void) {
    pr_info("Tomsk State University forever!\n");  // Вывод сообщения в журнал ядра
}

// Макросы для указания функций инициализации и очистки
module_init(tsu_module_init);  // Указание функции инициализации
module_exit(tsu_module_exit);  // Указание функции очистки