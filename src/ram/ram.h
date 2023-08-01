// ram/ram.h
#ifndef RAM_H
#define RAM_H

#include <thread>
#include <atomic>
#include <unordered_map>

class FSB;

class RAM
{
    std::unordered_map<uint64_t, uint8_t> mem;
    FSB *bus;
    std::thread listener_thread;
    std::atomic<bool> running;
    void listener();

    public:
        RAM(FSB*);
        ~RAM();
        void start();
        void stop();
        uint8_t read(uint64_t) const;
        void write(uint64_t, uint8_t);
};

#endif