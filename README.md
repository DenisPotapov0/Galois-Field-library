[![CI](https://github.com/DenisPotapov0/Galois-Field-library/actions/workflows/ci.yml/badge.svg)](https://github.com/DenisPotapov0/Galois-Field-library/actions/workflows/ci.yml)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
# Galois-Field-library

Библиотека для выполнения арифметических операций в поле Галуа **GF(256)**. Реализованы сложение, вычитание, умножение и деление с использованием таблиц логарифмов и антилогарифмов по модулю неприводимого полинома `0x11B` (x^8 + x^4 + x^3 + x + 1).

## Особенности

- Поддержка стандартов **C99, C11, C17, C23**.
- Поддержка встраивания в ядро Linux (`__KERNEL__`).
- Полный набор полевых операций: `+`, `−`, `×`, `÷`.
- Генерация таблиц логарифмов при первом обращении (ленивая инициализация).
- Модульные тесты, проверяющие аксиомы поля.
- Интеграция с CMake, CTest.

## Структура проекта

```
├── .github/
│   └── workflows/
│       └── ci.yml
├── src/
│   ├── Galois_Field_256.c
│   └── Galois_Field_256.h
├── test/
│   └── test_Galois_Field_256.c
├── .clang-format
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Требования

- Компилятор C с поддержкой C99 или более нового стандарта (C11, C17, C23).
- CMake (≥ 3.10).
- CUnit (libcunit1-dev) — для сборки тестов.

## Сборка и тестирование

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug    # конфигурация
cmake --build build                        # сборка
ctest --test-dir build --output-on-failure # тесты
```

## Использование

Подключите заголовочный файл и используйте функции:

```c
#include "Galois_Field_256.h"

int main(void) {
    GF256_t a = 0x57;
    GF256_t b = 0x83;

    GF256_t sum = GF256_Add(a, b);    // a + b
    GF256_t diff = GF256_Sub(a, b);   // a - b
    GF256_t prod = GF256_Mul(a, b);   // a × b
    GF256_t quot = GF256_Div(a, b);   // a ÷ b

    return 0;
}
```
Ошибка деления на 0 никак не обрабатывается, функция GF256_Div просто возвращает 0.

### API

| Функция                          | Описание                       |
|----------------------------------|--------------------------------|
| `GF256_t GF256_Add(a, b)`        | Сложение (побитовый XOR)       |
| `GF256_t GF256_Sub(a, b)`        | Вычитание (побитовый XOR)      |
| `GF256_t GF256_Mul(a, b)`        | Умножение в GF(256)            |
| `GF256_t GF256_Div(a, b)`        | Деление a на b (b ≠ 0)         |

Все операции работают с типом `GF256_t`, определённым как `uint8_t` (в пространстве пользователя) или `u8` (в ядре).

## Лицензия

Проект распространяется под лицензией **MIT**.

## Автор

Денис Потапов (2026)
