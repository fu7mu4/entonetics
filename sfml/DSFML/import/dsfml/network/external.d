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

module dsfml.network.external;

import dsfml.network.socketstatus;

version(Dynamic)
{
    extern(C)
    {
        ////////////////////////////////////////////////////////////
        //ipaddress.d
        ////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////////
        /// sfIPAddress provides easy manipulation of IP v4 addresses
        ////////////////////////////////////////////////////////////
        struct sfIPAddress
        {
            char Address[16];
        }
    
    	typedef sfIPAddress function(char*) pf_sfIPAddress_FromString;
    	typedef sfIPAddress function(ubyte, ubyte, ubyte, ubyte) pf_sfIPAddress_FromBytes;
    	typedef bool function(sfIPAddress) pf_sfIPAddress_IsValid;
    	typedef void function(sfIPAddress, char*) pf_sfIPAddress_ToString;
    	typedef sfIPAddress function() pf_sfIPAddress_GetLocalAddress;
    	typedef sfIPAddress function() pf_sfIPAddress_GetPublicAddress;
    	typedef sfIPAddress function() pf_sfIPAddress_LocalHost;
    
    	pf_sfIPAddress_FromString sfIPAddress_FromString;
    	pf_sfIPAddress_FromBytes sfIPAddress_FromBytes;
    	pf_sfIPAddress_IsValid sfIPAddress_IsValid;
    	pf_sfIPAddress_ToString sfIPAddress_ToString;
    	pf_sfIPAddress_GetLocalAddress sfIPAddress_GetLocalAddress;
    	pf_sfIPAddress_GetPublicAddress sfIPAddress_GetPublicAddress;
    	pf_sfIPAddress_LocalHost sfIPAddress_LocalHost;



        ////////////////////////////////////////////////////////////
        //packet.d
        ////////////////////////////////////////////////////////////
        
        struct sfPacket {};

    	typedef sfPacket* function() pf_sfPacket_Create;
    	typedef void function(sfPacket*) pf_sfPacket_Destroy;
    	typedef void function(sfPacket*, void*, size_t) pf_sfPacket_Append;
    	typedef void function(sfPacket*) pf_sfPacket_Clear;
    	typedef byte* function(sfPacket*) pf_sfPacket_GetData;
    	typedef uint function(sfPacket*) pf_sfPacket_GetDataSize;
    	typedef bool function(sfPacket*) pf_sfPacket_CanRead;
    	typedef byte function(sfPacket*) pf_sfPacket_ReadInt8;
    	typedef ubyte function(sfPacket*) pf_sfPacket_ReadUint8;
    	typedef short function(sfPacket*) pf_sfPacket_ReadInt16;
    	typedef ushort function(sfPacket*) pf_sfPacket_ReadUint16;
    	typedef int function(sfPacket*) pf_sfPacket_ReadInt32;
    	typedef uint function(sfPacket*) pf_sfPacket_ReadUint32;
    	typedef float function(sfPacket*) pf_sfPacket_ReadFloat;
    	typedef double function(sfPacket*) pf_sfPacket_ReadDouble;
    	typedef void function(sfPacket*, char*) pf_sfPacket_ReadString;
    	typedef void function(sfPacket*, wchar*) pf_sfPacket_ReadWideString;
    	typedef void function(sfPacket*, byte) pf_sfPacket_WriteInt8;
    	typedef void function(sfPacket*, ubyte) pf_sfPacket_WriteUint8;
    	typedef void function(sfPacket*, short) pf_sfPacket_WriteInt16;
    	typedef void function(sfPacket*, ushort) pf_sfPacket_WriteUint16;
    	typedef void function(sfPacket*, int) pf_sfPacket_WriteInt32;
    	typedef void function(sfPacket*, uint) pf_sfPacket_WriteUint32;
    	typedef void function(sfPacket*, float) pf_sfPacket_WriteFloat;
    	typedef void function(sfPacket*, double) pf_sfPacket_WriteDouble;
    	typedef void function(sfPacket*, char*) pf_sfPacket_WriteString;
    	typedef void function(sfPacket*, wchar*) pf_sfPacket_WriteWideString;
    
    	pf_sfPacket_Create sfPacket_Create;
    	pf_sfPacket_Destroy sfPacket_Destroy;
    	pf_sfPacket_Append sfPacket_Append;
    	pf_sfPacket_Clear sfPacket_Clear;
    	pf_sfPacket_GetData sfPacket_GetData;
    	pf_sfPacket_GetDataSize sfPacket_GetDataSize;
    	pf_sfPacket_CanRead sfPacket_CanRead;
    	pf_sfPacket_ReadInt8 sfPacket_ReadInt8;
    	pf_sfPacket_ReadUint8 sfPacket_ReadUint8;
    	pf_sfPacket_ReadInt16 sfPacket_ReadInt16;
    	pf_sfPacket_ReadUint16 sfPacket_ReadUint16;
    	pf_sfPacket_ReadInt32 sfPacket_ReadInt32;
    	pf_sfPacket_ReadUint32 sfPacket_ReadUint32;
    	pf_sfPacket_ReadFloat sfPacket_ReadFloat;
    	pf_sfPacket_ReadDouble sfPacket_ReadDouble;
    	pf_sfPacket_ReadString sfPacket_ReadString;
    	pf_sfPacket_ReadWideString sfPacket_ReadWideString;
    	pf_sfPacket_WriteInt8 sfPacket_WriteInt8;
    	pf_sfPacket_WriteUint8 sfPacket_WriteUint8;
    	pf_sfPacket_WriteInt16 sfPacket_WriteInt16;
    	pf_sfPacket_WriteUint16 sfPacket_WriteUint16;
    	pf_sfPacket_WriteInt32 sfPacket_WriteInt32;
    	pf_sfPacket_WriteUint32 sfPacket_WriteUint32;
    	pf_sfPacket_WriteFloat sfPacket_WriteFloat;
    	pf_sfPacket_WriteDouble sfPacket_WriteDouble;
    	pf_sfPacket_WriteString sfPacket_WriteString;
    	pf_sfPacket_WriteWideString sfPacket_WriteWideString;





        ////////////////////////////////////////////////////////////
        //sockettcp.d
        ////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////////
        /// SocketTCP wraps a socket using TCP protocol to
        /// send data safely (but a bit slower)
        ////////////////////////////////////////////////////////////
        struct sfSocketTCP {};
        

    	typedef sfSocketTCP* function() pf_sfSocketTCP_Create;
    	typedef void function(sfSocketTCP*) pf_sfSocketTCP_Destroy;
    	typedef bool function(sfSocketTCP*, ushort, sfIPAddress) pf_sfSocketTCP_Connect;
    	typedef bool function(sfSocketTCP*, ushort) pf_sfSocketTCP_Listen;
    	typedef SocketStatus function(sfSocketTCP*, sfSocketTCP**, sfIPAddress*) pf_sfSocketTCP_Accept;
    	typedef SocketStatus function(sfSocketTCP*, byte*, size_t) pf_sfSocketTCP_Send;
    	typedef SocketStatus function(sfSocketTCP*, byte*, size_t, size_t*) pf_sfSocketTCP_Receive;
    	typedef SocketStatus function(sfSocketTCP*, sfPacket*) pf_sfSocketTCP_SendPacket;
    	typedef SocketStatus function(sfSocketTCP*, sfPacket*) pf_sfSocketTCP_ReceivePacket;
    	typedef bool function(sfSocketTCP*) pf_sfSocketTCP_IsValid;
    
    	pf_sfSocketTCP_Create sfSocketTCP_Create;
    	pf_sfSocketTCP_Destroy sfSocketTCP_Destroy;
    	pf_sfSocketTCP_Connect sfSocketTCP_Connect;
    	pf_sfSocketTCP_Listen sfSocketTCP_Listen;
    	pf_sfSocketTCP_Accept sfSocketTCP_Accept;
    	pf_sfSocketTCP_Send sfSocketTCP_Send;
    	pf_sfSocketTCP_Receive sfSocketTCP_Receive;
    	pf_sfSocketTCP_SendPacket sfSocketTCP_SendPacket;
    	pf_sfSocketTCP_ReceivePacket sfSocketTCP_ReceivePacket;
    	pf_sfSocketTCP_IsValid sfSocketTCP_IsValid;



        ////////////////////////////////////////////////////////////
        //socketudp.d
        ////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////////
        /// sfSocketUDP wraps a socket using UDP protocol to
        /// send data fastly (but with less safety)
        ////////////////////////////////////////////////////////////
        struct sfSocketUDP {};

    	typedef sfSocketUDP* function() pf_sfSocketUDP_Create;
    	typedef void function(sfSocketUDP*) pf_sfSocketUDP_Destroy;
    	typedef bool function(sfSocketUDP*, ushort) pf_sfSocketUDP_Bind;
    	typedef bool function(sfSocketUDP*, ushort) pf_sfSocketUDP_Unbind;
    	typedef SocketStatus function(sfSocketUDP*, byte*, size_t, sfIPAddress, ushort) pf_sfSocketUDP_Send;
    	typedef SocketStatus function(sfSocketUDP*, byte*, size_t, size_t*, sfIPAddress*) pf_sfSocketUDP_Receive;
    	typedef SocketStatus function(sfSocketUDP*, sfPacket*, sfIPAddress*, ushort) pf_sfSocketUDP_SendPacket;
    	typedef SocketStatus function(sfSocketUDP*, sfPacket*, sfIPAddress*) pf_sfSocketUDP_ReceivePacket;
    	typedef bool function(sfSocketUDP*) pf_sfSocketUDP_IsValid;
    
    	pf_sfSocketUDP_Create sfSocketUDP_Create;
    	pf_sfSocketUDP_Destroy sfSocketUDP_Destroy;
    	pf_sfSocketUDP_Bind sfSocketUDP_Bind;
    	pf_sfSocketUDP_Unbind sfSocketUDP_Unbind;
    	pf_sfSocketUDP_Send sfSocketUDP_Send;
    	pf_sfSocketUDP_Receive sfSocketUDP_Receive;
    	pf_sfSocketUDP_SendPacket sfSocketUDP_SendPacket;
    	pf_sfSocketUDP_ReceivePacket sfSocketUDP_ReceivePacket;
    	pf_sfSocketUDP_IsValid sfSocketUDP_IsValid;



        ////////////////////////////////////////////////////////////
        //selector.d
        ////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////////
        /// sfSelectorTCP and sfSelectorUDP allow reading from multiple sockets
        /// without blocking. It's a kind of multiplexer
        ////////////////////////////////////////////////////////////
        struct sfSelectorTCP {};
        
        struct sfSelectorUDP {};
        
    	typedef sfSelectorTCP* function() pf_sfSelectorTCP_Create;
    	typedef sfSelectorUDP* function() pf_sfSelectorUDP_Create;
    	typedef void function(sfSelectorTCP*) pf_sfSelectorTCP_Destroy;
    	typedef void function(sfSelectorUDP*) pf_sfSelectorUDP_Destroy;
    	typedef void function(sfSelectorTCP*, sfSocketTCP*) pf_sfSelectorTCP_Add;
    	typedef void function(sfSelectorUDP*, sfSocketUDP*) pf_sfSelectorUDP_Add;
    	typedef void function(sfSelectorTCP*, sfSocketTCP*) pf_sfSelectorTCP_Remove;
    	typedef void function(sfSelectorUDP*, sfSocketUDP*) pf_sfSelectorUDP_Remove;
    	typedef void function(sfSelectorTCP*) pf_sfSelectorTCP_Clear;
    	typedef void function(sfSelectorUDP*) pf_sfSelectorUDP_Clear;
    	typedef uint function(sfSelectorTCP*, float) pf_sfSelectorTCP_Wait;
    	typedef uint function(sfSelectorUDP*, float) pf_sfSelectorUDP_Wait;
    	typedef sfSocketTCP* function(sfSelectorTCP*, uint) pf_sfSelectorTCP_GetSocketReady;
    	typedef sfSocketUDP* function(sfSelectorUDP*, uint) pf_sfSelectorUDP_GetSocketReady;
    
    	pf_sfSelectorTCP_Create sfSelectorTCP_Create;
    	pf_sfSelectorUDP_Create sfSelectorUDP_Create;
    	pf_sfSelectorTCP_Destroy sfSelectorTCP_Destroy;
    	pf_sfSelectorUDP_Destroy sfSelectorUDP_Destroy;
    	pf_sfSelectorTCP_Add sfSelectorTCP_Add;
    	pf_sfSelectorUDP_Add sfSelectorUDP_Add;
    	pf_sfSelectorTCP_Remove sfSelectorTCP_Remove;
    	pf_sfSelectorUDP_Remove sfSelectorUDP_Remove;
    	pf_sfSelectorTCP_Clear sfSelectorTCP_Clear;
    	pf_sfSelectorUDP_Clear sfSelectorUDP_Clear;
    	pf_sfSelectorTCP_Wait sfSelectorTCP_Wait;
    	pf_sfSelectorUDP_Wait sfSelectorUDP_Wait;
    	pf_sfSelectorTCP_GetSocketReady sfSelectorTCP_GetSocketReady;
    	pf_sfSelectorUDP_GetSocketReady sfSelectorUDP_GetSocketReady;
    }
}
else
{
    extern(C)
    {
        //ipaddress.d
        struct sfIPAddress
        {
            char Address[16];
        }
    
        sfIPAddress sfIPAddress_FromString(char*);
        sfIPAddress sfIPAddress_FromBytes(ubyte, ubyte, ubyte, ubyte);
        bool sfIPAddress_IsValid(sfIPAddress);
        void sfIPAddress_ToString(sfIPAddress, char*);
        sfIPAddress sfIPAddress_GetLocalAddress();
        sfIPAddress sfIPAddress_GetPublicAddress();
        sfIPAddress sfIPAddress_LocalHost();
        
        //packet.d
        struct sfPacket {};
        
        sfPacket* sfPacket_Create();
        void sfPacket_Destroy(sfPacket*);
        void sfPacket_Append(sfPacket*, void*, size_t);
        void sfPacket_Clear(sfPacket*);
        byte* sfPacket_GetData(sfPacket*);
        uint sfPacket_GetDataSize(sfPacket*);
        bool sfPacket_CanRead(sfPacket*);
        byte sfPacket_ReadInt8(sfPacket*);
        ubyte sfPacket_ReadUint8(sfPacket*);
        short sfPacket_ReadInt16(sfPacket*);
        ushort sfPacket_ReadUint16(sfPacket*);
        int sfPacket_ReadInt32(sfPacket*);
        uint sfPacket_ReadUint32(sfPacket*);
        float sfPacket_ReadFloat(sfPacket*);
        double sfPacket_ReadDouble(sfPacket*);
        void sfPacket_ReadString(sfPacket*, char*);
        void sfPacket_ReadWideString(sfPacket*, wchar*);
        void sfPacket_WriteInt8(sfPacket*, byte);
        void sfPacket_WriteUint8(sfPacket*, ubyte);
        void sfPacket_WriteInt16(sfPacket*, short);
        void sfPacket_WriteUint16(sfPacket*, ushort);
        void sfPacket_WriteInt32(sfPacket*, int);
        void sfPacket_WriteUint32(sfPacket*, uint);
        void sfPacket_WriteFloat(sfPacket*, float);
        void sfPacket_WriteDouble(sfPacket*, double);
        void sfPacket_WriteString(sfPacket*, char*);
        void sfPacket_WriteWideString(sfPacket*, wchar*);
        
        //sockettcp.d
        struct sfSocketTCP {};
        
        sfSocketTCP* sfSocketTCP_Create();
        void sfSocketTCP_Destroy(sfSocketTCP*);
        bool sfSocketTCP_Connect(sfSocketTCP*, ushort, sfIPAddress);
        bool sfSocketTCP_Listen(sfSocketTCP*, ushort);
        SocketStatus sfSocketTCP_Accept(sfSocketTCP*, sfSocketTCP**, sfIPAddress*);
        SocketStatus sfSocketTCP_Send(sfSocketTCP*, byte*, size_t);
        SocketStatus sfSocketTCP_Receive(sfSocketTCP*, byte*, size_t, size_t*);
        SocketStatus sfSocketTCP_SendPacket(sfSocketTCP*, sfPacket*);
        SocketStatus sfSocketTCP_ReceivePacket(sfSocketTCP*, sfPacket*);
        bool sfSocketTCP_IsValid(sfSocketTCP*);
        
        //socketudp.d
        struct sfSocketUDP {};
    
        sfSocketUDP* sfSocketUDP_Create();
        void sfSocketUDP_Destroy(sfSocketUDP*);
        bool sfSocketUDP_Bind(sfSocketUDP*, ushort);
        bool sfSocketUDP_Unbind(sfSocketUDP*, ushort);
        SocketStatus sfSocketUDP_Send(sfSocketUDP*, byte*, size_t, sfIPAddress, ushort);
        SocketStatus sfSocketUDP_Receive(sfSocketUDP*, byte*, size_t, size_t*, sfIPAddress*);
        SocketStatus sfSocketUDP_SendPacket(sfSocketUDP*, sfPacket*, sfIPAddress*, ushort);
        SocketStatus sfSocketUDP_ReceivePacket(sfSocketUDP*, sfPacket*, sfIPAddress*);
        bool sfSocketUDP_IsValid(sfSocketUDP*);
        
        //selector.d
        struct sfSelectorTCP {};
        struct sfSelectorUDP {};
    
        sfSelectorTCP* sfSelectorTCP_Create();
        sfSelectorUDP* sfSelectorUDP_Create();
        void sfSelectorTCP_Destroy(sfSelectorTCP*);
        void sfSelectorUDP_Destroy(sfSelectorUDP*);
        void sfSelectorTCP_Add(sfSelectorTCP*, sfSocketTCP*);
        void sfSelectorUDP_Add(sfSelectorUDP*, sfSocketUDP*);
        void sfSelectorTCP_Remove(sfSelectorTCP*, sfSocketTCP*);
        void sfSelectorUDP_Remove(sfSelectorUDP*, sfSocketUDP*);
        void sfSelectorTCP_Clear(sfSelectorTCP*);
        void sfSelectorUDP_Clear(sfSelectorUDP*);
        sfSocketTCP* sfSelectorTCP_GetSocketReady(sfSelectorTCP*, uint);
        sfSocketUDP* sfSelectorUDP_GetSocketReady(sfSelectorUDP*, uint);
        uint sfSelectorTCP_Wait(sfSelectorTCP*, float);
        uint sfSelectorUDP_Wait(sfSelectorUDP*, float);
    }
}
