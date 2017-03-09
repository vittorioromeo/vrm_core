#include <iostream>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits/streamable.hpp>

using namespace vrm::core;

struct Foo
{
};

VRM_CORE_STATIC_ASSERT_NM(ostreamable<int>);
VRM_CORE_STATIC_ASSERT_NM(ostreamable<float>);
VRM_CORE_STATIC_ASSERT_NM(istreamable<int>);
VRM_CORE_STATIC_ASSERT_NM(istreamable<float>);

VRM_CORE_STATIC_ASSERT_NM(!ostreamable<Foo>);
VRM_CORE_STATIC_ASSERT_NM(!istreamable<Foo>);

struct Bar
{
};

std::ostream& operator<<(std::ostream& os, const Bar&);
std::istream& operator>>(std::istream& is, Bar&);

VRM_CORE_STATIC_ASSERT_NM(ostreamable<Bar>);
VRM_CORE_STATIC_ASSERT_NM(istreamable<Bar>);

int main()
{
}
