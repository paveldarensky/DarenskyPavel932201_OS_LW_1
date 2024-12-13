// Подключение необходимых заголовочных файлов
#include <linux/module.h>  // Для работы с модулями ядра
#include <linux/kernel.h>  // Для использования функций ядра (pr_info, printk)
#include <linux/init.h>    // Для макросов __init и __exit
#include <linux/proc_fs.h> // Для работы с файловой системой /proc
#include <linux/uaccess.h> // Для копирования данных между пространствами пользователя и ядра

// Макросы для лицензии и автора модуля
MODULE_LICENSE("GPL");  // Лицензия модуля (General Public License)
MODULE_AUTHOR("Tomsk State University");  // Автор модуля
MODULE_DESCRIPTION("Simple kernel module example");  // Краткое описание модуля

// Определяем имя файла в каталоге /proc
#define PROC_FILE_NAME "tsulab"

// Переменные для подсчёта обращений и степени двойки
static int access_count = 0;
static unsigned long current_value = 1;  // 2^0 = 1

// Указатель на запись в /proc
static struct proc_dir_entry *proc_file;

// Функция чтения из файла в /proc
static ssize_t tsulab_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
    char message[256]; // Уменьшенный буфер
    int len;

    // Проверка позиции для EOF
    if (*pos > 0) {
        return 0; // EOF
    }

    // Увеличиваем счётчик обращений
    access_count++;

    // Формируем строку с текущими данными
    len = snprintf(message, sizeof(message), "Обращение номер %d, новое значение равно %lu\n", access_count, current_value);

    // Возводим двойку в степень для следующего обращения
    current_value *= 2;

    // Копируем данные из пространства ядра в пространство пользователя
    if (copy_to_user(buf, message, len)) {
        return -EFAULT; // Возвращаем ошибку
    }

    // Обновляем позицию для следующего чтения
    *pos += len;
    return len;
}

// Операции для работы с файлом в /proc
static const struct proc_ops proc_file_ops = {
    .proc_read = tsulab_read,
};

// Функция инициализации модуля
// Выполняется при загрузке модуля в ядро
static int __init tsu_module_init(void) {
    pr_info("Welcome to the Tomsk State University\n");  // Вывод сообщения в журнал ядра

    // Создаём файл в /proc
    proc_file = proc_create(PROC_FILE_NAME, 0444, NULL, &proc_file_ops);

    pr_info("/proc/%s created\n", PROC_FILE_NAME);
    return 0;  // Возвращаем 0 при успешной инициализации
}

// Функция очистки модуля
// Выполняется при выгрузке модуля из ядра
static void __exit tsu_module_exit(void) {
    // Удаляем файл из /proc
    proc_remove(proc_file);
    pr_info("/proc/%s removed\n", PROC_FILE_NAME);

    pr_info("Tomsk State University forever!\n");  // Вывод сообщения в журнал ядра
}

// Макросы для указания функций инициализации и очистки
module_init(tsu_module_init);  // Указание функции инициализации
module_exit(tsu_module_exit);  // Указание функции очистки
