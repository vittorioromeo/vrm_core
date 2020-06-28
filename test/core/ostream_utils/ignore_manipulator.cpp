#include "../../utils/test_utils.hpp"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vrm/core/ostream_utils.hpp>

int main()
{
    using namespace vrm::core;
    using namespace std::literals;
    std::ostringstream o;

    o << "hi";
    TEST_ASSERT_OP(o.str(), ==, "hi"s);
    o.str("");

    o << std::setw(4) << "hi";
    TEST_ASSERT_OP(o.str(), ==, "  hi"s);
    o.str("");

    o << make_ignore_manipulator("hi");
    TEST_ASSERT(std::strcmp(o.str().c_str(), "hi\0") == 0);
    o.str("");

    o << std::setw(4) << make_ignore_manipulator("hi");
    TEST_ASSERT(std::strcmp(o.str().c_str(), "hi\0") == 0);
    o.str("");



    o << std::setw(4) << "hi"s;
    TEST_ASSERT_OP(o.str(), ==, "  hi"s);
    o.str("");

    o << make_ignore_manipulator("hi"s);
    TEST_ASSERT_OP(o.str(), ==, "hi"s);
    o.str("");

    o << std::setw(4) << make_ignore_manipulator("hi"s);
    TEST_ASSERT_OP(o.str(), ==, "hi"s);
    o.str("");

    {
        const auto& somestr = "hi"s;

        o << make_ignore_manipulator(somestr);
        TEST_ASSERT_OP(o.str(), ==, "hi"s);
        o.str("");

        o << std::setw(4) << make_ignore_manipulator(somestr);
        TEST_ASSERT_OP(o.str(), ==, "hi"s);
        o.str("");
    }
    {
        auto somestr = "hi"s;

        o << make_ignore_manipulator(somestr);
        TEST_ASSERT_OP(o.str(), ==, "hi"s);
        o.str("");

        o << std::setw(4) << make_ignore_manipulator(somestr);
        TEST_ASSERT_OP(o.str(), ==, "hi"s);
        o.str("");

        auto& ss2 = somestr;

        o << make_ignore_manipulator(ss2);
        TEST_ASSERT_OP(o.str(), ==, "hi"s);
        o.str("");

        o << std::setw(4) << make_ignore_manipulator(ss2);
        TEST_ASSERT_OP(o.str(), ==, "hi"s);
        o.str("");

        o << std::setw(4) << make_ignore_manipulator(std::move(somestr));
        TEST_ASSERT_OP(o.str(), ==, "hi"s);
        o.str("");
    }

    // o << std::setw(4) << "hi";
    // TEST_ASSERT_OP(o.str(), ==, "hi");
    // o.str("");

    return 0;
}