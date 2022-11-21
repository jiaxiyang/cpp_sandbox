## basic

1. `blocking queue`: 会阻塞的 queue, 只需要一个 not_empty cv, 用于 push 后通知 queue 不是空
1. `bounded queue`: 有边界的 queue, 需要两个 cv， not_empty 和 not_full, not_full 用于 pop 之后通知 queue 未满。

## Note

1.  解锁之后再 notify， 否则可能出现当前线程还未释放锁，被接收的线程被唤醒后拿不到锁立即就又休眠。可以用 `{}`将 wait 代码包起来

## sample

1. vitis ai : [boundedqueue](https://github.com/Xilinx/Vitis-AI/blob/c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8/src/Vitis-AI-Runtime/VART/vart/util/include/vitis/ai/bounded_queue.hpp)
   [test bounded queue](https://github.com/Xilinx/Vitis-AI/blob/c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8/src/Vitis-AI-Runtime/VART/vart/util/test/test_bounded_queue.cpp)
   [blocking queue](https://github.com/Xilinx/Vitis-AI/blob/c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8/src/Vitis-AI-Runtime/VART/vart/util/include/vitis/ai/shared_queue.hpp)
1. [minimalistic-blocking-bounded-queue](https://morestina.net/blog/1400/minimalistic-blocking-bounded-queue-for-c)
