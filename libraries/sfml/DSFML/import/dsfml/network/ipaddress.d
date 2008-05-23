/*
*   
*   
*   This file is part of DSFML
*
*   This software is provided 'as-is', without any express or
*   implied warranty. In no event will the authors be held
*   liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose,
*   including commercial applications, and to alter it and redistribute
*   it freely, subject to the following restrictions:
*
*   1.  The origin of this software must not be misrepresented;
*       you must not claim that you wrote the original software.
*       If you use this software in a product, an acknowledgment
*       in the product documentation would be appreciated but
*       is not required.
*
*   2.  Altered source versions must be plainly marked as such,
*       and must not be misrepresented as being the original software.
*
*   3.  This notice may not be removed or altered from any
*       source distribution.
*/

module dsfml.network.ipaddress;

import dsfml.network.external;

import dsfml.system.stringutil;

/**
*   IPAddress provides easy manipulation of IP v4 addresses
*/
class IPAddress
{
    this()
    {
        m_address = sfIPAddress_FromBytes(0, 0, 0, 0);
    }

    /**
    *   Construct the address from a string
    *
    *   Params: 
    *       address = IP address ("xxx.xxx.xxx.xxx") or network name
    *
    */
    this(char[] address)
    {
        m_address = sfIPAddress_FromString(toStringz(address));
    }


    /**
    *   Construct the address from 4 bytes
    *
    *   Params:
    *       byte0 = First byte of the address
    *       byte1 = Second byte of the address
    *       byte2 = Third byte of the address
    *       byte3 = Fourth byte of the address
    *
    */
    this(ubyte byte0, ubyte byte1, ubyte byte2, ubyte byte3)
    {
        m_address = sfIPAddress_FromBytes(byte0, byte1, byte2, byte3);
    }

    /**
    *   Tell if the address is a valid one
    *
    *   Returns: 
    *       True if address has a valid syntax
    *
    */
    bool isValid()
    {
        return sfIPAddress_IsValid(m_address);
    }

    /**
    *   Get a string representation of the address
    *
    *   Returns: 
    *       String representation of the IP address ("xxx.xxx.xxx.xxx")
    *
    */
    char[] toString() 
    {
        return m_address.Address.dup;
    }
    
    /**
    *   Get the computer's local IP address (from the LAN point of view)
    *
    *   Returns: 
    *       Local IP address
    *
    */
    static IPAddress getLocalAddress()
    {
        IPAddress address = new IPAddress();
        address.m_address = sfIPAddress_GetLocalAddress();
        return address;
    }

    /**
    *   Get the computer's public IP address (from the web point of view).
    *   The only way to get a public address is to ask it to a
    *   distant website ; as a consequence, this function may be
    *   very slow -- use it as few as possible !
    *
    *   Returns: 
    *         Public IP address
    *
    */
    static IPAddress getPublicAddress()
    {
        IPAddress address = new IPAddress;
        address.m_address = sfIPAddress_GetPublicAddress();
        return address;
    }

    bool opEqual(IPAddress other) 
    {
        return m_address.Address == other.m_address.Address;
    }

    sfIPAddress toCAddress()
    {
        return m_address;
    }

    /**
    *   Local host address (to connect to the same computer). 
    */   
    static IPAddress LOCALHOST()
    {
        if (s_LOCALHOST is null)
        {
            s_LOCALHOST = new IPAddress("127.0.0.1");
        }
        return s_LOCALHOST;
    }

package:
    void setCAddress(sfIPAddress adr)
    {
        m_address = adr;
    }

private:
    sfIPAddress m_address;
    static IPAddress s_LOCALHOST;
}
