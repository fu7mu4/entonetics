////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2008 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_WINDOWIMPLXXX_HPP
#define SFML_WINDOWIMPLXXX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowImpl.hpp>
#include <string>


namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
/// WindowImplXXX is the XXX implementation of WindowImpl
////////////////////////////////////////////////////////////
class WindowImplXXX : public WindowImpl
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    /// (creates a dummy window to provide a valid OpenGL context)
    ///
    ////////////////////////////////////////////////////////////
    WindowImplXXX();

    ////////////////////////////////////////////////////////////
    /// Construct the window implementation from an existing control
    ///
    /// \param Handle : Platform-specific handle of the control
    /// \param Params : Creation parameters
    ///
    ////////////////////////////////////////////////////////////
    WindowImplXXX(WindowHandle Handle, WindowSettings& Params);

    ////////////////////////////////////////////////////////////
    /// Create the window implementation
    ///
    /// \param Mode :        Video mode to use
    /// \param Title :       Title of the window
    /// \param WindowStyle : Window style
    /// \param Params :      Creation parameters
    ///
    ////////////////////////////////////////////////////////////
    WindowImplXXX(VideoMode Mode, const std::string& Title, unsigned long WindowStyle, WindowSettings& Params);

    ////////////////////////////////////////////////////////////
    /// Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~WindowImplXXX();

private :

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::Display
    ///
    ////////////////////////////////////////////////////////////
    virtual void Display();

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::ProcessEvents
    ///
    ////////////////////////////////////////////////////////////
    virtual void ProcessEvents();

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::MakeActive
    ///
    ////////////////////////////////////////////////////////////
    virtual void MakeActive(bool Active = true) const;

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::UseVerticalSync
    ///
    ////////////////////////////////////////////////////////////
    virtual void UseVerticalSync(bool Enabled);

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::ShowMouseCursor
    ///
    ////////////////////////////////////////////////////////////
    virtual void ShowMouseCursor(bool Show);

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::SetCursorPosition
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetCursorPosition(unsigned int Left, unsigned int Top);

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::SetPosition
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetPosition(int Left, int Top);

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::Show
    ///
    ////////////////////////////////////////////////////////////
    virtual void Show(bool State);

    ////////////////////////////////////////////////////////////
    /// /see sfWindowImpl::EnableKeyRepeat
    ///
    ////////////////////////////////////////////////////////////
    virtual void EnableKeyRepeat(bool Enabled);
};

} // namespace priv

} // namespace sf

#endif // SFML_WINDOWIMPLXXX_HPP
