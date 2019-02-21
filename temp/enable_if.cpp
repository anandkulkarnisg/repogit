

#include <cstdlib>
#include <cstdio>
#include <cstdint>

#include <type_traits>

namespace utils
{

namespace details
{

template< typename E >
using enable_enum_t = typename std::enable_if< std::is_enum<E>::value, 
                                               typename std::underlying_type<E>::type 
                                             >::type;

}   // namespace details


template< typename E >
constexpr inline details::enable_enum_t<E> underlying_value( E e )noexcept
{
    return static_cast< typename std::underlying_type<E>::type >( e );
}   


template< typename E , typename T>
constexpr inline typename std::enable_if< std::is_enum<E>::value &&
                                          std::is_integral<T>::value, E
                                         >::type 
 to_enum( T value ) noexcept 
 {
     return static_cast<E>( value );
 }

} // namespace utils




int main()
{
    enum class E{ a = 1, b = 3, c = 5 };

    constexpr auto a = utils::underlying_value(E::a);
    constexpr E    b = utils::to_enum<E>(5);
    constexpr auto bv = utils::underlying_value(b);
	
	constexpr auto ret = utils::underlying_value(E::b);

    printf("a = %d, b = %d, c=%d", a,bv,ret);
    return 0;
}


