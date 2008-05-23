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

module dsfml.system.external;

version (Dynamic)
{
    extern(C)
    {
        ////////////////////////////////////////////////////////////
        //clock.d
        ////////////////////////////////////////////////////////////
        struct sfClock {}
    
    	typedef sfClock* function() pf_sfClock_Create;
    	typedef void function(sfClock*) pf_sfClock_Destroy;
    	typedef float function(sfClock*) pf_sfClock_GetTime;
    	typedef void function(sfClock*) pf_sfClock_Reset;
    
    	pf_sfClock_Create sfClock_Create;
    	pf_sfClock_Destroy sfClock_Destroy;
    	pf_sfClock_GetTime sfClock_GetTime;
    	pf_sfClock_Reset sfClock_Reset;
    

        ////////////////////////////////////////////////////////////
        //randomizer.d
        ////////////////////////////////////////////////////////////
    
    
    	typedef void function(uint) pf_sfRandom_SetSeed;
    	typedef uint function() pf_sfRandom_GetSeed;
    	typedef float function(float, float) pf_sfRandom_Float;
    	typedef int function(int, int) pf_sfRandom_Int;
    
    	pf_sfRandom_SetSeed sfRandom_SetSeed;
    	pf_sfRandom_GetSeed sfRandom_GetSeed;
    	pf_sfRandom_Float sfRandom_Float;
    	pf_sfRandom_Int sfRandom_Int;
    }
}
else
{
    extern(C)
    {
        ////////////////////////////////////////////////////////////
        //clock.d
        ////////////////////////////////////////////////////////////
        struct sfClock {}
    
    
    	sfClock* sfClock_Create();
    	void sfClock_Destroy(sfClock*);
    	float sfClock_GetTime(sfClock*);
    	void sfClock_Reset(sfClock*);
    
    
        ////////////////////////////////////////////////////////////
        //randomizer.d
        ////////////////////////////////////////////////////////////
    	void sfRandom_SetSeed(uint);
    	uint sfRandom_GetSeed();
    	float sfRandom_Float(float, float);
    	int sfRandom_Int(int, int);
    }
}
