// bus/bus.h
#ifndef FSB_H
#define FSB_H

#include <bitset>
#include <mutex>
#include <condition_variable>

class FSB
{
    // wires
    uint64_t address_lines;
    uint8_t data_lines;
    std::bitset<1> low_read, low_write;
    std::bitset<8> low_byte_enable;

    std::condition_variable ready;
    std::mutex mutex;
    bool ready_state;

    public:
        FSB();
        
        uint64_t get_address_lines();
        bool set_address_lines(uint64_t);
        
        uint8_t get_data_lines();
        bool set_data_lines(uint8_t);
        
        bool reset_ready();
        bool set_ready();
        void wait_ready(bool);

        std::bitset<1> get_read();
        bool reset_read();
        bool set_read();

        std::bitset<1> get_write();
        bool reset_write();
        bool set_write();
};



#endif