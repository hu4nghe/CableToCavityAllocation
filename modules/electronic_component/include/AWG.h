/**
 * @file AWG.h
 * @author
 * HUANG He (he.huang.intern@3ds.com)
 * @brief
 * American Wire Gauge (AWG) class
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

class AWG
{
public :

    enum awg_values : int 
    {
        AWGUnknown = -1,
        AWG8  = 8,
        AWG10 = 10,
        AWG12 = 12,
        AWG16 = 16,
        AWG20 = 20, 
        AWG22 = 22
    };

    /**
     * @brief 
     * Default constructor set attributes to unknown.
     */
    constexpr AWG() : _value(awg_values::AWGUnknown) {}

    /**
     * @brief 
     * Constructor with enum value.
     * 
     */
    constexpr AWG(awg_values gauge) : _value(gauge) {}

    /**
     * @brief 
     * Constructor with integer, if the integer is invalid, set value to unknown.
     */
    explicit constexpr AWG(int gauge) : 
        _value(is_valid(gauge) ? static_cast<awg_values>(gauge) : awg_values::AWGUnknown) {}

    /**
     * @brief 
     * Allow switch(AWG)
     * 
     * @return awg_values Enum value
     */
    constexpr operator awg_values() const { return _value; }

    /**
     * @brief 
     * Prevent if (AWG) operattion.
     * 
     */
    explicit  operator bool()       const = delete;
    
    /**
     * @brief 
     * Operator== which allows comparaison.
     * 
     * @param other Another AWG enum object
     * @return true If they are equal.
     * @return false If they are not equal.
     */
    constexpr bool operator==(const AWG& other) const { return _value == other._value; }

    /**
     * @brief 
     * Operator!= which allows comparaison.
     * 
     * @param other Another AWG enum object
     * @return true If they are not equal.
     * @return false If they are equal.
     */
    constexpr bool operator!=(const AWG& other) const { return _value != other._value; }

private :

    awg_values _value;

    /**
     * @brief 
     * Tool function to check the validity at initialization.
     * 
     * @param gauge Gauge value.
     * @return true If the value is a valid AWG.
     * @return false If the value is not a valid AWG.
     */
    constexpr bool is_valid(int gauge) const
    {
        return gauge == 8  || gauge == 10 || gauge == 12 ||
               gauge == 16 || gauge == 20 || gauge == 22;
    }
    
};