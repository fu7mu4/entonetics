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

module dsfml.network.selector;

import dsfml.network.external;
import dsfml.network.sockettcp;
import dsfml.network.socketudp;

import dsfml.system.pointerchecker;

/**
* Selector TCP allow reading from multiple sockets
* without blocking. It's a kind of multiplexer. Use SocketTCP or 
* SocketUDP aliases.
*/
class Selector(T)
{
    //Ensure type is correct
    static if (!is(T : SocketTCP) && !is(T : SocketUDP))
        static assert("Only SocketTCP and SocketUDP are valid for Selector.");
    
    //Alias functions
    static if (is (T : SocketTCP))
    {
        alias sfSelectorTCP* SELECTORTYPE;
        alias sfSocketTCP BASETYPE;
        alias sfSelectorTCP_Create sfSelector_Create;
        alias sfSelectorTCP_Destroy sfSelector_Destroy;
        alias sfSelectorTCP_Add sfSelector_Add;
        alias sfSelectorTCP_Remove sfSelector_Remove;
        alias sfSelectorTCP_Clear sfSelector_Clear;
        alias sfSelectorTCP_GetSocketReady sfSelector_GetSocketReady;
        alias sfSelectorTCP_Wait sfSelector_Wait;
    }
    static if (is(T : SocketUDP))
    {
        alias sfSelectorUDP* SELECTORTYPE;
        alias sfSocketUDP BASETYPE;
        alias sfSelectorUDP_Create sfSelector_Create;
        alias sfSelectorUDP_Destroy sfSelector_Destroy;
        alias sfSelectorUDP_Add sfSelector_Add;
        alias sfSelectorUDP_Remove sfSelector_Remove;
        alias sfSelectorUDP_Clear sfSelector_Clear;
        alias sfSelectorUDP_GetSocketReady sfSelector_GetSocketReady;
        alias sfSelectorUDP_Wait sfSelector_Wait;
    }
    
    /**
    *   Default constructor
    */        
    this()
    {
        m_selector = sfSelector_Create();
    }
    
    /**
    *   Destructor
    */        
    ~this()
    {
        sfSelector_Destroy(m_selector);
    }
    
    /**
    *   Add a socket to watch
    *   
    *   Params:
    *       socket = A tcp or udp socket            
    */        
    void add(T socket)
    {
        sfSelector_Add(m_selector, socket.toCSocket());
        m_watchedSockets[socket.toCSocket()] = socket;
        m_numSocketsWatched++;
    }
    
    /**
    *   Remove a previously added socket
    *   
    *   Params:
    *       socket = A tcp or udp socket                 
    */        
    void remove(T socket)
    {
        sfSelector_Remove(m_selector, socket.toCSocket());
        m_watchedSockets.remove(socket.toCSocket());
        m_numSocketsWatched--;
    }
    
    /**
    *   Clear all sockets being watched
    */        
    void clear()
    {
        sfSelector_Clear(m_selector);
        BASETYPE*[] keys = m_watchedSockets.keys;
        foreach(BASETYPE* key; keys)
            m_watchedSockets.remove(key);
        m_numSocketsWatched = 0;
    }
    
    /**
    *   Wait and collect sockets which are ready for reading.
    *   This functions will return either when at least one socket
    *   is ready, or when the given time is out
    *
    *   Params: 
    *       Selector = Selector to check
    *       Timeout = Maximum time to wait, in seconds (0 to disable timeout)
    *
    *   Returns: 
    *       Number of sockets ready
    */
    uint wait(float timeout = 0.f)
    {
        return sfSelector_Wait(m_selector, timeout);
    }
    
    /**
    *   After a call to Wait(), get the Index-th socket which is
    *   ready for reading. The total number of sockets ready
    *   is the integer returned by the previous call to Wait()
    *
    *   Params:
    *       Selector = Selector to check
    *       Index = Index of the socket to get
    *
    *   Returns:
    *       The Index-th socket
    */
    T GetSocketsReady(uint index)
    {
        return m_watchedSockets[sfSelector_GetSocketReady(m_selector, index)];
    }
    

private: 
    SELECTORTYPE m_selector;
    size_t m_numSocketsWatched;
    T[BASETYPE*] m_watchedSockets;
    
    mixin TEnforcePointer!(m_selector);
}

/**
*   Specializations of selector for TCP or UDP Socket. 
*/
alias Selector!(SocketTCP) SelectorTCP;
/// ditto
alias Selector!(SocketUDP) SelectorUDP;

