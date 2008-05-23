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

module dsfml.system.thread;

import dsfml.system.external;

version(Tango)
{
    static import tango.core.Thread;
    alias tango.core.Thread.Thread DThread;
}
else
{
    static import std.thread;
    alias std.thread.Thread DThread;
}

/**
*   Thread defines a simple thread abstraction.
*   
*   Examples:       
*   Can be a base class (you need to override void run(void) method) :
*   --------------------
*   class MyThread : Thread
*   {
*       void function()
*       {
*           this.Launch();    
*       }
*
*       //Thread entry point    
*       private void run()
*       {
*       }               
*   }        
*   --------------------    
*   
*   or
*   
*   --------------------
*   void main()
*   {
*       Thread t = new Thread(&threadStart);
*       t.launch();
*       t.<ait();  //Wait the end of t thread        
*   }
*   
*   //Thread entry point    
*   void threadStart (void* userData)
*   {
*           
*   }                    
*   --------------------                
*
*    
*/
class Thread
{
	/**
    *   Construct the thread from a function pointer.
    *   
    *   Params:
    *       func = Entry point of the thread
	*       userData = Data to pass to the thread function (NULL by default)       
    *   
	*/
	this(void function(void*) func, void* userData = null)
	{
        m_t = new DThread(&threadStart);

        m_func = func;
        m_userData = userData;
	}

	/**
    *   Construct the thread from a delegate.
    *   
    *   Params:
    *       dg = Entry point of the thread
	*       userData = Data to pass to the thread function (NULL by default)       
    *   
	*/
	this(void delegate(void*) dg, void* userData = null)
	{
        m_t = new DThread(&threadStart);

        m_dg = dg;
        m_userData = userData;
        
        m_isDelegate = true;
	}

	/**
    *   Run the thread
	*/
	final void launch()
	{
        m_t.start();
	}

	/**
	*   Wait until the thread finishes
	*/
	final void wait()
	{
        version (Tango)
        {
            m_t.join();
        }
        else
        {
            m_t.wait();
        }
	}

protected:

    this()
    {
        m_t = new DThread(&threadStart);
    }

    void run()
    {
        if (m_isDelegate)
            this.m_dg(this.m_userData);
        else
            this.m_func(this.m_userData);
    }

private:
    DThread m_t;
    bool m_isDelegate;
    
    union
    {
	   void function(void*) m_func;
	   void delegate(void*) m_dg;
	}
	void* m_userData;
        
    /*
    *   Thread entry point
    */
    version (Tango)
    {
        final void threadStart()
        {
            run();
        }
    }
    else
    {
        final int threadStart()
        {
            run();
            return 0;
        }
    }
}

