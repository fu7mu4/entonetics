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

module dsfml.system.loader;

import dsfml.system.external;
import dsfml.system.dllloader;

version (Windows)
{
    const char[] LIBNAME = "csfml-system.dll";
}
version (linux)
{
    const char[] LIBNAME = "libcsfml-system.so";
}

DLLloader s_lib;

void init()
{
    s_lib = DLLloader.load(LIBNAME);

    // clock.d
    sfClock_Create = cast(pf_sfClock_Create)s_lib.getSymbol("sfClock_Create");
    sfClock_Destroy = cast(pf_sfClock_Destroy)s_lib.getSymbol("sfClock_Destroy");
    sfClock_GetTime = cast(pf_sfClock_GetTime)s_lib.getSymbol("sfClock_GetTime");
    sfClock_Reset = cast(pf_sfClock_Reset)s_lib.getSymbol("sfClock_Reset");
    
	// randomizer.d
	sfRandom_SetSeed = cast(pf_sfRandom_SetSeed)s_lib.getSymbol("sfRandom_SetSeed");
	sfRandom_GetSeed = cast(pf_sfRandom_GetSeed)s_lib.getSymbol("sfRandom_GetSeed");
	sfRandom_Float = cast(pf_sfRandom_Float)s_lib.getSymbol("sfRandom_Float");
	sfRandom_Int = cast(pf_sfRandom_Int)s_lib.getSymbol("sfRandom_Int");
}
