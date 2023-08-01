// computer modules
// #include "boot/boot.cpp"
#include "bus/bus.h"
#include "cpu/cpu.h"
#include "ram/ram.h"
// functionality
#include <iostream>
#include <future>
#include <thread>
#include <bitset>
#include <chrono>
#include <iomanip>


void simple_test_for_ram_and_bus(FSB bus, RAM ram)
{
    uint64_t A = 0x0000000000000000;
    uint8_t D = 'a';

    ram.start();
    for (int i = 0; i < 3; i++)
    {
        std::cout 
            << "address:\t0x" << std::setfill('0') << std::setw(16) 
            << std::hex << A << std::endl;
        std::cout << "data (before):\t" << bus.get_data_lines() << std::endl;

        bus.set_address_lines(A);
        bus.set_data_lines(D);
        // writing {
        bus.reset_write();
        bus.reset_ready();

        bus.wait_ready(true);
        bus.set_write();
        // } writing

        A += 1;
        D += 1;

        // reading {
        bus.reset_read();
        bus.reset_ready();

        bus.wait_ready(true);
        bus.set_read();
        // } reading

        std::cout << "data (after):\t" << bus.get_data_lines() << std::endl;
        std::cout << std::endl;
    }
    ram.stop();
    // std::this_thread::sleep_for(std::chrono::seconds(1));
}


int main() 
{
    FSB bus;
    RAM ram(&bus);
    CPU cpu(&bus);

    ram.start();
    cpu.start();
    
    //

    cpu.stop();
    ram.stop();

    return 0;
}
