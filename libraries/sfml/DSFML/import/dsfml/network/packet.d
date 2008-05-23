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

module dsfml.network.packet;

import dsfml.network.external;

import dsfml.system.pointerchecker;
import dsfml.system.stringutil;

/** 
*   Packet wraps data to send / to receive through the network
*   
*   The order of insertion and extraction must be the same.
*   
*   Litterals integer are promoted to int.
*   Litterals floating point are promoted to float.
*   
*   Extraction or insertion can be specified with explicit template.
*   Examples:
*   ------------------------------------------------------------
*   Packet p = new Packet();
*   
*   int i = 32, j = 42;
*   char[] k = hello;
*   
*   p.Set(i, k, j); //Set the data in the packet
*   
*   int a, b;
*   char[] c;
*   p.Get(a, c, b); //Get data from the packet
*   
*   //...
*   
*   Packet p = new Packet();
*   p.Set!(byte)(5); // Litteral are inserted with byte type
*   ------------------------------------------------------------
*   
*   See_Also:
*       $(LINK2 http://www.digitalmars.com/d/1.0/lex.html, D litterals Specification) for more informations.
*/
class Packet
{
    /**
    * Default constructor
    *
    */
    this()
	{
		m_Packet = sfPacket_Create();
	}

    /**
    * Virtual destructor
    *
    */
    ~this()
	{
		sfPacket_Destroy(m_Packet);
	}

    /**
    *   Append data to the end of the packet
    *
    *   Params: 
    *       data = Pointer to the bytes to append
    *       sizeInBytes = Number of bytes to append
    *
    */
    void append(void* data, size_t sizeInBytes)
	{
		sfPacket_Append(m_Packet, data, sizeInBytes);
	}

    /**
    *   Clear the packet data
    *
    */
    void clear()
	{
		sfPacket_Clear(m_Packet);
	}

    /**
    *   Get a pointer to the data contained in the packet
    *   $(B the returned array may be invalid after you
    *   append data to the packet)
    *
    *   Returns: 
    *       Array of data
    */
    byte[] getData()
	{
        size_t l = sfPacket_GetDataSize(m_Packet);
		byte* temp = cast(byte*) sfPacket_GetData(m_Packet);
		return temp[0..l];
	}

    /**
    *   Get the size of the data contained in the packet
    *
    *   Returns: 
    *       Data size, in bytes
    *
    */
    uint getDataSize() 
	{
		return sfPacket_GetDataSize(m_Packet);
	}

    /**
    *   Tell if the packet is valid for reading
    *
    *   Returns: 
    *       True if data can be extracted from the packet
    *
    */
    bool canRead() 
	{
		return cast(bool)(sfPacket_CanRead(m_Packet));
	}
        
    //Dumm_ functions to stop recursion
    private void set()(){}
    private void get()(){}
    
    /**
    *   Add new variables to the packet
    *   Accept (u)byte, (u)short, (u)int, float, double, char[] and wchar[]    
    */        
    Packet set(T, A...)( T t, A a)
    {
        internalSet(t);
        set(a);
        return this;
    }

    /**
    *   Retrieve data from the packet
    *   Accept (u)byte, (u)short, (u)int, float, double, char[] and wchar[]      
    */        
    Packet get(T, A...)(ref T t, ref A a)
    {
        internalGet(t);
        get(a);
        return this;
    }
    
    
package:
    
    sfPacket* toCPacket()
    {
        return m_Packet;
    }
    
    
private:
    void internalGet(ref byte data)
	{
		data = sfPacket_ReadInt8(m_Packet);
        return this;
    }
    void internalGet(ref ubyte data)
	{
		data = sfPacket_ReadUint8(m_Packet);
        return this;
    }
    void internalGet(ref short data)
	{
		data = sfPacket_ReadInt16(m_Packet);
        return this;
    }
    void internalGet(ref ushort data)
	{
		data = sfPacket_ReadUint16(m_Packet);
        return this;
    }
    void internalGet(ref int data)
	{
		data = sfPacket_ReadInt32(m_Packet);
        return this;
    }
    void internalGet(ref uint data)
	{
		data = sfPacket_ReadUint32(m_Packet);
        return this;
    }
    void internalGet(ref float data)
	{
		data = sfPacket_ReadFloat(m_Packet);
        return this;
    }
    void internalGet(ref double data)
	{
		data = sfPacket_ReadDouble(m_Packet);
        return this;
    }
    void internalGet(ref char[] data)
	{
        scope char[] temp = new char[sfPacket_GetDataSize(m_Packet)];
		sfPacket_ReadString(m_Packet, temp.ptr);
        size_t l = fromStringz(temp.ptr).length;
        data = new char[l];
        data[] = temp[0 .. l];
        return this;
    }

    void internalGet(ref wchar[] data)
    {
        scope wchar[] temp = new wchar[sfPacket_GetDataSize(m_Packet)];
		sfPacket_ReadWideString(m_Packet, temp.ptr);
        size_t l = fromString16z(temp.ptr).length;
        data = new wchar[l];
        data[] = temp[0 .. l];
        return this;
    }

    void internalSet(byte data)
	{
		sfPacket_WriteInt8(m_Packet, data);
	    return this;
    }
    void internalSet(ubyte data)
	{
		sfPacket_WriteUint8(m_Packet, data);
    	return this;
    }
    void internalSet(short data)
	{
		sfPacket_WriteInt16(m_Packet, data);
	    return this;
    }
    void internalSet(ushort data)
	{
		sfPacket_WriteUint16(m_Packet, data);
	    return this;
    }
    void internalSet(int data)
	{
		sfPacket_WriteInt32(m_Packet, data);
        return this;
    }
    void internalSet(uint data)
	{
		sfPacket_WriteUint32(m_Packet, data);
        return this;
    }
    void internalSet(float data)
	{
		sfPacket_WriteFloat(m_Packet, data);
        return this;
    }
    void internalSet(double data)
	{
		sfPacket_WriteDouble(m_Packet, data);
        return this;
    }
    void internalSet(char[] data)
	{
		sfPacket_WriteString(m_Packet, toStringz(data));
        return this;
    }

    void internalSet(wchar[] data)
	{
		sfPacket_WriteWideString(m_Packet, toString16z(data));
        return this;
    }


	sfPacket* m_Packet;
	
	mixin TEnforcePointer!(m_Packet);
}
