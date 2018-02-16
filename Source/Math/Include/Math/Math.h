//======================================================================================
//! @file         Math.h
//! @brief        Shared math constants and functions
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 18 January 2005
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


#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Math/Scalar.h"

#ifdef WIN32
	#define MATH_IOSTREAM_SUPPORT
#endif

namespace Math
{

	//Pi constants
	extern const Scalar Pi;
	extern const Scalar TwoPi;
	extern const Scalar HalfPi;
	extern const Scalar QuarterPi;
	extern const Scalar InvPi;

	//Constants for small floating point numbers
	extern const Scalar EpsilonE4;
	extern const Scalar EpsilonE5;
	extern const Scalar EpsilonE6;

	//Left-handed/Right-handed
	enum EHandedness
	{
		LEFT_HANDED,
		RIGHT_HANDED
	};

	//Function Prototypes
	inline bool	  Equal ( Scalar s1, Scalar s2 ) throw();
	inline bool	  IsZero  ( Scalar s ) throw();
	inline bool	  InRange ( Scalar s, Scalar min, Scalar max  ) throw();

	inline Scalar DegreesToRadians ( Scalar angleInDegrees ) throw() { return ((angleInDegrees) * Pi/180.0f); }
	inline Scalar RadiansToDegrees ( Scalar angleInRadians ) throw() { return ((angleInRadians) * 180.0f/Pi); }

	//Random functions
	inline void  SRand ( ) throw();
	inline void	 SRand ( UInt seed ) throw();
	inline UInt	 RandomUInt  ( UInt min, UInt max ) throw();
	inline Float RandomFloat  ( Float min, Float max ) throw();

	//Trig functions
	inline Float  Sin( Float x ) throw()		{ return sinf(x);  }
	inline Float  Cos( Float x ) throw()		{ return cosf(x);  }
	inline Float  Tan( Float x ) throw()		{ return tanf(x);  }
	inline Float  SinH( Float x ) throw()		{ return sinhf(x); }
	inline Float  CosH( Float x ) throw()		{ return coshf(x); }
	inline Float  TanH( Float x ) throw()		{ return tanhf(x); }
	inline Float  ASin( Float x ) throw()		{ return asinf(x); }
	inline Float  ACos( Float x ) throw()		{ return acosf(x); }
	inline Float  ATan( Float x ) throw()		{ return atanf(x); }
	inline Float  Cot( Float x ) throw()		{ return (Cos(static_cast<Double>(x))/Sin(static_cast<Double>(x))); }
	inline Float  Sec( Float x ) throw()		{ return (1.0f/Cos(x));   }
	inline Float  Csc( Float x ) throw()		{ return (1.0f/Sin(x));   }
	inline Float  CotH( Float x ) throw()		{ return (CosH(x)/SinH(x)); }
	inline Float  SecH( Float x ) throw()		{ return (1.0f/CosH(x));	}
	inline Float  CscH( Float x ) throw()		{ return (1.0f/SinH(x));	}

	inline Double Sin( Double x ) throw()		{ return sin(x);  }
	inline Double Cos( Double x ) throw()		{ return cos(x);  }
	inline Double Tan( Double x ) throw()		{ return tan(x);  }
	inline Double SinH( Double x ) throw()		{ return sinh(x); }
	inline Double CosH( Double x ) throw()		{ return cosh(x); }
	inline Double TanH( Double x ) throw()		{ return tanh(x); }
	inline Double ASin( Double x ) throw()		{ return asin(x); }
	inline Double ACos( Double x ) throw()		{ return acos(x); }
	inline Double ATan( Double x ) throw()		{ return atan(x); }
	inline Double Cot( Double x ) throw()		{ return (Cos(x)/Sin(x)); }
	inline Double Sec( Double x ) throw()		{ return (1.0f/Cos(x));   }
	inline Double Csc( Double x ) throw()		{ return (1.0f/Sin(x));   }
	inline Double CotH( Double x ) throw()		{ return (CosH(x)/SinH(x)); }
	inline Double SecH( Double x ) throw()		{ return (1.0f/CosH(x));	}
	inline Double CscH( Double x ) throw()		{ return (1.0f/SinH(x));	}

	inline Float  Ceil ( Float x ) throw()		{ return ceilf(x);	 }
	inline Float  Floor( Float x ) throw()		{ return floorf(x);	 }

	inline Double Ceil ( Double x ) throw()		{ return ceil(x);	}
	inline Double Floor( Double x ) throw()		{ return floor(x);	}

	inline Float  Sqrt ( Float x ) throw()		{ return sqrtf(x);	}
	inline Double Sqrt ( Double x ) throw()		{ return sqrt(x);	}

	inline Float  Log ( Float x ) throw()		{ return logf(x);	}
	inline Double Log ( Double x ) throw()		{ return log(x);	}

	inline Float  Exp ( Float x ) throw()		{ return expf(x);	}
	inline Double Exp ( Double x) throw()		{ return exp(x);	}

	inline Float  Frac ( Float x ) throw()		{ return x - Floor(x); }
	inline Double Frac ( Double x ) throw()		{ return x - Floor(x); }

	inline Float Round ( Float x ) throw()		{ return (static_cast<Int>(x + 0.5));  }
	inline Double Round ( Double x ) throw()	{ return (static_cast<Int>(x + 0.5));  }

	//Wave forms
	inline Float SawToothFunction ( Float x ) throw();
	inline Double SawToothFunction ( Double x ) throw();

	inline Float SquareWaveFunction ( Float x ) throw();
	inline Double SquareWaveFunction ( Double x ) throw();
	
	inline Float TriangleWaveFunction ( Float x ) throw();
	inline Double TriangleWaveFunction ( Double x ) throw();


	//
	template <class T>
		inline T Abs(T x) throw();

	template <class T>
		inline T Squared ( T value ) throw();


	//=========================================================================
    //! @function    Math::Abs<T>
    //! @brief       Return the absolute value of x
    //!              
    //! @param       x [in] Value to get the absolute value of
    //!              
    //! @return      Return the absolute value of x
    //=========================================================================
	template <class T>
	inline T Abs( T x )
	{
		return abs(x);
	}
	//End Math::Abs<T>



    //=========================================================================
    //! @function    Math::Abs<Float>
    //! @brief       Return the absolute value of x
    //!              
    //! @param       x [in] Value to get the absolute value of
    //!              
    //! @return      Return the absolute value of x   
    //=========================================================================
	template<>
	inline Float Abs<Float> ( Float x )
	{
		return fabsf(x);
	}
	//End Maths::Abs<Float>



    //=========================================================================
    //! @function    Math::Abs<Double>
    //! @brief       Return the absolute value of x
    //!              
    //! @param       x [in] Value to get the absolute value of
    //!              
    //! @return      Return the absolute value of x  
    //=========================================================================
	template<>
	inline Double Abs<Double> ( Double x )
	{
		return fabs(x);
	}
	//End Maths::Abs<Double>



    //=========================================================================
    //! @function    Math::Equal
    //! @brief       Check two floating point values for equality, compensating for tiny differences
	//!
    //!              Return true if two floating point values are extremely close to equality. 
    //!              Use this to avoid problems with floating point accuracy when comparing floating point values
    //!              
    //! @param       s1 [in]
    //! @param       s2 [in]
    //!              
    //! @return      true if s1 and s2 are very nearly equal. false otherwise
    //=========================================================================
	bool Equal ( Scalar s1, Scalar s2 )
	{
		if ( Abs( s1 - s2 ) <= EpsilonE4 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//end Math::Equal




    //=========================================================================
    //! @function    Math::IsZero
    //! @brief       Return true if the scalar passed is zero 
    //!              Use this to avoid problems with floating point accuracy when comparing floating point values
    //!              
    //! @param       s	[in]	 
    //!              
    //! @return      true if s is very close to zero, false otherwise
    //=========================================================================
	bool IsZero ( Scalar s )
	{
		if ( Abs( s ) <= EpsilonE4 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//end Math::IsZero


    //=========================================================================
    //! @function    Math::InRange
    //! @return		 Return true if s is between min and max
    //!              
    //! @param       s		[in]
    //! @param       min	[in]
    //! @param       max	[in]
    //!              
    //=========================================================================
	bool InRange ( Scalar s, Scalar min, Scalar max )
	{
		if  ( ( s >= min) && ( s <= max ) )
		{
			return true;
		
		}else{

			return false;
		}
	}
	//end Math::InRange



	//=========================================================================
	//! @function    Math::Squared<T>
	//! @param       value 
	//!              
	//! @return      value * value      
	//=========================================================================
	template <class T>
	inline T Squared ( T value )
	{
		return (value*value);
	}
	//end Squared


	//=========================================================================
    //! @function    Math::SRand
    //! @brief       Seed the random number generator with the current time
	//!
	//=========================================================================
	void SRand ()
	{
		srand ( (unsigned)time( 0 ) );
	}
	//End Math::SRand



    //=========================================================================
    //! @function    Math::SRand
    //! @brief       Seed the random number generator
	//!
    //! @param       seed 
    //   
	//=========================================================================
	void SRand ( UInt seed )
	{
		srand ( seed );
	}
	//End Math::SRand



    //=========================================================================
    //! @function    Math::RandomUInt
    //! @brief       Return a random unsigned integer between min and max
    //!              
    //! @param       min [in]	Minimum value of the random number
    //! @param       max [in]	Maximum value of the random number
    //!              
    //! @return      Random integer between min and max
    //=========================================================================
	UInt RandomUInt ( UInt min, UInt max )
	{
		return rand() % (max-min+1) + min;
	}
	//end Math::Rand



    //=========================================================================
    //! @function    Math::RandomFloat
    //! @brief       Return a floating point value between min and max
	//!
    //! @param       min [in]	Minumum value of random value
    //! @param       max [in]	Maximum value of random value
    //!              
    //! @return      Random floating point value between min and max
    //=========================================================================
	Float RandomFloat ( Float min, Float max )
	{
		return ((rand()+min) / (Float)RAND_MAX) * (max-min) + min ;
	}
	//end Math::Rand



	

    //=========================================================================
    //! @function    Math::SawToothFunction
    //! @brief       Return the results of a sawtooth function for x,
    //!				 with a amplitude of 1, a period of 1, and a phase of 0              
	//!
    //! @param       x [in] Value to calculate the sawtooth function for
    //!              
    //! @return      The value of the sawtooth function for x
    //=========================================================================
	Float SawToothFunction ( Float x ) 
	{

		//S(x) = amplitude * frac ( (x/period) + phase )
		//
		//Since our amplitude is 1.0, and our phase is 0,
		//the result is as follows
		return Frac(x/1.0f);
	}
	//End Math::SawToothFunction



	//=========================================================================
    //! @function    Math::SawToothFunction
    //! @brief       Return the results of a sawtooth function for x,
    //!				 with a amplitude of 1, a period of 1, and a phase of 0              
	//!
    //! @param       x [in] Value to calculate the sawtooth function for
    //!              
    //! @return      The value of the sawtooth function for x
    //=========================================================================
	Double SawToothFunction ( Double x ) 
	{

		//S(x) = amplitude * frac ( (x/period) + phase )
		//
		//Since our amplitude is 1.0, and our phase is 0,
		//the result is as follows
		return Frac(x/1.0);
	}
	//End Math::SawToothFunction



    //=========================================================================
    //! @function    Math::SquareWaveFunction
    //! @brief       Return a square wave function with an amplitude of 1
    //!              and a period of 1
	//!
    //! @param       x [in]
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	Float SquareWaveFunction ( Float x )
	{
		if ( (x > 1.0f) || (x < -1.0f) )
		{
			x = x - Floor( Abs(x) );
		}
		
		return (x >= 0.5) ? -1.0f : 1.0f;
	}
	//End SquareWaveFunction



	//=========================================================================
    //! @function    Math::SquareWaveFunction
    //! @brief       Return a square wave function with an amplitude of 1
    //!              and a period of 1
	//!
    //! @param       x [in]
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	Double SquareWaveFunction ( Double x )
	{
		if ( (x > 1.0f) || (x < -1.0f) )
		{
			x = x - Floor( Abs(x) );
		}

		return (x > 0.5) ? -1.0 : 1.0;
	}
	//End Math::SquareWaveFunction


    //=========================================================================
    //! @function    Math::TriangleWaveFunction
    //! @brief       Return the value of a triangle wave at x
    //!              
    //! @param       x 
    //!              
    //! @return      The value of a triangle wave at x
    //=========================================================================
	Float TriangleWaveFunction ( Float x )
	{
		return (1.0f - (2.0f* Abs(Round(x) - (x))) );
	}
	//End TriangleWaveFunction


	//=========================================================================
    //! @function    Math::TriangleWaveFunction
    //! @brief       Return the value of a triangle wave at x
    //!              
    //! @param       x 
    //!              
    //! @return      The value of a triangle wave at x
    //=========================================================================
	Double TriangleWaveFunction ( Double x )
	{
		return (1.0 - (2.0* Abs(Round(x) - (x))) );	
	}
	//End TriangleWaveFunction


};//end namespace Math

#endif
//#ifndef MATH_COMMON_H
