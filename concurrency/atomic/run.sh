# g++ -o atomic atomic.cpp --std=c++17 -pthread -latomic -lglog && ./atomic
g++ -o atomic1 atomic1.cpp -fsanitize=thread --std=c++17 -pthread -latomic -lglog && ./atomic1
