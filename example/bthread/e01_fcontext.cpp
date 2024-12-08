#include "bthread/context.h"
#include "bthread/bthread.h"

::bthread_fcontext_t fc1;
::bthread_fcontext_t fc2;
::bthread_fcontext_t fc_tmp;
intptr_t  g_num1 = 0;
intptr_t  g_num2 = 0;

static void jumper1(intptr_t param) {
    for(int i = 0; i < 9; i++) {
        LOG(INFO) << "context1: g_num1 = " << ++g_num1 << ", then jump to context2";
        ::bthread_jump_fcontext(&fc1, fc2, 0);
    }
    // 最后结尾，jump到原始上下文中，继续执行
    LOG(INFO) << "context1: g_num1 = " << ++g_num1 << ", then jump to main";
    ::bthread_jump_fcontext(&fc1, fc_tmp, 0);
}
static void jumper2(intptr_t param) {
    for(int i = 0; i < 10; i++) {
        LOG(INFO) << "context2: g_num2 = " << ++g_num2 << ", then jump to context1";
        ::bthread_jump_fcontext(&fc2, fc1, 0);
    }
}

int main() {
    static const std::size_t stack_size = 8192;

    // 创建两个上下文
    void *sp1 = ::malloc(stack_size);
    fc1 = ::bthread_make_fcontext((char*)sp1 + stack_size, stack_size, jumper1);

    void *sp2 = ::malloc(stack_size);
    fc2 = ::bthread_make_fcontext((char*)sp2 + stack_size, stack_size, jumper2); 

    // 将当前上下文保存到fc_tmp，并切换上下为fc2
    ::bthread_jump_fcontext(&fc_tmp, fc2, 0);

    LOG(INFO) << "done";

    ::free(sp1);
    ::free(sp2);
    return 0;
}