
использование: 
brainfuck <filename> debug
brainfuck <filename>

краткий комментарий:

> = увеличение указателя памяти или смещение право на 1 блок
< = уменьшение или смещение влево на 1 блок
+ = увеличение значения в ячейке памяти, на которую ссылается указатель
- = соответственно уменьшение на единиц
[ = аналог цикла while(cur_block_value != 0)
] = если значение в ячейке на которую указывает указатель не равно нулю, то переход на [
, = аналог getchar(), ввод одного символа
. = аналог putchar(), вывод одного сивола на кончоль

s = распечатать состояние ядра (только если ключ debug указан)


