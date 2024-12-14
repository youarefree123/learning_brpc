#include "bthread/context.h"
#include "bthread/bthread.h"

::bthread_fcontext_t fc1;
::bthread_fcontext_t fc2;
::bthread_fcontext_t fc_tmp;
intptr_t  g_num1 = 0;
intptr_t  g_num2 = 0;
int  g_shared_num = 0;
intptr_t vp = (intptr_t)(&g_shared_num);

void jumper1(intptr_t param) {
    int* p_shared_num = (int*)param;
    for(int i = 0; i < 9; i++) {
        LOG(INFO) << "context1: g_num1 = " << ++g_num1 <<
                ", g_shared_num = " << ++(*p_shared_num) << ", then jump to context2";
        ::bthread_jump_fcontext(&fc1, fc2, param);
    }
    // 最后结尾，jump到原始上下文中，继续执行
    LOG(INFO) << "context1: g_num1 = " << ++g_num1 << 
            ", g_shared_num = " << ++(*p_shared_num) << ", then jump to main";
    ::bthread_jump_fcontext(&fc1, fc_tmp, param);
}
void jumper2(intptr_t param) {
    int* p_shared_num = (int*)param;
    for(int i = 0; i < 10; i++) {
        LOG(INFO) << "context2: g_num2 = " << ++g_num2 << 
                ", g_shared_num = " << ++(*p_shared_num) << ", then jump to context1";
        ::bthread_jump_fcontext(&fc2, fc1, param);
    }
}

int main() {
    static const std::size_t stack_size = 8192;

    // 创建两个上下文
    void *sp1 = ::malloc(stack_size);
    fc1 = ::bthread_make_fcontext((char*)sp1 + stack_size, stack_size, jumper1);

    void *sp2 = ::malloc(stack_size);
    fc2 = ::bthread_make_fcontext((char*)sp2 + stack_size, stack_size, jumper2); 

    // 将当前context保存到fc_tmp，并切换context：fc2
    ::bthread_jump_fcontext(&fc_tmp, fc2, vp); // 将g_shared_num作为vp，实现context之间的变量传递

    LOG(INFO) << "done";

    ::free(sp1);
    ::free(sp2);
    return 0;
}