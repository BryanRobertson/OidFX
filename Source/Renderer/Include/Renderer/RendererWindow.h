//======================================================================================
//! @file         RendererWindow.h
//! @brief        Provides a base class for a renderer window using the Windows API.
//!
//!				  This class isn't intended to be a complete wrapper of the Win32 API,
//!				  but rather to serve as a simple wrapper for windowing functionality.
//!               
//! @author       Bryan Robertson
//! @date         Monday, 10 January 2005
//! @copyright    Bryan Robertson 2005
//
//				  This file is part of OidFX Engine.
//
//  			  OidFX Engine is free software; you can redistribute it and/or modify
//  			  it under the terms of the GNU General Public License as published by
//  			  the Free Software Foundation; either version 2 of the License, or
//  			  (at your option) any later version.
//
//  			  OidFX Engine is distributed in the hope that it will be useful,
//  			  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  			  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  			  GNU General Public License for more details.
//
//  			  You should have received a copy of the GNU General Public License
//  			  along with OidFX Engine; if not, write to the Free Software
//  			  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================

#ifndef RENDERER_RENDERERWINDOW_H
#define RENDERER_RENDERERWINDOW_H


#include <windows.h>
#include "Core/StandardExceptions.h"
#include "Core/EventConnection.h"
#include "Core/ResizeEvent.h"
#include "Core/KeyboardEvent.h"
#include "Core/MouseEvent.h"


//namespace Renderer
namespace Renderer
{

	typedef Core::RuntimeError RendererWindowException;

	//! @class	RendererWindow
	//! @brief	Provides a base class for a simple window using the Windows API.
	//!
	//!			This class isn't intended to be a complete wrapper of the Win32 API,
	//!			but rather to serve as a simple wrapper for windowing functionality,
	//!			in applications that do not require much in the way of user interface.
	class RendererWindow
	{

		public:

            //=========================================================================
            // Public types
            //=========================================================================
			class QuitMessage
			{
			};

            //=========================================================================
            // Public methods
            //=========================================================================
			//constructors and destructor
			RendererWindow ( const Char* className, const Char* title, UInt top, UInt left, UInt width, UInt height );
			virtual ~RendererWindow ( );

			//public static methods
			static void GetFormattedErrorMessage ( std::string& errString );
			static LRESULT CALLBACK MessageDispatcher ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

			//public non-static methods
			virtual void Initialise ( );
			virtual void ShutDown   ( );
			
			inline UInt Width	( ) const	{ return m_width;  }
			inline UInt Height	( ) const	{ return m_height; }

			inline HWND WindowHandle ( ) const { return m_hWnd; }

			void SetTitle ( const Char* title );
			void SetFullScreenStyle ( bool fullScreen );

			//Message queue
			void	ProcessMessageQueue (  ) const;
			virtual LRESULT CALLBACK MessageProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

			//Events
			Core::EventConnection RegisterResizeHandler	 ( Core::IResizable& handler );
			Core::EventConnection RegisterKeyboardHandler  ( Core::IKeyboardSensitive& handler );
			Core::EventConnection RegisterMouseHandler ( Core::IMouseSensitive& handler );
			
		protected:

			//protected methods
			virtual void GetWindowClass ( WNDCLASSEX& windowClass ) const;
			void RegisterWindowClass ( );
			void UnRegisterWindowClass ( );
			virtual DWORD GetExStyle ( ) const;
			virtual DWORD GetStyle ( ) const;
			void Create ( );
			void Destroy ( );
		
			//Protected data members
			HWND			m_hWnd;
			UInt			m_width;
			UInt			m_height;
			UInt			m_top;
			UInt			m_left;
			std::string		m_className;
			std::string		m_title;

			//Events
			Core::MouseEvent    m_mouse;
			Core::KeyboardEvent m_keyboard;
			Core::ResizeEvent	m_onResize;

	};
	//end class RendererWindow

};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERERWINDOW_H
