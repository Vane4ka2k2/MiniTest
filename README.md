# MiniTest

Минималистичный, легковесный **header-only** тестовый фреймворк для C++17. Идеально подходит для небольших проектов, лабораторных работ и быстрого написания unit-тестов без необходимости сборки тяжелых библиотек (вроде Google Test).

## ✨ Возможности
- **Header-only**: Для интеграции достаточно скопировать один файл `minitest.hpp`.
- **Автоматическая регистрация тестов**: Не нужно вручную добавлять тест в список запуска — макрос `MINITEST_TEST` сделает это за вас.
- **Цветной вывод результатов**: Выделение пройденных и проваленных тестов зеленым и красным цветами в терминале.
- **Бенчмаркинг**: Отображение времени выполнения каждого теста в миллисекундах.
- **Отчет об ошибках**: Вывод имени файла и точного номера строки, на которой сработало падение утверждения (assert).

---

## 🛠️ Доступные макросы

### Утверждения (Assertions)
* `MINITEST_ASSERT_EQ(actual, expected)` — проверка равенства двух значений.
* `MINITEST_ASSERT_NEQ(actual, expected)` — проверка неравенства двух значений.
* `MINITEST_ASSERT_TRUE(expr)` — проверка того, что выражение `expr` истинно (`true`).
* `MINITEST_ASSERT_FALSE(expr)` — проверка того, что выражение `expr` ложно (`false`).
* `MINITEST_ASSERT_THROW(expr, ExceptionType)` — проверка того, что выражение `expr` генерирует исключение указанного типа `ExceptionType`.

### Описание и запуск тестов
* `MINITEST_TEST(test_name) { ... }` — объявление тест-кейса.
* `MINITEST_MAIN()` — автоматическое генерирование функции `main()`, которая запускает все зарегистрированные тесты и возвращает количество упавших проверок как код завершения процесса.

---

## 🚀 Быстрый старт

Просто подключите `minitest.hpp` в вашем файле с тестами:

```cpp
#include "minitest/minitest.hpp"
#include <stdexcept>

// Объявление теста
MINITEST_TEST(MathOperations) {
    int result = 2 + 2;
    MINITEST_ASSERT_EQ(result, 4);
    MINITEST_ASSERT_NEQ(result, 5);
}

// Тестирование логических выражений
MINITEST_TEST(BooleanLogic) {
    bool is_cpp_fun = true;
    MINITEST_ASSERT_TRUE(is_cpp_fun);
}

// Тестирование ожидаемых исключений
MINITEST_TEST(ExceptionHandling) {
    auto divide_by_zero = []() {
        throw std::invalid_argument("Division by zero!");
    };
    MINITEST_ASSERT_THROW(divide_by_zero(), std::invalid_argument);
}

// Генерируем main()
MINITEST_MAIN()
```

### Сборка и запуск:
Поскольку фреймворк header-only, вам нужно лишь указать путь к заголовочным файлам при компиляции:

```bash
g++ -std=c++17 -I./include test_main.cpp -o run_tests
./run_tests
```

### Пример вывода в консоли:
```text
Running 3 test(s)...

[PASS] MathOperations (0ms)
[PASS] BooleanLogic (0ms)
[PASS] ExceptionHandling (0ms)

Results: 3/3 passed.
```
