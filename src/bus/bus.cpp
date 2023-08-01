// bus/bus.cpp
#include "bus/bus.h"

FSB::FSB()
{
    ready_state = true;
    low_read.set();
    low_write.set();
}

uint64_t FSB::get_address_lines()
{
    return address_lines;
}
bool FSB::set_address_lines(uint64_t address)
{
    address_lines = address;
    return true;
}

uint8_t FSB::get_data_lines()
{
    return data_lines;
}
bool FSB::set_data_lines(uint8_t data)
{
    data_lines = data;
    return true;
}

bool FSB::reset_ready()
{
    std::lock_guard<std::mutex> lock_in_reset(mutex);
    ready_state = false;
    ready.notify_all();
    return true;
}
bool FSB::set_ready()
{
    std::lock_guard<std::mutex> lock_in_set(mutex);
    ready_state = true;
    ready.notify_all();
    return true;
}
void FSB::wait_ready(bool desired_state)
{
    std::unique_lock<std::mutex> lock_in_wait(mutex);
    ready.wait(lock_in_wait, [this, desired_state] { return ready_state == desired_state; });
}

std::bitset<1> FSB::get_read()
{
    return low_read;
}
bool FSB::set_read()
{
    low_read.set();
    return true;
}
bool FSB::reset_read()
{
    low_read.reset();
    return true;
}

std::bitset<1> FSB::get_write()
{
    return low_write;
}
bool FSB::set_write()
{
    low_write.set();
    return true;
}
bool FSB::reset_write()
{
    low_write.reset();
    return true;
}