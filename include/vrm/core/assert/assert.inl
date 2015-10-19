// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/assert/assert.hpp>

#if !VRM_CORE_IMPL_ASSERT_DISABLED

#include <iostream>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        namespace assert
        {
            template <typename TLhs, typename TRhs>
            void fire(const char* code, const char* line, const char* file,
                const char* lhs, const char* op, const char* rhs,
                const char* msg, const TLhs& lhs_res, const TRhs& rhs_res)
            {
                auto c_str_empty([](auto c_str)
                    {
                        return c_str && !c_str[0];
                    });

                std::cout << "ASSERTION FAILED\n";
                if(!c_str_empty(msg)) std::cout << "Message: " << msg << "\n";
                std::cout << "\n";

                std::cout << "[file: " << file << "]\n"
                          << "[line: " << line << "]\n\n" << code << "\n\n";

                std::cout << lhs << " = " << lhs_res << "\n" << rhs << " = "
                          << rhs_res << "\n\n"
                          << "(" << lhs_res << " " << op << " " << rhs_res
                          << ") == false\n\n";

                if(get_state()._skip)
                {
                    std::cout << "Skipping assertion..." << std::endl;
                    return;
                }

                std::cout << "0) Skip this assertion.\n"
                          << "1) Skip all assertions.\n"
                          << "_) Terminate the program." << std::endl;

                std::string input;
                std::cin >> input;

                if(input == "0")
                {
                    return;
                }

                if(input == "1")
                {
                    get_state()._skip = true;
                    return;
                }

                std::terminate();
            }
        }
    }
}
VRM_CORE_NAMESPACE_END

#endif