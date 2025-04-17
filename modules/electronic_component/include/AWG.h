/**
 * @file AWG.h
 * @author
 * HUANG He (he.huang.intern@3ds.com)
 * @brief
 * American Wire Gauge (AWG) class
 * Mimics the traditional enum class while adding checks for value
 * @version 1.0
 * @date 2025-04-17     
 * @copyright
 * Dassault Systemes 2025   
 * 
 */
#include <stdexcept>

class AWG
{
public:

    enum awg_values : int 
    {
        AWGUnkown = -1,
        AWG8  = 8,
        AWG10 = 10,
        AWG12 = 12,
        AWG16 = 16,
        AWG20 = 20, 
        AWG22 = 22
    };

    // Default constructor set attributes to unknown.
    constexpr AWG() : _value(awg_values::AWGUnkown) {}
    // Constructor with enum value.
    constexpr AWG(awg_values gauge) : _value(gauge) {}

    // Constructor with int value, if the value is not in the enum, set to unknown.
    explicit constexpr AWG(int gauge) : 
        _value(is_valid(gauge) ? static_cast<awg_values>(gauge) : awg_values::AWGUnkown) {}

    // Allow switch(AWG) directly and prevent if(AWG).
    constexpr operator awg_values() const { return _value; }
    explicit  operator bool()       const = delete;
    
    // Allow comparison with int8_t
    constexpr bool operator==(AWG& other) const { return _value == other._value; }
    constexpr bool operator!=(AWG& other) const { return _value != other._value; }

private:

    // value
    awg_values _value;


    //tools
    constexpr bool is_valid(int gauge) const
    {
        return gauge == 8  || gauge == 10 || gauge == 12 ||
               gauge == 16 || gauge == 20 || gauge == 22;
    }
    
};