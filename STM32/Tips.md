- 强制执行，STM32会把没有用的进程跳过，比如软件延时。所以要加这个。
> asm("nop")

- 浮点运算单元，F1的话切记要DISABLE
> FPU_STATE       ?= DISABLE
