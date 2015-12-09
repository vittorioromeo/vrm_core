#include <cstddef>
#include <vrm/core/config.hpp>
#include <vrm/core/static_if.hpp>

volatile bool banana_eaten = false;
volatile bool apple_eaten = false;

struct banana
{
    void peel()
    {
    }
    void eat_banana()
    {
        banana_eaten = true;
    }
};

struct apple
{
    void peel()
    {
    }
    void eat_apple()
    {
        apple_eaten = true;
    }
};

struct chestnut
{
    void peel()
    {
    }
};

template <typename T>
using is_banana = std::integral_constant<bool, std::is_same<banana, T>{}>;

template <typename T>
using is_apple = std::integral_constant<bool, std::is_same<apple, T>{}>;

volatile int else_count = 0;

int main()
{
    banana_eaten = apple_eaten = false;
    else_count = 0;

    {
        auto b = banana{};
        b.peel();
        b.eat_banana();

        auto a = apple{};
        a.peel();
        a.eat_apple();

        auto c = chestnut{};
        c.peel();
    }

    banana_eaten = apple_eaten = false;
    else_count = 0;

    {
        auto b = banana{};
        b.peel();
        b.eat_banana();

        auto a = apple{};
        a.peel();
        a.eat_apple();

        auto c = chestnut{};
        c.peel();
    }

    banana_eaten = apple_eaten = false;
    else_count = 0;

    {
        auto b = banana{};
        b.peel();
        b.eat_banana();
        ++else_count;

        auto a = apple{};
        a.peel();
        a.eat_apple();
        ++else_count;

        auto c = chestnut{};
        c.peel();
        ++else_count;
        ++else_count;
    }

    banana_eaten = apple_eaten = false;
    else_count = 0;

    {
        auto b = banana{};
        b.peel();
        b.eat_banana();

        auto a = apple{};
        a.peel();
        a.eat_apple();

        auto c = chestnut{};
        c.peel();
        ++else_count;
    }

    banana_eaten = apple_eaten = false;
    else_count = 0;

    {
        auto b = banana{};
        b.peel();
        b.eat_banana();

        auto a = apple{};
        a.peel();
        a.eat_apple();

        auto c = chestnut{};
        c.peel();
        ++else_count;
    }

    return 0;
}