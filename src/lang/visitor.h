#ifndef SCS_LANG_VISITOR
#define SCS_LANG_VISITOR

namespace SCS::Lang
{

template<class... T>
struct Visitor : T...
{
	using T::operator()...;
};

};

#endif // !SCS_LANG_VISITOR