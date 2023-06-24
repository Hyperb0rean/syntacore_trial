# Syntacore trial
Trial task on Syntacore intern position June 2023

# Task


https://syntacore.com/media/files/trial_task_math.pdf

Задание 1. C/C++/CAS
Вычисление весового спектра линейного подпространства

a. Назовем вектором строку битов (значения 0 или 1) фиксированной длины N: то
есть, всего возможно 2^n различных векторов

b. Введем операцию сложения по модулю 2 векторов (операция xor), которая по двум
векторам a и b получает вектор a+b той же длины N

c. Пусть задано множество из векторов. Назовем его
порождающим: при помощи сложения множества A = { $a_i$ | i $\in 1..K$} можно получить векторов вида
$\sum_{i=1}^{k} b_i *a_i$, где $b_i$ равно либо 0, либо 1.

d. Весом вектора назовем количество единичных (ненулевых) битов в векторе: то
есть, вес – это натуральное число от 0 до N

Требуется для заданных порождающего множества векторов и числа N построить
гистограмму (спектр) количества различных векторов по их весу.

Можно использовать не только С/C++, но и CAS (Octave/Matlab/Mathematica) или
скриптовые языки. Важное условие – использование только стандартных библиотек, без
дополнительных пакетов.

Формат входных данных:
Текстовый файл из набора строк одинаковой длины по одному вектору в строке (символы
0 или 1 без разделителей).

Формат выходных данных:
Текстовый файл строк с парой значений вес/количество разделённых символом
табуляции, по одной паре на строку, сортированный по числовому значению веса.


# Solution

Убираем незначащие биты в двоичном векторе. Находим базис линейного подространства и его ранг. Для параллельной обработки запросов разбиваем подпространство на примерно равные части и для всех векторов ищем их веса. Если матрица из векторов с удаленными нулями оказалась единичной, то используем упрощенную формулу посчета спектра.

Ограничения реализации: большое количесвто потоков или вектора длины больше 32 могут работать нестабильно.

# Materials

https://habr.com/ru/companies/wolfram/articles/336350/
