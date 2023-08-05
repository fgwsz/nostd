#include"test_function_traits.hpp"
#include"template_wrapper.hpp"
int main(void){
    ::testFunctionTraits();
    std::cout<<nostd::type_name<
    nostd::template_wrapper_to_instance_t<
        nostd::template_wrapper_bind_back_t<
            nostd::template_wrapper_bind_front_t<
                nostd::TemplateWrapper<std::is_same>,
                int const
            >,
            double const volatile
        >
    >
    >()<<std::endl;
    return 0;
}
