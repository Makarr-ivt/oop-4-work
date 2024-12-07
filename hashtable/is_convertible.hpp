#include <iostream>
#include <type_traits>
#include <string>
using namespace std;

template<typename T>
class is_output_streamable {
private:
    // Проверяем, можно ли вывести T в поток
    template<typename U>
    static auto test(int) -> decltype(
        declval<ostream&>() << declval<U>(), true_type()
    );

    // Альтернативный вариант, который всегда возвращает false
    template<typename>
    static auto test(...) -> false_type;

public:
    // Если есть возможность вывести, то value будет true
    static constexpr bool value = decltype(test<T>(0))::value;
};
