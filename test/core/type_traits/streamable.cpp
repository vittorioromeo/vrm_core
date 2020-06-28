#include <iostream>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits/streamable.hpp>

using namespace vrm::core;

struct Foo
{
};

static_assert(ostreamable<int>);
static_assert(ostreamable<float>);
static_assert(istreamable<int>);
static_assert(istreamable<float>);

static_assert(!ostreamable<Foo>);
static_assert(!istreamable<Foo>);

struct Bar
{
};

std::ostream& operator<<(std::ostream& os, const Bar&);
std::istream& operator>>(std::istream& is, Bar&);

static_assert(ostreamable<Bar>);
static_assert(istreamable<Bar>);

int main()
{
}
