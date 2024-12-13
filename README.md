LabWork_2:

Для тестирования на Linux в терминале:

g++ -o lw2 lw2.cpp

./lw2

Через другой терминал:

Или

telnet localhost 11111

Далее любые сообщения посылаем.


Или 

посылаем сигнал

сначала узнаем <PID>: ps aux | grep lw2

Заетм:

kill -SIGHUP <PID>

Или и посылание сообщений и посылание сигнала только ещё третий терминал.

Завершить процесс: kill -9 <PID>

LabWork_3:
Для тестирования на Linux в терминале:

make

затем

sudo insmod tsulab.ko

затем

dmesg | tail

или

dmesg | tail -n 1

(для вывода одного последнего сообщения из буфера)

затем

sudo rmmod tsulab

и затем аналогично

dmesg | tail

или

dmesg | tail -n 1

(для вывода одного последнего сообщения из буфера)

LabWork_4:
Для тестирования на Linux в терминале:

make

затем

sudo insmod tsulab.ko

затем

sudo dmesg | tail

или

sudo dmesg | tail -n 2

(для вывода двух последних сообщений из буфера)

Можно наблюдать сообщения:

"Welcome to the Tomsk State University"

"/proc/tsulab created"

затем

cat /proc/tsulab

(после чего можно ещё раз то же самое и можно наблюдать функционал модуля - увеличение степени 2-ки с количеством обращений)

затем

sudo rmmod tsulab

и затем аналогично

sudo dmesg | tail

или

sudo dmesg | tail -n 2

(для вывода двух последних сообщений из буфера)

Можно наблюдать сообщения:

"/proc/tsulab removed"

"Tomsk State University forever!"
