# g++ -o atomic atomic.cpp --std=c++17 -pthread -latomic -lglog && ./atomic
# g++ -o atomic1 atomic1.cpp -fsanitize=thread --std=c++17 -pthread -latomic -lglog && ./atomic1
# g++ -o atomic_time atomic_time.cpp -fsanitize=thread --std=c++17 -pthread -latomic -lglog && ./atomic_time
g++ -o atomic_time atomic_time.cpp --std=c++17 -pthread -latomic -lglog && ./atomic_time
