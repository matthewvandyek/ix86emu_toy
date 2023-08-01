// cpu/cpu.h
#ifndef CPU_H
#define CPU_H

#include <queue>
#include <array>
#include <bitset>
#include <thread>
#include <atomic>

class FSB;

class IBU
{
    // Instruction Boundary Unit
    std::queue<uint8_t> *prefetch_queue;
    public:
        // IBU(std::queue<uint8_t> *prefetch_queue) : prefetch_queue(prefetch_queue) {}
        std::vector<uint8_t> get_next_instruction_bytes();
};

class BIU
{
    FSB *bus;
    std::queue<uint8_t> prefetch_queue;
    uint64_t CS; // Code Segment register
    uint64_t IP; // Instruction Pointer register
    IBU ibu; // Instruction Boundary Unit

    public:
        BIU(FSB *bus) : bus(bus) {}
        void prefetch();
        uint8_t get_next_instruction();
};

class ALU
{
    public:
        uint64_t execute(uint8_t opcode, uint64_t operand1, uint64_t operand2);
};

class CU
{
    ALU alu;
    std::array<uint64_t, 16> general_purpose_registers;
    std::bitset<64> flags;

    public:
        std::pair<uint8_t, std::pair<uint64_t, uint64_t>> decode(uint8_t instruction);
        uint64_t execute(uint8_t opcode, uint64_t operand1, uint64_t operand2);
        uint64_t get_register(int index);
        void set_register(int index, uint64_t value);
};

class EU
{
    CU cu;

    public:
        EU(CU cu) : cu(cu) {}
        void execute_cycle();
};

class CPU
{
    FSB *bus;
    BIU biu;
    EU eu;
    std::thread biu_thread;
    std::thread eu_thread;
    std::atomic<bool> running;

    public:
        // CPU(FSB *bus);
        CPU(FSB *bus) : bus(bus), biu(BIU(bus)), eu(EU(CU())), running(false) {}
        void start();
        void stop();
};

#endif
