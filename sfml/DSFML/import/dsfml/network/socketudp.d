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

module dsfml.network.socketudp;

import dsfml.network.external;
import dsfml.network.ipaddress;
import dsfml.network.packet;
import dsfml.network.socketstatus;

import dsfml.system.pointerchecker;

/**
*   SocketUDP wraps a socket using UDP protocol to
*   send data fastly (but with less safety)
*/
class SocketUDP
{
    /**
    *   Default constructor
    */
    this()
	{
		m_Socket = sfSocketUDP_Create();
		m_Port = 0;
	}

    /**
    *   Destructor
    */
    ~this()
	{
		sfSocketUDP_Destroy(m_Socket);
	}

    /**
    *   Bind the socket to a specific port
    *
    *   Params: 
    *       port = Port to bind the socket to
    *
    *   Returns: 
    *       True if operation has been successful
    *
    */
    bool bind(ushort port)
	{
		m_Port = port;
		return sfSocketUDP_Bind(m_Socket, port);
	}

    /**
    *   Unbind the socket from its previous port, if any
    *
    *   Returns: True if operation has been successful
    *
    */
    bool unbind()
	{
		m_Port = 0;
		return sfSocketUDP_Unbind(m_Socket, m_Port);
	}

    /**
    *   Send an array of bytes
    *
    *   Params: 
    *       data = Pointer to the bytes to send
    *       size = Number of bytes to send
    *       address = Address of the computer to send the packet to
    *       port = Port to send the data to
    *
    *   Returns: 
    *       Status code
    *
    */
    SocketStatus send(byte* data, size_t size, IPAddress address, ushort port)
	{
		return cast(SocketStatus) sfSocketUDP_Send(m_Socket, data, size, address.toCAddress(), port);
	}

    /**
    *   Receive an array of bytes.
    *   This function is blocking.
    *
    *   Params: 
    *       data = Pointer to a byte array to fill (make sure it is big enough)
    *       maxSize = Maximum number of bytes to read
    *       sizeReceived = Number of bytes received
    *       address = Address of the computer which sent the data
    *
    *   Returns: 
    *       Status code
    *
    */
    SocketStatus receive(byte* data, size_t maxSize, ref size_t sizeReceived, IPAddress address)
	{
        sfIPAddress dumm_;
		SocketStatus ret = sfSocketUDP_Receive(m_Socket, data, maxSize, &sizeReceived, &dumm_);
		address.setCAddress(dumm_);
		return ret;
	}

    /**
    *   Send a packet of data
    *
    *   Params: 
    *       packetToSend = Packet to send
    *       address = Address of the computer to send the packet to
    *       port = Port to send the data to
    *
    *   Returns: 
    *       Status code
    *
    */
    SocketStatus send(Packet packetToSend, IPAddress address, ushort port)
	{
		return cast(SocketStatus)sfSocketUDP_SendPacket(m_Socket, packetToSend.toCPacket(), &(address.toCAddress()), port);
	}

    /**
    *   Receive a packet.
    *   This function is blocking.
    *
    *   Params: 
    *       packetToReceive = Packet to fill with received data
    *       address = Address of the computer which sent the packet
    *
    *   Returns: 
    *       Status code
    *
    */
    SocketStatus receive(Packet packetToReceive, IPAddress address)
	{
        sfIPAddress dumm_;
		SocketStatus ret = sfSocketUDP_ReceivePacket(m_Socket, packetToReceive.toCPacket(), &dumm_);
		address.setCAddress(dumm_);
		return ret;

	}

    /**
    *   Check if the socket is in a valid state ; this function
    *   can be called any time to check if the socket is OK
    *
    *   Returns: 
    *       True if the socket is valid
    *
    */
    bool isValid()
	{
		return cast(bool)sfSocketUDP_IsValid(m_Socket);
	}

    /**
    *   Get the port the socket is currently bound to
    *
    *   Returns: 
    *       Current port (0 means the socket is not bound)
    */
    ushort getPort()
	{
		return m_Port;
	}

    bool opEquals(SocketUDP other)
	{
		return (other.toCSocket() == this.toCSocket());
	}

package:
    this (sfSocketUDP* ptr)
    {
        m_Socket = ptr;
        m_Port = 0;
    }

    sfSocketUDP* toCSocket()
	{
		return m_Socket;
	}
   
private:
	sfSocketUDP* m_Socket;
	ushort m_Port;
	
	mixin TEnforcePointer!(m_Socket);
}
