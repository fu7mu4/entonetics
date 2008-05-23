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

module dsfml.network.sockettcp;

import dsfml.network.external;
import dsfml.network.ipaddress;
import dsfml.network.packet;
import dsfml.network.socketstatus;

import dsfml.system.pointerchecker;

/**
*   SocketTCP wraps a socket using TCP protocol to send data safely (but a bit slower)
*/
class SocketTCP
{
    /**
    *   Default constructor
    */
    this()
    {
        m_Socket = sfSocketTCP_Create();
    }

    /**
    *   Destructor
    */
    ~this()
    {
        sfSocketTCP_Destroy(m_Socket);
    }

    /**
    *   Connect to another computer on a specified port
    *
    *   Params: 
    *       port = Port to use for transfers (warning : ports < 1024 are reserved)
    *       hostAddress = IP Address of the host to connect to
    *
    *   Returns: 
    *       True if operation has been successful
    */
    bool connect(ushort port, IPAddress hostAddress)
    {
        return cast(bool) sfSocketTCP_Connect(m_Socket, port, hostAddress.toCAddress());
    }

    /**
    *   Connect to another computer on a specified port
    *
    *   Params: 
    *       port = Port to use for transfers (warning : ports < 1024 are reserved)
    *       iP = string of the IP Address
    *
    *   Returns: 
    *       True if operation has been successful
    */

    bool connect(ushort port, char[] IP)
    {
        return connect(port, new IPAddress(IP));
    }

    /**
    *   Listen to a specified port for incoming data or connections
    *
    *   Params: 
    *       port = Port to listen to
    *
    *   Returns: 
    *       True if operation has been successful
    */
    bool listen(ushort port)
    {
        return sfSocketTCP_Listen(m_Socket, port);
    }

    /**
    *   Wait for a connection (must be listening to a port).
    *   This function is blocking.
    *
    *   Params: 
    *       connected = Socket containing the connection with the connected client
    *       address = Pointer to an address to fill with client infos (NULL by default)
    *
    *   Returns: 
    *       Status code
    */
    SocketStatus accept(SocketTCP connected, IPAddress address = null)
    {
        sfSocketTCP* temp = null;
        sfIPAddress adr;
        SocketStatus ret = sfSocketTCP_Accept(m_Socket, &temp, address is null ? null : &(adr));
        connected.m_Socket = temp;
        if (address !is null)
            address.setCAddress(adr);
        return ret;
    }

    /**
    *   Send an array of bytes to the host (must be connected first)
    *
    *   Params: 
    *       data = Pointer to the bytes to send
    *       size = Number of bytes to send
    *
    *   Returns: 
    *       Status code
    */
    SocketStatus send(byte* data, size_t size)
    {
        return cast(SocketStatus)sfSocketTCP_Send(m_Socket, data, size);
    }

    /**
    *   Receive an array of bytes from the host (must be connected first).
    *   This function will block until a connection was accepted
    *
    *   Params: 
    *       data = Pointer to a byte array to fill (make sure it is big enough)
    *       maxSize = Maximum number of bytes to read
    *       sizeReceived = Number of bytes received
    *
    *   Returns: 
    *       Status code
    *
    */
    SocketStatus receive(byte* data, size_t maxSize, out size_t sizeReceived)
    {
        return cast(SocketStatus)sfSocketTCP_Receive(m_Socket, data, maxSize, &sizeReceived);
    }


    /**
    *   Send a packet of data to the host (must be connected first)
    *
    *   Params: 
    *       packetToSend = Packet to send
    *
    *   Returns: 
    *       Status code
    *
    */
    SocketStatus send(Packet packetToSend)
    {
        return cast(SocketStatus)sfSocketTCP_SendPacket(m_Socket, packetToSend.toCPacket());
    }

    /**
    *   Receive a packet from the host (must be connected first).
    *   This function will block if the socket is blocking
    *
    *   Params: 
    *       packetToReceive = Packet to fill with received data
    *
    *   Returns: 
    *       Status code
    *
    */
    SocketStatus receive(Packet packetToReceive)
    {
        return cast(SocketStatus)sfSocketTCP_ReceivePacket(m_Socket, packetToReceive.toCPacket());
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
        return sfSocketTCP_IsValid(m_Socket);
    }

    bool opEquals(SocketTCP other) 
    {
        return (other.toCSocket() == this.toCSocket());
    }


package:

    this (sfSocketTCP* ptr)
    {
        m_Socket = ptr;
    }

    sfSocketTCP* toCSocket() 
    {
        return m_Socket;
    }

private:
    sfSocketTCP* m_Socket;
    mixin TEnforcePointer!(m_Socket);
}
