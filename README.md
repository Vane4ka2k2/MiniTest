<div align="center">

# 🧪 MiniTest — Header-only C++17 тестовый фреймворк

**Легковесный, быстрый и удобный заголовочный фреймворк для модульного тестирования (Unit Testing) на C++17 с цветным консольным выводом и автоматическим замером времени выполнения.**

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus)
![Header Only](https://img.shields.io/badge/Library-Header--Only-orange)
![License](https://img.shields.io/badge/License-MIT-green)

</div>

---

## 📑 Оглавление
- [🌟 Особенности](#-особенности)
- [📦 Быстрое подключение](#-быстрое-подключение)
- [💡 Пример использования](#-пример-использования)
- [📜 Лицензия](#-лицензия)

---

## 🌟 Особенности

- 🚀 **Zero Dependencies** — Состоит из одного заголовочного файла `minitest.hpp`.
- 🎨 **Цветной консольный вывод** — Наглядные статусы прохождения тестов (`PASS` / `FAIL`).
- ⏱ **Замер времени** — Автоматический измеритель времени выполнения каждого теста в миллисекундах.
- 🛠 **Макросы макета** — Набор удобных проверок: `ASSERT_EQ`, `ASSERT_NE`, `ASSERT_TRUE`, `ASSERT_FALSE`.

---

## 📦 Быстрое подключение

Скопируйте `include/minitest/minitest.hpp` в ваш проект или подключите через CMake `FetchContent`:

```cmake
include(FetchContent)
FetchContent_Declare(
    minitest
    GIT_REPOSITORY https://github.com/Vane4ka2k2/MiniTest.git
    GIT_TAG main
)
FetchContent_MakeAvailable(minitest)

target_link_libraries(my_test PRIVATE MiniTest::MiniTest)
```

---

## 💡 Пример использования

```cpp
#include <minitest/minitest.hpp>

TEST_CASE("Basic Math") {
    ASSERT_EQ(2 + 2, 4);
    ASSERT_TRUE(10 > 5);
}

int main() {
    return RUN_ALL_TESTS();
}
```

---

## 📜 Лицензия

Распространяется под лицензией **MIT**. Подробнее см. в файле [LICENSE](LICENSE).