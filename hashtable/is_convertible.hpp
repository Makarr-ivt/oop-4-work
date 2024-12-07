#include <iostream>
#include <type_traits>
#include <string>

template<typename T>
class is_output_streamable {
private:
    // Проверяем, можно ли вывести T в поток
    template<typename U>
    static auto test(int) -> decltype(
        std::declval<std::ostream&>() << std::declval<U>(), std::true_type()
    );

    // Альтернативный вариант, который всегда возвращает false
    template<typename>
    static auto test(...) -> std::false_type;

public:
    // Если есть возможность вывести, то value будет true
    static constexpr bool value = decltype(test<T>(0))::value;
};
