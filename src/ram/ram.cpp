// ram/ram.cpp
#include "ram/ram.h"
#include "bus/bus.h"
#include <iostream>
#include <chrono>
#include <thread>

RAM::RAM(FSB *bus) : bus(bus), running(false)
{
}

RAM::~RAM()
{
    // make sure listener thread is stopped at destruction
    if (running) stop();
    bus->set_ready();
}

uint8_t RAM::read(uint64_t address) const 
{
    auto it = mem.find(address);
    if (it != mem.end()) return it->second;
    return 0;
}

void RAM::write(uint64_t address, uint8_t value)
{
    mem[address] = value;
}

void RAM::start()
{
    running = true;
    listener_thread = std::thread(&RAM::listener, this);
}

void RAM::stop()
{
    running = false;
    bus->reset_ready();
    if(listener_thread.joinable()) listener_thread.join();
}

void RAM::listener()
{
    while (true)
    {
        if (!running) break;
        bus->wait_ready(false);
        uint64_t address = bus->get_address_lines();
        if ((address >= 0x0000000000000000 && address <= 0x00007FFFFFFFFFFF) ||
            (address >= 0xFFFF800000000000 && address <= 0xFFFFFFFFFFFFFFFF))
        {
            if (bus->get_read().none()) bus->set_data_lines(read(address));
            else if (bus->get_write().none()) write(address, bus->get_data_lines());
        }
        bus->set_ready();
    }
}