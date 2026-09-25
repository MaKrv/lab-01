# `ember` — starter skeleton (Lab 1)

Copy this folder to a repository of your own, `git init`, and start from **M1** of
[Lab 01](../lab-01-a-box-of-bytes.md). It builds and runs as-is.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/ember
```

## Why a skeleton exists

Lab 1 is about **bytes and types**. It is not about `while` loops, splitting a
string into words, or `std::setw` — you meet those properly in Labs 4, 5 and 7.
So the parts that need them are given to you, fully written and commented. You
read those. You write the four small things that *are* Lab 1.

## Given — read it, don't rewrite it

| File | What it does |
|---|---|
| `CMakeLists.txt` | C++17, `-Wall -Wextra -Werror`, ASan + UBSan on Debug |
| `src/main.cpp` | the prompt: read a line, split it into words, call your functions |
| `src/memory.hpp` | `Byte`, `MEM_SIZE`, `struct Memory` — the box |
| `src/dump.hpp` | the two declarations |
| `src/dump.cpp` → `dump()` | the hex dump loop |

## Yours — four `TODO(lab-01)` markers

```bash
grep -rn "TODO(lab-01)" src/
```

| # | Where | The job |
|---|---|---|
| 1 | `memory.cpp` → `mem_get` | return the byte, or 0 if the address is outside the box |
| 2 | `memory.cpp` → `mem_set` | write the byte, or return `false` if the address is outside |
| 3 | `dump.cpp` → the ASCII gutter | print the character when the byte is printable |
| 4 | `dump.cpp` → `show_byte` | one byte, four views |

When all four are done:

```txt
ember> set 0 65
ember> set 1 66
ember> get 0
65  0x41  0b01000001  'A'
ember> dump
0000  41 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |AB..............|
```

That is M2 and M3 of Lab 1. M4 (the three deliberate breakages) is in the lab.

Until you implement `mem_set`, `set` accepts everything and stores nothing, and
`get` prints `show_byte: not implemented yet`. That is the starting state, not a
bug.

## Later labs

You keep this repository for all eight labs. Every lab adds one `else if` branch
to the dispatcher in `main.cpp` and one or two new files next to these.

---

## Українською

Скопіюйте цю теку у свій репозиторій — вона вже збирається й запускається.

Lab 1 — про **байти й типи**, а не про цикли, розбір рядка на слова чи
форматування виводу (це Labs 4, 5, 7). Тому все, що потребує ще не пройденого,
вам **дано** — з коментарями, щоб читати. Ви пишете чотири маленькі речі, які й
є Lab 1: `mem_get`, `mem_set`, ASCII-колонку в дампі та `show_byte`.

Знайти свою роботу: `grep -rn "TODO(lab-01)" src/`.

Якщо C++ бачите вперше — спочатку
[C++ за годину](../cpp-survival-kit.notes.md), потім
[інструменти й git](../setup.notes.md).

## Lab 01 - Results
### M4. Exp 1 - Integer overflow
1. Встановити значення байта за адресою 0 у 255 і перевірити через get.
```text
ember> set 0 255
ember> get 0
255  0xff  0b11111111  '.'
```
2. Додати команду inc<addr>, яка читає байт, збільшує його на 1 і записує назад.
3. Виконати inc 0 і перевірити, що після 255 отримали 0, а не 256.
```text
ember> inc 0
ember> get 0
0  0x0  0b00000000  '.'
```
4. Порівняти це зі знаковим переповненням int, скомпільованим з UBSan, і зафіксувати повідомлення.

Программа була скомпільована за допомогою:
g++ -fsanitize=undefined overflow.cpp -o overflow

Результат прееповнення int:
```text
mk_@home-pc:~/pf/ember/overflow$ ./overflow 0 overflow.cpp:10:7: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int' -2147483648
```

Висновок:
За правилами C++ знакове переповнення int є невизначеною поведінкою (undefined behavior). Результат -2147483648 — це лише те, що сталося під час цього конкретного запуску, і він не є гарантованим. UBSan виявив переповнення та повідомив, що операція 2147483647 + 1 не може бути представлена типом int.
Водночас переповнення беззнакового байта є визначеною поведінкою в C++. Після збільшення значення 255 на 1 байт переходить до 0, а не до 256.

### M4. Exp 2 - Floating point
```text
mk_@home-pc:~/pf/ember/floating$ ./floating
0.3
false
```
Висновок:
Більшість десяткових дробів не мають точного бітового запису. Тому коли ми використовуємо оператор (==), він перевіряє, чи є два значення точно рівними. У нашому випадку 0.1 + 0.2 == 0.3 повертає false, оскільки через особливості представлення дробових чисел у пам'яті результат не є точно рівним 0.3, хоча при виведенні на екран ми бачимо 0.3 через округлення.
### M4. Exp 3 - ASCII dump
```text
ember> set 0 65
ember> set 1 66
ember> set 2 0
ember> dump
0000  41 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |AB..............|
0010  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
```
Висновок:
Дані в пам'яті зберігаються як числові значення байтів, але їх можна інтерпретувати ще через таблицю ASCII. В ній числа 65 і 66 відповідають А і В, тому в ASCII колонці вони відображаються як АВ, але значення 0 не є друкованим символом в таблиці, тому за написаним раніше кодом воно виводиться як ".".
### M4. Exp 4 - Memory initialization
1. Тимчасово видаляємо {} в memory.hpp в строці Byte data[MEM_SIZE]{};
2. Після перебудови проєкту та виконання команди "dump" пам'ять більше не містила гарантованих значень і видала невизначену поведінку
```text 
ember> dump
0000 90 db 20 00 00 00 00 00 90 db 20 00 00 00 00 00 |.. ....... .....| 
0010 90 db 20 00 00 00 00 00 20 00 00 00 00 00 00 00 |.. ..... .......| 
0020 20 00 00 00 00 00 00 00 04 00 00 00 00 00 00 00 | ...............| 
0030 07 00 00 00 04 00 00 00 98 eb 20 00 00 00 00 00 |.......... .....|
```
3. Після експерименту повернуто "{}" і повторно перевірено "dump":
```text
ember> dump
0000  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
0010  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
0020  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
```

Висновок:
Дужки {} у Byte data[MEM_SIZE]{} ініціалізують елементи масиву нульовими значеннями. Якщо прибрати {}, масив залишається неініціалізованим, тому його значення не гарантовані. Читання таких неініціалізованих значень призводить до невизначеної поведінки (undefined behavior).

## Notes §§1–4

### §1. sizeof
Перевірка розміру різних типів:
```text
mk_@home-pc:~/pf/ember/sizeof$ ./sizeof
1 4 4 8 8
1 2
```text

| Type | Size |
|---|---:|
| char | 1 byte |
| int | 4 bytes |
| float | 4 bytes |
| double | 8 bytes |
| void* | 8 bytes |
| std::uint8_t | 1 byte |
| std::uint16_t | 2 bytes |

Висновок:
Перевірка розмірів кожного типу показала, що 'std::uint8_t' найкраще підходить для проєкту, тому що одна клітинка пам'яті ember має займати один байт пам'яті. 'std::uint8_t' займає саме 1 байт, тоді як 'int' займає 4 байти.

### §2. Переповнення: wrap vs UB
Беззнакове 8-бітне число після переповнення переходить від 255 до 0. Це визначенна поведінка в С++. Переповнення знакового 'int' є невизначенною поведінкою, тому UBSan виявив помилку та повідомив про неї. (див.M4 Exp 1)

### §3. Числа з рухомою комою
Більшість десяткових дробів не мають точного представлення в двійковому вигляді. Тому результат 0.1+0.2 при виведенні округлюється до 0.3, але при точному порівнянні (0.1 + 0.2 == 0.3) вийшло false. (див. M4 Exp 2)

### §4. Символ — це теж число
Результат:
```text
mk_@home-pc:~/pf/ember/characters$ ./characters
65 65 65 A
B
2 2.5
```
Висновок:
Експеримент показав, що символи можуть бути представлені числами. Наприклад, символ 'A' має числовий код '65'. Результат ділення залежить від типів операндів: якщо обидва операнди цілі, C++ відкидає дробову частину, тому '5 / 2 = 2'. Якщо один з операндів є числом з рухомою комою, дробова частина зберігається, тому '5 / 2.0 = 2.5'.

### Final ember check
```text
ember 0.1 - 4096 bytes of memory you can see. Type `help`.
ember> set 0 65
ember> get 0
65  0x41  0b01000001  'A'
ember> set 5000 1
address 5000 is outside 0..4095
ember> set 0 255
ember> inc 0
ember> get 0
0  0x0  0b00000000  '.'
ember> quit
```