#include "../../utils/test_utils.hpp"
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/resizable_buffer.hpp>
#include <cassert>
#include <cstddef>
#include <functional>
#include <new>
#include <utility>

using vrm::core::sz_t;

template <sz_t N>
class stack_store
{
public:
    stack_store() = default;

    stack_store(stack_store const&) = delete;

    stack_store& operator=(stack_store const&) = delete;

    char* allocate(sz_t n)
    {
        assert(pointer_in_buffer(ptr_) &&
               "stack_allocator has outlived stack_store");

        n = align(n);

        if(buf_ + N >= ptr_ + n)
        {
            auto r(ptr_);

            ptr_ += n;

            return r;
        }
        else
        {
            return static_cast<char*>(::operator new(n));
        }
    }

    void deallocate(char* const p, sz_t n) noexcept
    {
        assert(pointer_in_buffer(ptr_) &&
               "stack_allocator has outlived stack_store");

        if(pointer_in_buffer(p))
        {
            n = align(n);

            if(p + n == ptr_)
            {
                ptr_ = p;
            }
            // else do nothing
        }
        else
        {
            ::operator delete(p);
        }
    }

    void reset() noexcept { ptr_ = buf_; }

    static constexpr ::sz_t size() noexcept { return N; }

    ::sz_t used() const { return ::sz_t(ptr_ - buf_); }

private:
    static constexpr ::sz_t align(::sz_t const n) noexcept
    {
        return (n + (alignment - 1)) & -alignment;
    }

    bool pointer_in_buffer(char* const p) noexcept
    {
        return (buf_ <= p) && (p <= buf_ + N);
    }

private:
    static constexpr auto const alignment = alignof(::max_align_t);

    char* ptr_{buf_};

    alignas(::max_align_t) char buf_[N];
};

template <class T, sz_t N>
class stack_allocator
{
public:
    using store_type = stack_store<N>;

    using size_type = ::sz_t;

    using difference_type = ::std::ptrdiff_t;

    using pointer = T*;
    using const_pointer = T const*;

    using reference = T&;
    using const_reference = T const&;

    using value_type = T;

    template <class U>
    struct rebind
    {
        using other = stack_allocator<U, N>;
    };

    stack_allocator() = default;

    stack_allocator(stack_store<N>& s) noexcept : store_(&s) {}

    template <class U>
    stack_allocator(stack_allocator<U, N> const& other) noexcept
        : store_(other.store_)
    {
    }

    stack_allocator& operator=(stack_allocator const&) = delete;

    T* allocate(::sz_t const n)
    {
        return static_cast<T*>(
            static_cast<void*>(store_->allocate(n * sizeof(T))));
    }

    void deallocate(T* const p, ::sz_t const n) noexcept
    {
        store_->deallocate(
            static_cast<char*>(static_cast<void*>(p)), n * sizeof(T));
    }

    template <class U, class... A>
    void construct(U* const p, A&&... args)
    {
        new(p) T(::std::forward<A>(args)...);
    }

    template <class U>
    void destroy(U* const p)
    {
        p->~T();
    }

    template <class U, sz_t M>
    inline bool operator==(stack_allocator<U, M> const& rhs) const noexcept
    {
        return store_ == rhs.store_;
    }

    template <class U, sz_t M>
    inline bool operator!=(stack_allocator<U, M> const& rhs) const noexcept
    {
        return !(*this == rhs);
    }

private:
    template <class U, sz_t M>
    friend class stack_allocator;

    store_type* store_{};
};

volatile int cc = 0;
volatile int dd = 0;
volatile int copies = 0;

struct item
{
    int l;
    item() { ++cc; }

    item(const item&) { ++copies; }
    item(item&&) = delete;

    item& operator=(const item&)
    {
        ++copies;
        return *this;
    }

    ~item() { ++dd; }
};

template <typename TAllocator = ::std::allocator<item>>
void run_test(const TAllocator& allocator = TAllocator{})
{
    cc = dd = copies = 0;

    vrm::core::resizable_buffer<item, TAllocator> rb{allocator};

    TEST_ASSERT_NS_OP(rb.data(), ==, nullptr);
    TEST_ASSERT_OP(cc, ==, 0);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(0, 10);

    TEST_ASSERT_NS_OP(rb.data(), !=, nullptr);
    TEST_ASSERT_OP(cc, ==, 10);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(10, 20);

    TEST_ASSERT_NS_OP(rb.data(), !=, nullptr);
    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 10);
    TEST_ASSERT_OP(dd, ==, 10);

    rb.destroy_and_deallocate(20);

    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 10);
    TEST_ASSERT_OP(dd, ==, 30);
}

template <typename TAllocator = ::std::allocator<item>>
void run_test2(const TAllocator& allocator = TAllocator{})
{
    cc = dd = copies = 0;

    vrm::core::resizable_buffer<item, TAllocator> rb{allocator};

    TEST_ASSERT_NS_OP(rb.data(), ==, nullptr);
    TEST_ASSERT_OP(cc, ==, 0);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(0, 10);

    TEST_ASSERT_NS_OP(rb.data(), !=, nullptr);
    TEST_ASSERT_OP(cc, ==, 10);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(10, 20);

    TEST_ASSERT_NS_OP(rb.data(), !=, nullptr);
    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 10);
    TEST_ASSERT_OP(dd, ==, 10);

    auto rb2 = std::move(rb);

    rb2.destroy_and_deallocate(20);
}

template <typename TAllocator = ::std::allocator<item>>
void run_test3(const TAllocator& allocator = TAllocator{})
{
    cc = dd = copies = 0;

    vrm::core::resizable_buffer<item, TAllocator> rb{allocator};

    TEST_ASSERT_NS_OP(rb.data(), ==, nullptr);
    TEST_ASSERT_OP(cc, ==, 0);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(0, 10);

    TEST_ASSERT_NS_OP(rb.data(), !=, nullptr);
    TEST_ASSERT_OP(cc, ==, 10);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(10, 20);

    TEST_ASSERT_NS_OP(rb.data(), !=, nullptr);
    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 10);
    TEST_ASSERT_OP(dd, ==, 10);

    auto rb2 = rb.copy(20);

    TEST_ASSERT_NS_OP(rb.data(), !=, nullptr);
    TEST_ASSERT_NS_OP(rb2.data(), !=, nullptr);
    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 30);
    TEST_ASSERT_OP(dd, ==, 10);

    rb.destroy_and_deallocate(20);
    rb2.destroy_and_deallocate(20);

    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 30);
    TEST_ASSERT_OP(dd, ==, 50);
}


int main()
{
    using namespace vrm::core;

    run_test();
    run_test2();
    run_test3();

    {
        stack_store<sizeof(item) * 50> store;
        stack_allocator<item, sizeof(item) * 50> sa{store};
        run_test<decltype(sa)>(sa);
    }

    {
        stack_store<sizeof(item) * 50> store;
        stack_allocator<item, sizeof(item) * 50> sa{store};
        run_test2<decltype(sa)>(sa);
    }

    {
        stack_store<sizeof(item) * 50> store;
        stack_allocator<item, sizeof(item) * 50> sa{store};
        run_test3<decltype(sa)>(sa);
    }

    return 0;
}
