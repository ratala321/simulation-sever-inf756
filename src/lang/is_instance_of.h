#ifndef SCS_LANG_IS_INSTANCE_OF
#define SCS_LANG_IS_INSTANCE_OF

// Source - https://stackoverflow.com/a/5999432
// Posted by bluescarni, modified by community. See post 'Timeline' for change history
// Retrieved 2026-10-31, License - CC BY-SA 3.0

#include <type_traits>

namespace SCS::Lang
{

template <template <typename> class F>
struct conversion_tester
{
	template <typename T>
	conversion_tester(const F<T>&);
};

template <class From, template <typename> class To>
struct is_instance_of
{
	static constexpr bool value = std::is_convertible<From, conversion_tester<To>>::value;
};

};

#endif //!SCS_LANG_IS_INSTANCE_OF
