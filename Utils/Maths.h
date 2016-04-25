/// Math.h
// This header defines the Vector3 class and the CMath class

/*
The Vector3 class is a typical Vector3 definition with nasty and tasty operator overloads,
so operating with Vector3s should be better and faster.
The CMath class allows you to do maths calculations that come handy when coding things that involve
a lot of math, like an aimbot, or an external radar...
Credits to TeamGamerFood
*/

/*
DOUBLE SDK | A FREE CSGO SDK MADE BY DOUBLE V FOR UNKNOWNCHEATS.ME
CREDITS AND SHOUTOUTS:
Double V
WasserEsser
TeamGamerFood
Serge
*/

#pragma once

#include "DoubleSDK.h"
#include <math.h>


#define M_RADPI 57.295779513082f
#define M_PI 3.14159265358979323846
#define M_PI_F ((float)(M_PI))

#define SQUARE( a )	   a*a
#define DEG2RAD( x )  ( (float)(x) * (float)( M_PI_F / 180.f ) )
#define RAD2DEG( x )  ( (float)(x) * (float)( 180.f/M_PI_F ) )

#pragma warning(disable : 4244)

class Vector3;
class CMath;

/// TEAMGAMERFOOD 1337 SQRT: THE FASTEST SQRT ALIVE
double inline __declspec ( naked ) __stdcall FastSQRT( double n )
{
	_asm fld qword ptr[ esp + 4 ]
	_asm fsqrt
	_asm ret 8
}

class Vector3
{
public:
	float x, y, z;

	Vector3()
	{
		x = y = z = 0.0f;
	}

	Vector3( float X, float Y, float Z )
	{
		x = X; y = Y; z = Z;
	}

	Vector3( float XYZ )
	{
		x = XYZ; y = XYZ; z = XYZ;
	}

	Vector3( float* v )
	{
		x = v[ 0 ]; y = v[ 1 ]; z = v[ 2 ];
	}

	Vector3( const float* v )
	{
		x = v[ 0 ]; y = v[ 1 ]; z = v[ 2 ];
	}

	inline Vector3& operator=( const Vector3& v )
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	inline Vector3& operator=( const float* v )
	{
		x = v[ 0 ]; y = v[ 1 ]; z = v[ 2 ]; return *this;
	}

	inline float& operator[]( int i )
	{
		return ( ( float* )this )[ i ];
	}

	inline float operator[]( int i ) const
	{
		return ( ( float* )this )[ i ];
	}

	inline Vector3& operator+=( const Vector3& v )
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline Vector3& operator-=( const Vector3& v )
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline Vector3& operator*=( const Vector3& v )
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	inline Vector3& operator/=( const Vector3& v )
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	inline Vector3& operator+=( float v )
	{
		x += v; y += v; z += v; return *this;
	}

	inline Vector3& operator-=( float v )
	{
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector3& operator*=( float v )
	{
		x *= v; y *= v; z *= v; return *this;
	}

	inline Vector3& operator/=( float v )
	{
		x /= v; y /= v; z /= v; return *this;
	}

	inline Vector3 operator-( ) const
	{
		return Vector3( -x, -y, -z );
	}

	inline Vector3 operator+( const Vector3& v ) const
	{
		return Vector3( x + v.x, y + v.y, z + v.z );
	}

	inline Vector3 operator-( const Vector3& v ) const
	{
		return Vector3( x - v.x, y - v.y, z - v.z );
	}

	inline Vector3 operator*( const Vector3& v ) const
	{
		return Vector3( x * v.x, y * v.y, z * v.z );
	}

	inline Vector3 operator/( const Vector3& v ) const
	{
		return Vector3( x / v.x, y / v.y, z / v.z );
	}

	inline Vector3 operator+( float v ) const
	{
		return Vector3( x + v, y + v, z + v );
	}

	inline Vector3 operator-( float v ) const
	{
		return Vector3( x - v, y - v, z - v );
	}

	inline Vector3 operator*( float v ) const
	{
		return Vector3( x * v, y * v, z * v );
	}

	inline Vector3 operator/( float v ) const
	{
		return Vector3( x / v, y / v, z / v );
	}

	inline float Length() const
	{
		return sqrtf( x * x + y * y + z * z );
	}

	inline float LengthSqr() const
	{
		return ( x * x + y * y + z * z );
	}

	inline float LengthXY() const
	{
		return sqrtf( x * x + y * y );
	}

	inline float LengthXZ() const
	{
		return sqrtf( x * x + z * z );
	}

	inline float DistTo( const Vector3& v ) const
	{
		return ( *this - v ).Length();
	}

	inline float Dot( const Vector3& v ) const
	{
		return ( x * v.x + y * v.y + z * v.z );
	}

	inline Vector3 Cross( const Vector3& v ) const
	{
		return Vector3( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x );
	}

	inline bool IsZero() const
	{
		return ( x > -0.01f && x < 0.01f
				 &&	y > -0.01f && y < 0.01f
				 &&	z > -0.01f && z < 0.01f );
	}

	inline void Reset()
	{
		x = 0.f; y = 0.f; z = 0.f;
	}
};

/// TODO: Maybe update this class, for now I need it only in W2S
class Vector2
{
public:
	float x,y;
};

class CMath
{
public:

	CMath()
	{
		srand( time( NULL ) );
	}

	void inline SinCos( float radians, float *sine, float *cosine )
	{
		_asm
		{
			fld		DWORD PTR[ radians ]
				fsincos

				mov edx, DWORD PTR[ cosine ]
				mov eax, DWORD PTR[ sine ]

				fstp DWORD PTR[ edx ]
				fstp DWORD PTR[ eax ]
		}

		*sine = sin( radians );
		*cosine = cos( radians );
	}

	void AngleVectors( const Vector3 &angles, Vector3 *forward )
	{

		float sr, sp, sy, cr, cp, cy;

		SinCos( DEG2RAD( angles[ 0 ] ), &sy, &cy );
		SinCos( DEG2RAD( angles[ 1 ] ), &sp, &cp );
		SinCos( DEG2RAD( angles[ 2 ] ), &sr, &cr );

		if( forward )
		{
			forward->x = cp*cy;
			forward->y = cp*sy;
			forward->z = -sp;
		}
	}

	void AngleVectors( const Vector3 &angles, Vector3 *forward, Vector3 *right, Vector3 *up )
	{

		float sr, sp, sy, cr, cp, cy;

		SinCos( DEG2RAD( angles[ 0 ] ), &sy, &cy );
		SinCos( DEG2RAD( angles[ 1 ] ), &sp, &cp );
		SinCos( DEG2RAD( angles[ 2 ] ), &sr, &cr );

		if( forward )
		{
			forward->x = cp*cy;
			forward->y = cp*sy;
			forward->z = -sp;
		}

		if( right )
		{
			right->x = ( -1 * sr*sp*cy + -1 * cr*-sy );
			right->y = ( -1 * sr*sp*sy + -1 * cr*cy );
			right->z = -1 * sr*cp;
		}

		if( up )
		{
			up->x = ( cr*sp*cy + -sr*-sy );
			up->y = ( cr*sp*sy + -sr*cy );
			up->z = cr*cp;
		}
	}

	float DotProduct( Vector3 &v1, float* v2 )
	{
		return v1.x*v2[ 0 ] + v1.y*v2[ 1 ] + v1.z*v2[ 2 ];
	}

	float Dot( const Vector3 &v1, Vector3 &v2 )
	{
		return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
	}

	float VecLength( Vector3& vec )
	{
		return FastSQRT( vec.x *  vec.x + vec.y *  vec.y + vec.z *  vec.z );
	}

	float VecDist( Vector3& fVec1, Vector3& fVec2 )
	{
		return FastSQRT( pow( fVec1.x - fVec2.x, 2 ) + pow( fVec1.y - fVec2.y, 2 ) + pow( fVec1.z - fVec2.z, 2 ) );
	}

	float GetFov( Vector3 angle, Vector3 src, Vector3 dst )
	{
		Vector3 ang, aim;
		ang = CalcAngle( src, dst );
		MakeVector( angle, aim );
		MakeVector( ang,   ang );

		float mag = FastSQRT( pow( aim.x, 2 ) + pow( aim.y, 2 ) + pow( aim.z, 2 ) );
		float u_dot_v = Dot( aim, ang );

		return RAD2DEG( acos( u_dot_v / ( pow( mag, 2 ) ) ) );
	}

	Vector3 CalcAngle( Vector3 Source, Vector3 Destination )
	{
		#pragma warning(disable : 4244)
		Vector3 angles;
		Vector3 delta;
		delta.x = (Source.x - Destination.x);
		delta.y = (Source.y - Destination.y);
		delta.z = (Source.z - Destination.z);

		double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
		angles.x = (float)(atanf(delta.z / hyp) * 57.295779513082f);
		angles.y = (float)(atanf(delta.y / delta.x) * 57.295779513082f);

		angles.z = 0.0f;
		if (delta.x >= 0.0) { angles.y += 180.0f; }
		return angles;
	}

	void VectorAngles( const Vector3& dir, Vector3 &angles )
	{
		float hyp = FastSQRT( ( dir.x * dir.x ) + ( dir.y * dir.y ) );
		angles.x = atanf( dir.z / hyp ) * M_RADPI;
		angles.y = atanf( dir.y / dir.x ) * M_RADPI;
		angles.z = 0.0f;
		if( dir.x >= 0.0 )
			angles.y += 180.0f;
	}

	void NormalizeVector( Vector3& v )
	{
		if (v.x > 89.0f && v.x <= 180.0f)
			v.x = 89.0f;
		while (v.x > 180.f)
			v.x -= 360.f;
		while (v.x < -89.0f)
			v.x = -89.0f;
		while (v.y > 180.f)
			v.y -= 360.f;
		while (v.y < -180.f)
		v.y += 360.f;

		v.z = 0;
	}

	void SmoothAngle( Vector3& ViewAngle, Vector3& DestAngles, float smooth )
	{
		Vector3 vecDelta = ViewAngle - DestAngles;
		NormalizeVector( vecDelta );
		DestAngles = ViewAngle - vecDelta / 100.0f * smooth;
	}

	void MakeVector( Vector3 angle, Vector3& vector )
	{
		float pitch = float( angle[ 0 ] * M_PI / 180 );
		float yaw = float( angle[ 1 ] * M_PI / 180 );
		float tmp = float( cos( pitch ) );
		vector[ 0 ] = float( -tmp * -cos( yaw ) );
		vector[ 1 ] = float( sin( yaw )*tmp );
		vector[ 2 ] = float( -sin( pitch ) );
	}

	Vector3 AngleToDirection( Vector3 angle )
	{
		// Convert angle to radians 
		angle.x = ( float )DEG2RAD( angle.x );
		angle.y = ( float )DEG2RAD( angle.y );

		float sinYaw = sin( angle.y );
		float cosYaw = cos( angle.y );

		float sinPitch = sin( angle.x );
		float cosPitch = cos( angle.x );

		Vector3 direction;
		direction.x = cosPitch * cosYaw;
		direction.y = cosPitch * sinYaw;
		direction.z = -sinPitch;

		return direction;
	}

};

CMath Math;