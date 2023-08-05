#include"test_function_traits.hpp"
#include"template_wrapper.hpp"
#include"meta_function_operator.hpp"
int main(void){
    ::testFunctionTraits();
    using type0=
        typename nostd::template_wrapper_bind_back_t<
            nostd::template_wrapper_bind_front_t<
                nostd::TemplateWrapper<std::is_same>,
                int const
            >,
            double const volatile
        >::template unwrap<>::type;
    std::cout<<nostd::type_name<
        type0
    >()<<std::endl;
    nostd::operator_bit_left_shift_t<
        std::integral_constant<int,100>,
        std::integral_constant<int,2>
    > a;
    return 0;
}
