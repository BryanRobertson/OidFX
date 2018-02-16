//======================================================================================
//! @file         RendererWindow.h
//! @brief		  Provides a base class for a renderer window using the RendererWindows API.
//!
//!				  This class isn't intended to be a complete wrapper of the Win32 API,
//!				  but rather to serve as a simple wrapper for windowing functionality.
//!               
//!               
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


#include "Core/Core.h"
#include "Renderer/RendererWindow.h"


using namespace Renderer;


//Constructors and Destructor


//=========================================================================
//! @function    RendererWindow::RendererWindow
//! @brief       RendererWindow constructor
//!              
//!              Creates a window with the attributes specified
//!              
//! @param		 className  [in] class name of window to be passed to RegisterClassEx
//! @param       title		[in] text to be displayed in the title bar of the window
//! @param       top		[in] y value for top of the window
//! @param       left		[in] x value for the left of the window
//! @param       width		[in] width of the window
//! @param       height		[in] height of the window
//!
//!              
//! @throw       RendererWindowException if the window could not be created
//=========================================================================
RendererWindow::RendererWindow ( const Char* className, const Char* title, UInt top, UInt left, UInt width, UInt height )
: m_className(className), m_title(title), m_top(top), m_left(left), 
  m_width(width), m_height(height), m_hWnd(0)
{

}
//end RendererWindow::RendererWindow



//=========================================================================
//! @function    RendererWindow::~RendererWindow
//! @brief       RendererWindow destructor
//!              
//!				 Destroy the window and unregister the window class
//=========================================================================
RendererWindow::~RendererWindow ( )
{
	if ( m_hWnd != 0 )
	{
		ShutDown ();
	}
}
//end RendererWindow::~RendererWindow



//Public static methods



//=========================================================================
//! @function    RendererWindow::GetFormattedErrorMessage
//! @brief       Return an error message string based on the return from 
//!				 the windows API call GetLastError
//!              
//! @param       errString	[out] errString - String to write message into
//!    
//=========================================================================
void RendererWindow::GetFormattedErrorMessage ( std::string& errString )
{
	//Check that there is actually an error in the first place
	if ( GetLastError() == 0 )
	{
		errString = "No error";
		return;
	}
	
	//Reserve a reasonably large error message string
	errString.resize ( 1024 );

	DWORD size = FormatMessage ( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
									0, //Get message from system
									GetLastError( ), //messageID
									MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
									reinterpret_cast<LPSTR> ( &errString[0] ),
									errString.size ( ),
									0 );

	errString.resize ( size );

	#if 0
		std::cerr << errString << " : GetLastError = " << GetLastError() << std::endl;
	#endif
}
//end RendererWindow::GetFormattedErrorMessage



//=========================================================================
//! @function    RendererWindow::MessageDispatcher
//! @brief       Dispatches windows messages to instances of the window class
//!				 
//!				 The windows API requires that windows register a callback function.
//!				 Since the WIN32 API is C based, a pointer to a class member function won't work
//!				 so we need to register this static function to route messages to the appropriate class instance.
//!              
//! @return          
//=========================================================================
LRESULT CALLBACK RendererWindow::MessageDispatcher ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	
	//Attempt to retrieve instance pointer from GetWindowLong
	RendererWindow* pRendererWindow = reinterpret_cast<RendererWindow*>( GetWindowLongPtr(hWnd, GWLP_USERDATA) );

	//Check if it failed
	if( pRendererWindow )
	{
		//Call the message procedure for the object instance
		return ( pRendererWindow->MessageProc ( hWnd, uMsg, wParam, lParam) );

	}
	else //If we couldn't get the instance pointer then it hasn't been set yet
	{
		//check to see what message we recieved
		switch (uMsg)
		{

			case WM_NCCREATE:
			{
				//RendererWindow is being created
				//Use SetWindowLong to store pointer to instance
				//Get pointer from the lpCreateParams passed to CreateWindowEx
				pRendererWindow = reinterpret_cast<RendererWindow*> ( 
										reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams );
				SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pRendererWindow) );
	
				return pRendererWindow->MessageProc( hWnd, uMsg, wParam, lParam );
			
			}
			break;
			
			case WM_GETMINMAXINFO:
			{
				//For some reason, known only to Microsoft, this gets called before WM_NCCREATE
				//Meaning that the window doesn't have it's pointer to
				//the class instance yet. 
				//Just let the default window procedure deal with this message
				return DefWindowProc( hWnd, uMsg, wParam, lParam);
			}
			break;
			
			default:
			{
				//We've received a message other than WM_GETMINMAXINFO, and still can't find the instance
				//of the RendererWindow*, this shouldn't happen, so throw an exception
				throw RendererWindowException( "Serious error! Couldn't get pointer to window instance!", GetLastError(),
										__FILE__, __FUNCTION__, __LINE__ );

				return DefWindowProc( hWnd, uMsg, wParam, lParam);

			}
			break;

		};//end switch ( uMsg )

	}//end if (pRendererWindow )

	return DefWindowProc( hWnd, uMsg, wParam, lParam );

}
//end RendererWindow::MessageDispatcher




//=========================================================================
//! @function    RendererWindow::Initialise
//! @brief       Actually create the window, calling all necessary functions
//!              
//!              Override this to provide other functions (such as setting
//!				 up OpenGL for example)
//!              
//! @throw       RendererWindowException
//=========================================================================
void RendererWindow::Initialise ( )
{
	RegisterWindowClass();
	Create ( );

	ShowWindow ( m_hWnd, SW_SHOW );
}
//end RendererWindow::Initialize



//=========================================================================
//! @function    RendererWindow::ShutDown
//! @brief       Destroy the window and do any cleanup
//!              
//!              
//! @throw       RendererWindowException
//=========================================================================
void RendererWindow::ShutDown ( )
{
	if ( m_hWnd == 0 )
		return;

	Destroy ( );
	UnRegisterWindowClass ( );
}
//end RendererWindow::ShutDown



//=========================================================================
//! @function    RendererWindow::SetTitle
//! @brief       Set the text in the title bar of the window
//!              
//! @param       title [in] New title text for window
//=========================================================================
void RendererWindow::SetTitle ( const Char* title )
{
	if ( m_hWnd == 0 )
		return;

	//Send change text message
	SendMessage ( m_hWnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(title) );
}
//end RendererWindow::SetTitle



//=========================================================================
//! @function    RendererWindow::SetFullScreenStyle
//! @brief       Set the window style for full screen or windowed
//!             
//!				 Full screen applications don't have a title bar, border, etc
//!				 This function removes the title and border if necessary
//!
//! @param       fullScreen [in] true to set to full screen window styles
//!								 false to set to windowed window styles
//! @return      
//! @throw       
//=========================================================================
void RendererWindow::SetFullScreenStyle( bool fullScreen )
{
	if ( m_hWnd )
	{
		if ( fullScreen )
		{
			//Set the window style
			SetWindowLong( m_hWnd, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE );
			//Hide the cursor
			ShowCursor(FALSE);

		}
		else
		{
			//Set the window style
			SetWindowLong( m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CLIPCHILDREN
												| WS_SYSMENU | WS_VISIBLE | WS_BORDER | WS_CAPTION );
			//Hide the cursor
			ShowCursor(TRUE);
		}
	}
	else
	{
		std::cerr << "Error, tried to set full screen mode on a window that hasn't been created!" << std::endl;
	}
}
//End RendererWindow::SetFullScreenStyle



//=========================================================================
//! @function    RendererWindow::ProcessMessageQueue
//! @brief       Moves along the windows message queue
//! 
//!              
//! @throw		 QuitMessage if WM_QUIT was recieved
//=========================================================================
void RendererWindow::ProcessMessageQueue (  ) const
{
	MSG msg;

	//Check if there are any messages
	if ( PeekMessage ( &msg, m_hWnd, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage ( &msg );
		DispatchMessage  ( &msg );

		//Return false if a quit message is recieved
		if ( msg.message == WM_QUIT )
		{
			throw QuitMessage();
		}
	}
}
//end RendererWindow::ProcessMessageQueue



//=========================================================================
//! @function    RendererWindow::MessageProc
//! @brief       Message handler for this instance of the window class
//=========================================================================
LRESULT CALLBACK RendererWindow::MessageProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		case WM_SIZE:
			m_onResize.Resize ( LOWORD(lParam), HIWORD(lParam) );
			m_width = LOWORD (lParam);
			m_height = HIWORD (lParam);
			return 0;

		case WM_KEYUP:
		{
			UInt keyCode = Core::MapWindowsKeyToVirtualKey(wParam);

			m_keyboard.OnKeyUp ( keyCode ); 

			return 1;
		}

		case WM_KEYDOWN:
		{
			UInt keyCode = Core::MapWindowsKeyToVirtualKey(wParam);
			UInt repeatCount = lParam & 0xFFFF; //The repeat count is held in the first 16 bits of lParam
			bool previousState = ( lParam & 1<<30);

			m_keyboard.OnKeyDown( keyCode ); 

			return 1;
		}

		case WM_CHAR:
		{
			//If the key is being released then ignore it
			if ( lParam & 1<<31 )
			{
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}

			Char keyCode = 0;
			BOOL wasDefaultCharUsed = FALSE;

			//Convert the character to ANSI
			WideCharToMultiByte( CP_ACP,				// code page
								 0,					    // performance and mapping flags
								 (LPCWSTR)&wParam,      // wide-character string
								 1,						// number of chars in string
								 &keyCode,				// buffer for new string
								 1,						// size of buffer
								 " ",					// default for unmappable chars
								 &wasDefaultCharUsed    // set when default char used
								 );

			//If the character wasn't mappable, then just handle use DefWindowProc to handle the message
			if ( wasDefaultCharUsed )
			{
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}

			//Call the keyboard handlers. 
			//(repeat count is the first 16 bytes of lParam)
			//(previous key state is in lParam bit 30)
			m_keyboard.OnChar ( keyCode, (lParam & 0xF), (lParam & (1<<30) ) ); 
	
			return 1;
		}

		case WM_MOUSEMOVE:
		{
			static Int oldMouseX = 0;
			static Int oldMouseY = 0;
			static Int mouseX = 0;
			static Int mouseY = 0;

			oldMouseX = mouseX;
			oldMouseY = mouseY;

			//Get the change in mouse position
			mouseX = LOWORD(lParam); 
			mouseY = HIWORD(lParam); 

			m_mouse.OnMouseMove ( oldMouseX - mouseX, oldMouseY - mouseY );
		}
		break;
/*
		case WM_MOUSEWHEEL:
			m_mouse.OnMouseScroll ( HIWORD(wParam) / WHEEL_DELTA );
			break;
*/
		case WM_LBUTTONDOWN:
			m_mouse.OnMouseButtonDown ( Core::MOUSEBUTTON_LEFT );
			break;

		case WM_LBUTTONUP:
			m_mouse.OnMouseButtonUp ( Core::MOUSEBUTTON_LEFT );
			break;

		case WM_RBUTTONDOWN:
			m_mouse.OnMouseButtonDown ( Core::MOUSEBUTTON_RIGHT );
			break;

		case WM_RBUTTONUP:
			m_mouse.OnMouseButtonUp ( Core::MOUSEBUTTON_RIGHT );
			break;

		case WM_MBUTTONUP:
			m_mouse.OnMouseButtonUp ( Core::MOUSEBUTTON_MIDDLE );
			break;

		case WM_MBUTTONDOWN:
			m_mouse.OnMouseButtonDown ( Core::MOUSEBUTTON_MIDDLE );
			break;

		case WM_CLOSE:
			PostQuitMessage( 0 );
			ShutDown();
			return 0;
/*
		case WM_DESTROY:
			SetWindowLongPtr( m_hWnd, GWLP_USERDATA, static_cast<LONG_PTR>(0) );
			return 1;
*/
		default:
			break;
	};

	return DefWindowProc ( hWnd, uMsg, wParam, lParam );
}
//end RendererWindow::MessageProc



//=========================================================================
//! @function    RendererWindow::GetWindowClass
//! @brief       Return a window class structure filled out for the correct
//!				 window type
//!              
//!              Override this method to create a window with a different class
//!              
//! @param       windowClass [out]	       
//=========================================================================
void RendererWindow::GetWindowClass ( WNDCLASSEX& windowClass ) const
{
	windowClass.cbSize = sizeof ( windowClass );
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = MessageDispatcher;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle ( NULL );
	windowClass.hIcon = LoadIcon ( GetModuleHandle ( NULL ), "IDI_ICON1" );
	windowClass.hCursor = LoadCursor ( 0, IDC_ARROW );
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = m_className.c_str();
	windowClass.hIconSm = LoadIcon ( GetModuleHandle ( NULL ), "IDI_ICON1" );

	if ( windowClass.hIcon == NULL )
	{
		#if 0
			std::string error;
			GetFormattedErrorMessage ( error );

			std::cerr << __FUNCTION__ << ": Could not load icon: " << error << std::endl;
		#endif

		windowClass.hIcon = LoadIcon ( GetModuleHandle ( NULL ), "IDI_WINLOGO" );
		windowClass.hIconSm = LoadIcon ( GetModuleHandle ( NULL ), "IDI_WINLOGO" );
	}
}
//end RendererWindow::GetWindowClass



//=========================================================================
//! @function    RendererWindow::RegisterWindowClass
//! @brief       Call RegisterClassEx for this classes window class type
//!              
//!              
//! @throw       RendererWindowException
//=========================================================================
void RendererWindow::RegisterWindowClass ( )
{

	WNDCLASSEX windowClass;

	//Get the window class
	GetWindowClass( windowClass );

	//Register the window class
	if ( RegisterClassEx ( &windowClass ) )
	{
		std::cout << "RendererWindow: RendererWindow class " << m_className.c_str() << " registered" << std::endl;
	}
	else
	{	
		//Failed to register window class. Get the windows error message, and throw an exception
		std::string errorMessage ( "" );
		GetFormattedErrorMessage ( errorMessage );

		throw RendererWindowException ( errorMessage.c_str(), GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	}
}
//end RegisterWindowClass



//=========================================================================
//! @function    RendererWindow::UnRegisterWindowClass
//! @brief       Unregister the window class
//!              
//! @throw       RendererWindowException
//=========================================================================
void RendererWindow::UnRegisterWindowClass ( )
{
	//Unregister the window class
	if ( !UnregisterClass(m_className.c_str(), GetModuleHandle(NULL)) )
	{
		std::string errorString;
		GetFormattedErrorMessage ( errorString );

		throw RendererWindowException ( errorString.c_str(), GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	}
}
//end RendererWindow::UnRegisterWindowClass



//=========================================================================
//! @function    RendererWindow::GetExStyle
//! @brief       Return custom extended window style for this class
//=========================================================================
DWORD RendererWindow::GetExStyle ( ) const
{
	return WS_EX_WINDOWEDGE;
}
//end RendererWindow::GetExStyle



//=========================================================================
//! @function    RendererWindow::GetStyle
//! @brief       Return custom window style for this class
//=========================================================================
DWORD RendererWindow::GetStyle ( ) const
{
	return WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
}
//end RendererWindow::GetStyle



//=========================================================================
//! @function    RendererWindow::Create
//! @brief       Create the window
//!
//! @throw       RendererWindowException
//=========================================================================
void RendererWindow::Create ( )
{

	//Get the window style
	DWORD dwExStyle = GetExStyle ( );
	DWORD dwStyle   = GetStyle ( );

	if ( m_hWnd !=0 )
		throw RendererWindowException ( ": m_hWnd !=0!!!", GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	
	//Create the window, passing the address of this class instance in the last
	//parameter, so MessageDispatcher can dispatch messages to it 
	m_hWnd = CreateWindowEx (	dwExStyle,								 //dwExStyle
								m_className.c_str( ),					 //className
							    m_title.c_str(),						 //lpRendererWindowName
								dwStyle,								 //dwStyle
								m_top,m_left,							 //x,y
								m_width, m_height,						 //nWidth, nHeight
								0,										 //hWndParent
								0,										 //hMenu
								GetModuleHandle ( NULL ),				 //hInstance
								reinterpret_cast<LPVOID> ( this ) );	 //lpParam

	//Print an error message if the window was not created
	if ( m_hWnd == 0 )
	{
		std::string errorString;
		GetFormattedErrorMessage ( errorString );

		throw RendererWindowException ( errorString.c_str(), GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	}

}
//RendererWindow::Create




//=========================================================================
//! @function    RendererWindow::Destroy
//! @brief       Destroy the window
//!              
//!				 Does nothing if no window exists, so can be safely called
//!				 from the destructor
//!
//! @throw		 RendererWindowException       
//=========================================================================
void RendererWindow::Destroy ( )
{
	//Check that the window exists
	if ( m_hWnd == 0)
	{
		return;
	}

	//Destroy the window
	if ( !DestroyWindow(m_hWnd) )
	{
		std::string errorString;
		GetFormattedErrorMessage ( errorString );

		std::cerr << __FUNCTION__ ": Error! " << errorString << std::endl;
		//throw RendererWindowException ( errorString );
	}

	//Set the window pointer to zero to stop messages from being sent
	//to a dead window
	//SetWindowLongPtr(m_hWnd, GWLP_USERDATA, 0);
	m_hWnd = 0;
}
//end RendererWindow::Destroy



//=========================================================================
//! @function    RendererWindow::RegisterResizeHandler
//! @brief       Add an event handler to the list of event handlers 
//!				 to be informed of window resize events
//!              
//! @param       handler	[in] Reference to an IResizable implementing object
//!              
//=========================================================================
Core::EventConnection RendererWindow::RegisterResizeHandler ( Core::IResizable& handler )
{
	//Call the handler with the initial width and height
	handler.Resize( Width(), Height() );

	//Register the handler
	return m_onResize.Connect( handler );
}
//end RendererWindow::RegisterResizeHandler



//=========================================================================
//! @function    RendererWindow::RegisterOnKeyDownHandler
//! @brief       Add an event handler to the list of event handlers to be 
//!				 informed of Keyboard events
//!              
//! @param       handler	[in] Reference to IKeyboardSensitive implementing object          
//=========================================================================
Core::EventConnection RendererWindow::RegisterKeyboardHandler ( Core::IKeyboardSensitive& handler )
{
	//Register the handler
	return m_keyboard.Connect(handler);
}
//end RendererWindow::RegisterOnKeyDownHandler



//=========================================================================
//! @function    RendererWindow::RegisterMouseHandler
//! @brief       Add an event handler to the list of mouse event handlers
//!              
//! @param       handler [in]
//!              
//=========================================================================
Core::EventConnection RendererWindow::RegisterMouseHandler ( Core::IMouseSensitive& handler )
{
	return m_mouse.Connect ( handler );
}
//End RendererWindow::RegisterMouseHandler
