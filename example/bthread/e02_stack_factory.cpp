#include "bthread/stack.h"

bthread::ContextualStack* ctx1;
bthread::ContextualStack* ctx2;
bthread::ContextualStack* ctx_main;
intptr_t  g_num1 = 0;
intptr_t  g_num2 = 0;

void jumper1(intptr_t param) {
    for(int i = 0; i < 9; i++) {
        LOG(INFO) << "context1: g_num1 = " << ++g_num1 << ", then jump to context2";
        bthread::jump_stack(ctx1, ctx2);
    }
    // 最后结尾，jump到原始上下文中，继续执行
    LOG(INFO) << "context1: g_num1 = " << ++g_num1 << ", then jump to main";
    bthread::jump_stack(ctx1, ctx_main);
}
void jumper2(intptr_t param) {
    int* p_shared_num = (int*)param;
    for(int i = 0; i < 10; i++) {
        LOG(INFO) << "context2: g_num2 = " << ++g_num2 << ", then jump to context1";
        bthread::jump_stack(ctx2, ctx1);
    }
}

int main() {
    ctx_main = bthread::get_stack(bthread::STACK_TYPE_MAIN, NULL);
    ctx1 = bthread::get_stack(bthread::STACK_TYPE_NORMAL, jumper1);
    ctx2 = bthread::get_stack(bthread::STACK_TYPE_NORMAL, jumper2);

    // 将当前context保存到fc_tmp，并切换context：fc2
    bthread::jump_stack(ctx_main, ctx2);

    LOG(INFO) << "done";

    bthread::return_stack(ctx_main);
    bthread::return_stack(ctx1);
    bthread::return_stack(ctx2);
    return 0;
}
