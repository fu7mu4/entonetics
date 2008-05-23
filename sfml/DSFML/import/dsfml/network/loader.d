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

module dsfml.network.loader;

import dsfml.network.external;

import dsfml.system.dllloader;


version (Windows)
{
    const char[] LIBNAME = "csfml-network.dll";
}
version (linux)
{
    const char[] LIBNAME = "libcsfml-network.so.1";
}

DLLloader s_lib;

void init()
{
    s_lib = DLLloader.load(LIBNAME);

    //ipadress.d
    sfIPAddress_FromBytes = cast(pf_sfIPAddress_FromBytes)s_lib.getSymbol("sfIPAddress_FromBytes");
    sfIPAddress_FromString = cast(pf_sfIPAddress_FromString)s_lib.getSymbol("sfIPAddress_FromString");
    sfIPAddress_GetLocalAddress = cast(pf_sfIPAddress_GetLocalAddress)s_lib.getSymbol("sfIPAddress_GetLocalAddress");
    sfIPAddress_GetPublicAddress = cast(pf_sfIPAddress_GetPublicAddress)s_lib.getSymbol("sfIPAddress_GetPublicAddress");
    sfIPAddress_IsValid = cast(pf_sfIPAddress_IsValid)s_lib.getSymbol("sfIPAddress_IsValid");
    sfIPAddress_LocalHost = cast(pf_sfIPAddress_LocalHost)s_lib.getSymbol("sfIPAddress_LocalHost");
    sfIPAddress_ToString = cast(pf_sfIPAddress_ToString)s_lib.getSymbol("sfIPAddress_ToString");
    
    //packet.d
    sfPacket_Append = cast(pf_sfPacket_Append)s_lib.getSymbol("sfPacket_Append");
    sfPacket_CanRead = cast(pf_sfPacket_CanRead)s_lib.getSymbol("sfPacket_CanRead");
    sfPacket_Clear = cast(pf_sfPacket_Clear)s_lib.getSymbol("sfPacket_Clear");
    sfPacket_Create = cast(pf_sfPacket_Create)s_lib.getSymbol("sfPacket_Create");
    sfPacket_Destroy = cast(pf_sfPacket_Destroy)s_lib.getSymbol("sfPacket_Destroy");
    sfPacket_GetData = cast(pf_sfPacket_GetData)s_lib.getSymbol("sfPacket_GetData");
    sfPacket_GetDataSize = cast(pf_sfPacket_GetDataSize)s_lib.getSymbol("sfPacket_GetDataSize");
    sfPacket_ReadDouble = cast(pf_sfPacket_ReadDouble)s_lib.getSymbol("sfPacket_ReadDouble");
    sfPacket_ReadFloat = cast(pf_sfPacket_ReadFloat)s_lib.getSymbol("sfPacket_ReadFloat");
    sfPacket_ReadInt16 = cast(pf_sfPacket_ReadInt16)s_lib.getSymbol("sfPacket_ReadInt16");
    sfPacket_ReadInt32 = cast(pf_sfPacket_ReadInt32)s_lib.getSymbol("sfPacket_ReadInt32");
    sfPacket_ReadInt8 = cast(pf_sfPacket_ReadInt8)s_lib.getSymbol("sfPacket_ReadInt8");
    sfPacket_ReadString = cast(pf_sfPacket_ReadString)s_lib.getSymbol("sfPacket_ReadString");
    sfPacket_ReadWideString = cast(pf_sfPacket_ReadWideString)s_lib.getSymbol("sfPacket_ReadWideString");
    sfPacket_ReadUint16 = cast(pf_sfPacket_ReadUint16)s_lib.getSymbol("sfPacket_ReadUint16");
    sfPacket_ReadUint32 = cast(pf_sfPacket_ReadUint32)s_lib.getSymbol("sfPacket_ReadUint32");
    sfPacket_ReadUint8 = cast(pf_sfPacket_ReadUint8)s_lib.getSymbol("sfPacket_ReadUint8");
    sfPacket_WriteDouble = cast(pf_sfPacket_WriteDouble)s_lib.getSymbol("sfPacket_WriteDouble");
    sfPacket_WriteFloat = cast(pf_sfPacket_WriteFloat)s_lib.getSymbol("sfPacket_WriteFloat");
    sfPacket_WriteInt16 = cast(pf_sfPacket_WriteInt16)s_lib.getSymbol("sfPacket_WriteInt16");
    sfPacket_WriteInt32 = cast(pf_sfPacket_WriteInt32)s_lib.getSymbol("sfPacket_WriteInt32");
    sfPacket_WriteInt8 = cast(pf_sfPacket_WriteInt8)s_lib.getSymbol("sfPacket_WriteInt8");
    sfPacket_WriteString = cast(pf_sfPacket_WriteString)s_lib.getSymbol("sfPacket_WriteString");
    sfPacket_WriteWideString = cast(pf_sfPacket_WriteWideString)s_lib.getSymbol("sfPacket_WriteWideString");
    sfPacket_WriteUint16 = cast(pf_sfPacket_WriteUint16)s_lib.getSymbol("sfPacket_WriteUint16");
    sfPacket_WriteUint32 = cast(pf_sfPacket_WriteUint32)s_lib.getSymbol("sfPacket_WriteUint32");
    sfPacket_WriteUint8 = cast(pf_sfPacket_WriteUint8)s_lib.getSymbol("sfPacket_WriteUint8");
    
    //selector.d
    sfSelectorTCP_Add = cast(pf_sfSelectorTCP_Add)s_lib.getSymbol("sfSelectorTCP_Add");
    sfSelectorTCP_Clear = cast(pf_sfSelectorTCP_Clear)s_lib.getSymbol("sfSelectorTCP_Clear");
    sfSelectorTCP_Create = cast(pf_sfSelectorTCP_Create)s_lib.getSymbol("sfSelectorTCP_Create");
    sfSelectorTCP_Destroy = cast(pf_sfSelectorTCP_Destroy)s_lib.getSymbol("sfSelectorTCP_Destroy");
    sfSelectorTCP_GetSocketReady = cast(pf_sfSelectorTCP_GetSocketReady)s_lib.getSymbol("sfSelectorTCP_GetSocketReady");
    sfSelectorTCP_Wait = cast(pf_sfSelectorTCP_Wait)s_lib.getSymbol("sfSelectorTCP_Wait");
    sfSelectorTCP_Remove = cast(pf_sfSelectorTCP_Remove)s_lib.getSymbol("sfSelectorTCP_Remove");
    sfSelectorUDP_Add = cast(pf_sfSelectorUDP_Add)s_lib.getSymbol("sfSelectorUDP_Add");
    sfSelectorUDP_Clear = cast(pf_sfSelectorUDP_Clear)s_lib.getSymbol("sfSelectorUDP_Clear");
    sfSelectorUDP_Create = cast(pf_sfSelectorUDP_Create)s_lib.getSymbol("sfSelectorUDP_Create");
    sfSelectorUDP_Destroy = cast(pf_sfSelectorUDP_Destroy)s_lib.getSymbol("sfSelectorUDP_Destroy");
    sfSelectorUDP_GetSocketReady = cast(pf_sfSelectorUDP_GetSocketReady)s_lib.getSymbol("sfSelectorUDP_GetSocketReady");
    sfSelectorUDP_Wait = cast(pf_sfSelectorUDP_Wait)s_lib.getSymbol("sfSelectorUDP_Wait");
    sfSelectorUDP_Remove = cast(pf_sfSelectorUDP_Remove)s_lib.getSymbol("sfSelectorUDP_Remove");
    
    //sockettcp.d
    sfSocketTCP_Accept = cast(pf_sfSocketTCP_Accept)s_lib.getSymbol("sfSocketTCP_Accept");
    sfSocketTCP_Connect = cast(pf_sfSocketTCP_Connect)s_lib.getSymbol("sfSocketTCP_Connect");
    sfSocketTCP_Create = cast(pf_sfSocketTCP_Create)s_lib.getSymbol("sfSocketTCP_Create");
    sfSocketTCP_Destroy = cast(pf_sfSocketTCP_Destroy)s_lib.getSymbol("sfSocketTCP_Destroy");
    sfSocketTCP_IsValid = cast(pf_sfSocketTCP_IsValid)s_lib.getSymbol("sfSocketTCP_IsValid");
    sfSocketTCP_Listen = cast(pf_sfSocketTCP_Listen)s_lib.getSymbol("sfSocketTCP_Listen");
    sfSocketTCP_Receive = cast(pf_sfSocketTCP_Receive)s_lib.getSymbol("sfSocketTCP_Receive");
    sfSocketTCP_ReceivePacket = cast(pf_sfSocketTCP_ReceivePacket)s_lib.getSymbol("sfSocketTCP_ReceivePacket");
    sfSocketTCP_Send = cast(pf_sfSocketTCP_Send)s_lib.getSymbol("sfSocketTCP_Send");
    sfSocketTCP_SendPacket = cast(pf_sfSocketTCP_SendPacket)s_lib.getSymbol("sfSocketTCP_SendPacket");
    
    //socketudp.d
    sfSocketUDP_Bind = cast(pf_sfSocketUDP_Bind)s_lib.getSymbol("sfSocketUDP_Bind");
    sfSocketUDP_Create = cast(pf_sfSocketUDP_Create)s_lib.getSymbol("sfSocketUDP_Create");
    sfSocketUDP_Destroy = cast(pf_sfSocketUDP_Destroy)s_lib.getSymbol("sfSocketUDP_Destroy");
    sfSocketUDP_IsValid = cast(pf_sfSocketUDP_IsValid)s_lib.getSymbol("sfSocketUDP_IsValid");
    sfSocketUDP_Receive = cast(pf_sfSocketUDP_Receive)s_lib.getSymbol("sfSocketUDP_Receive");
    sfSocketUDP_ReceivePacket = cast(pf_sfSocketUDP_ReceivePacket)s_lib.getSymbol("sfSocketUDP_ReceivePacket");
    sfSocketUDP_Send = cast(pf_sfSocketUDP_Send)s_lib.getSymbol("sfSocketUDP_Send");
    sfSocketUDP_SendPacket = cast(pf_sfSocketUDP_SendPacket)s_lib.getSymbol("sfSocketUDP_SendPacket");
    sfSocketUDP_Unbind = cast(pf_sfSocketUDP_Unbind)s_lib.getSymbol("sfSocketUDP_Unbind");
}
