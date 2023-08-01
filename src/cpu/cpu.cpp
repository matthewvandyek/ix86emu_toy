// cpu/cpu.cpp
#include "cpu/cpu.h"
#include "bus/bus.h"

// CPU::CPU(FSB *bus) : bus(bus), biu(BIU(bus)), eu(EU(CU())), running(false) {}


void CPU::start()
{
    running = true;

    biu_thread = std::thread([this] {
        while (running) {
            // biu.fetch_instruction();
            return;
        }
    });

    eu_thread = std::thread([this] {
        while (running) {
            // eu.execute_cycle();
            return;
        }
    });
}

void CPU::stop()
{
    running = false;

    if (biu_thread.joinable()) {
        biu_thread.join();
    }

    if (eu_thread.joinable()) {
        eu_thread.join();
    }
}
