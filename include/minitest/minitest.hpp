#ifndef MINITEST_HPP
#define MINITEST_HPP

#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Пространство имён, чтобы избежать конфликтов
namespace minitest {

// Цвета вынесены в constexpr переменные (не макросы)
inline constexpr auto COLOR_PASS  = "\033[32m";
inline constexpr auto COLOR_FAIL  = "\033[31m";
inline constexpr auto COLOR_RESET = "\033[0m";

// ---------- Базовые исключения для assert'ов ----------
class AssertionFailure : public std::runtime_error {
public:
    AssertionFailure(const std::string& msg, const char* file, int line)
        : std::runtime_error(msg),
          file_(file),
          line_(line) {}

    const char* file() const noexcept { return file_; }
    int line() const noexcept { return line_; }

private:
    const char* file_;
    int line_;
};

// ---------- Макросы assert'ов с информацией о месте вызова ----------
// Формируем сообщение и бросаем AssertionFailure
#define MINITEST_ASSERT_EQ(actual, expected)                                   \
    do {                                                                       \
        if ((actual) != (expected)) {                                          \
            std::ostringstream ss;                                             \
            ss << "Expected: " << (expected) << ", Actual: " << (actual);      \
            throw ::minitest::AssertionFailure(ss.str(), __FILE__, __LINE__);  \
        }                                                                      \
    } while(0)

#define MINITEST_ASSERT_TRUE(expr)                                             \
    do {                                                                       \
        if (!(expr)) {                                                         \
            std::ostringstream ss;                                             \
            ss << "Assertion failed: " << #expr;                               \
            throw ::minitest::AssertionFailure(ss.str(), __FILE__, __LINE__);  \
        }                                                                      \
    } while(0)

#define MINITEST_ASSERT_THROW(expr, exception_type)                            \
    do {                                                                       \
        bool caught = false;                                                   \
        try {                                                                  \
            expr;                                                              \
        } catch (const exception_type&) {                                      \
            caught = true;                                                     \
        } catch (...) {}                                                       \
        if (!caught) {                                                         \
            std::ostringstream ss;                                             \
            ss << "Expected exception: " << #exception_type << " was not thrown."; \
            throw ::minitest::AssertionFailure(ss.str(), __FILE__, __LINE__);  \
        }                                                                      \
    } while(0)

// ---------- Тестовый реестр (синглтон) ----------
class TestSuite {
public:
    using TestCase = std::function<void()>;

    struct TestEntry {
        std::string name;
        TestCase    test;
    };

    static TestSuite& instance() {
        static TestSuite suite;
        return suite;
    }

    // Добавляет тест, игнорируя дубликаты имён (с предупреждением)
    void add_test(const std::string& name, TestCase test) {
        for (const auto& entry : tests_) {
            if (entry.name == name) {
                std::cerr << "[WARNING] Test \"" << name << "\" is already registered. Skipping.\n";
                return;
            }
        }
        tests_.push_back({name, std::move(test)});
    }

    // Запуск всех тестов; возвращает количество пройденных
    int run_all(std::ostream& out = std::cout) {
        int passed = 0;
        out << "Running " << tests_.size() << " test(s)...\n" << std::endl;

        for (const auto& entry : tests_) {
            auto start = std::chrono::steady_clock::now();
            try {
                entry.test();
                auto end = std::chrono::steady_clock::now();
                auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                out << COLOR_PASS << "[PASS]" << COLOR_RESET << " "
                    << entry.name << " (" << dur << "ms)" << std::endl;
                ++passed;
            } catch (const AssertionFailure& e) {
                auto end = std::chrono::steady_clock::now();
                auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                out << COLOR_FAIL << "[FAIL]" << COLOR_RESET << " "
                    << entry.name << " (" << dur << "ms)\n"
                    << "  Assertion failed at " << e.file() << ":" << e.line() << "\n"
                    << "  " << e.what() << std::endl;
            } catch (const std::exception& e) {
                auto end = std::chrono::steady_clock::now();
                auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                out << COLOR_FAIL << "[FAIL]" << COLOR_RESET << " "
                    << entry.name << " (" << dur << "ms) -> " << e.what() << std::endl;
            } catch (...) {
                auto end = std::chrono::steady_clock::now();
                auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                out << COLOR_FAIL << "[FAIL]" << COLOR_RESET << " "
                    << entry.name << " (" << dur << "ms) -> unknown exception" << std::endl;
            }
        }

        out << "\nResults: " << passed << "/" << tests_.size() << " passed." << std::endl;
        return passed;
    }

private:
    std::vector<TestEntry> tests_;
    TestSuite() = default;
};

// ---------- Макрос авторегистрации (только в .cpp!) ----------
// Использует немедленно вызываемую лямбду для создания глобальной переменной.
// Имя формируется с добавлением номера строки, чтобы избежать коллизий в одной единице трансляции.
#define MINITEST_TEST(name)                                                    \
    static void minitest_test_##name();                                        \
    namespace {                                                                \
        struct MinitestRegistrar_##name {                                      \
            MinitestRegistrar_##name() {                                       \
                ::minitest::TestSuite::instance().add_test(#name,              \
                    minitest_test_##name);                                     \
            }                                                                  \
        } minitest_registrar_##name;                                           \
    }                                                                          \
    static void minitest_test_##name()

} // namespace minitest

#endif // MINITEST_HPP
