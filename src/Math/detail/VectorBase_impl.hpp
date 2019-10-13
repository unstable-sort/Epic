//////////////////////////////////////////////////////////////////////////////
//
//            Copyright (c) 2019 Ronnie Brohn (EpicBrownie)      
//
//                Distributed under The MIT License (MIT).
//              (See accompanying file LICENSE or copy at 
//                 https://opensource.org/licenses/MIT)
//
//           Please report any bugs, typos, or suggestions to
//             https://github.com/unstable-sort/Epic/issues
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "VectorBase_decl.h"

#include "VectorData.h"
#include "VectorSwizzler.h"

//////////////////////////////////////////////////////////////////////////////

#define SWIZZLE_1(x, name)				VectorSwizzler<T, Size, x> name
#define SWIZZLE_2(x, y, name)			VectorSwizzler<T, Size, x, y> name
#define SWIZZLE_3(x, y, z, name)		VectorSwizzler<T, Size, x, y, z> name
#define SWIZZLE_4(x, y, z, w, name)		VectorSwizzler<T, Size, x, y, z, w> name

//////////////////////////////////////////////////////////////////////////////

template<class T, size_t N> 
class Epic::detail::VectorBase
{
public:
	using value_type = T;
	using container_type = VectorData<T, N>;

	static constexpr size_t Size = N;

public:
	container_type Values;
};

template<class T>
class Epic::detail::VectorBase<T, 0>;

template<class T>
class Epic::detail::VectorBase<T, 1>
{
public:
	using value_type = T;
	using container_type = VectorData<T, 1>;

	static constexpr size_t Size = 1;

public:
	union
	{
		#ifndef NDEBUG
		struct { T _x; };
		#endif

		// Value Array
		container_type Values;

		// 1-Component VectorSwizzlers
		SWIZZLE_1(0, x);

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_XYZW)

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, xx);
		
		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, xxx);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, xxxx);

		#endif

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_UVST)

		// 1-Component VectorSwizzlers
		struct
		{
			SWIZZLE_1(0, u);
		};

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, uu);

		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, uuu);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, uuuu);

		#endif
	};
};

template<class T>
class Epic::detail::VectorBase<T, 2>
{
public:
	using value_type = T;
	using container_type = VectorData<T, 2>;

	static constexpr size_t Size = 2;

public:
	union
	{
		#ifndef NDEBUG
		struct { T _x; T _y; };
		#endif

		// Value Array
		container_type Values;

		// 1-Component VectorSwizzlers
		SWIZZLE_1(0, x);
		SWIZZLE_1(1, y);

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_XYZW)

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, xx);
		SWIZZLE_2(0, 1, xy);
		SWIZZLE_2(1, 0, yx);
		SWIZZLE_2(1, 1, yy);

		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, xxx);
		SWIZZLE_3(0, 0, 1, xxy);
		SWIZZLE_3(0, 1, 0, xyx);
		SWIZZLE_3(0, 1, 1, xyy);
		SWIZZLE_3(1, 0, 0, yxx);
		SWIZZLE_3(1, 0, 1, yxy);
		SWIZZLE_3(1, 1, 0, yyx);
		SWIZZLE_3(1, 1, 1, yyy);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, xxxx);
		SWIZZLE_4(0, 0, 0, 1, xxxy);
		SWIZZLE_4(0, 0, 1, 0, xxyx);
		SWIZZLE_4(0, 0, 1, 1, xxyy);
		SWIZZLE_4(0, 1, 0, 0, xyxx);
		SWIZZLE_4(0, 1, 0, 1, xyxy);
		SWIZZLE_4(0, 1, 1, 0, xyyx);
		SWIZZLE_4(0, 1, 1, 1, xyyy);
		SWIZZLE_4(1, 0, 0, 0, yxxx);
		SWIZZLE_4(1, 0, 0, 1, yxxy);
		SWIZZLE_4(1, 0, 1, 0, yxyx);
		SWIZZLE_4(1, 0, 1, 1, yxyy);
		SWIZZLE_4(1, 1, 0, 0, yyxx);
		SWIZZLE_4(1, 1, 0, 1, yyxy);
		SWIZZLE_4(1, 1, 1, 0, yyyx);
		SWIZZLE_4(1, 1, 1, 1, yyyy);

		#endif

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_UVST)

		// 1-Component VectorSwizzlers
		struct
		{
			SWIZZLE_1(0, u);
			SWIZZLE_1(1, v);
		};

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, uu);
		SWIZZLE_2(0, 1, uv);
		SWIZZLE_2(1, 0, vu);
		SWIZZLE_2(1, 1, vv);

		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, uuu);
		SWIZZLE_3(0, 0, 1, uuv);
		SWIZZLE_3(0, 1, 0, uvu);
		SWIZZLE_3(0, 1, 1, uvv);
		SWIZZLE_3(1, 0, 0, vuu);
		SWIZZLE_3(1, 0, 1, vuv);
		SWIZZLE_3(1, 1, 0, vvu);
		SWIZZLE_3(1, 1, 1, vvv);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, uuuu);
		SWIZZLE_4(0, 0, 0, 1, uuuv);
		SWIZZLE_4(0, 0, 1, 0, uuvu);
		SWIZZLE_4(0, 0, 1, 1, uuvv);
		SWIZZLE_4(0, 1, 0, 0, uvuu);
		SWIZZLE_4(0, 1, 0, 1, uvuv);
		SWIZZLE_4(0, 1, 1, 0, uvvu);
		SWIZZLE_4(0, 1, 1, 1, uvvv);
		SWIZZLE_4(1, 0, 0, 0, vuuu);
		SWIZZLE_4(1, 0, 0, 1, vuuv);
		SWIZZLE_4(1, 0, 1, 0, vuvu);
		SWIZZLE_4(1, 0, 1, 1, vuvv);
		SWIZZLE_4(1, 1, 0, 0, vvuu);
		SWIZZLE_4(1, 1, 0, 1, vvuv);
		SWIZZLE_4(1, 1, 1, 0, vvvu);
		SWIZZLE_4(1, 1, 1, 1, vvvv);

		#endif
	};
};

template<class T>
class Epic::detail::VectorBase<T, 3>
{
public:
	using value_type = T;
	using container_type = VectorData<T, 3>;

	static constexpr size_t Size = 3;

public:
	union
	{
		#ifndef NDEBUG
		struct { T _x; T _y; T _z; };
		#endif

		// Value Array
		container_type Values;

		// 1-Component VectorSwizzlers
		SWIZZLE_1(0, x);
		SWIZZLE_1(1, y);
		SWIZZLE_1(2, z);

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_XYZW)

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, xx);
		SWIZZLE_2(0, 1, xy);
		SWIZZLE_2(0, 2, xz);
		SWIZZLE_2(1, 0, yx);
		SWIZZLE_2(1, 1, yy);
		SWIZZLE_2(1, 2, yz);
		SWIZZLE_2(2, 0, zx);
		SWIZZLE_2(2, 1, zy);
		SWIZZLE_2(2, 2, zz);

		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, xxx);
		SWIZZLE_3(0, 0, 1, xxy);
		SWIZZLE_3(0, 0, 2, xxz);
		SWIZZLE_3(0, 1, 0, xyx);
		SWIZZLE_3(0, 1, 1, xyy);
		SWIZZLE_3(0, 1, 2, xyz);
		SWIZZLE_3(0, 2, 0, xzx);
		SWIZZLE_3(0, 2, 1, xzy);
		SWIZZLE_3(0, 2, 2, xzz);
		SWIZZLE_3(1, 0, 0, yxx);
		SWIZZLE_3(1, 0, 1, yxy);
		SWIZZLE_3(1, 0, 2, yxz);
		SWIZZLE_3(1, 1, 0, yyx);
		SWIZZLE_3(1, 1, 1, yyy);
		SWIZZLE_3(1, 1, 2, yyz);
		SWIZZLE_3(1, 2, 0, yzx);
		SWIZZLE_3(1, 2, 1, yzy);
		SWIZZLE_3(1, 2, 2, yzz); 
		SWIZZLE_3(2, 0, 0, zxx);
		SWIZZLE_3(2, 0, 1, zxy);
		SWIZZLE_3(2, 0, 2, zxz);
		SWIZZLE_3(2, 1, 0, zyx);
		SWIZZLE_3(2, 1, 1, zyy);
		SWIZZLE_3(2, 1, 2, zyz);
		SWIZZLE_3(2, 2, 0, zzx);
		SWIZZLE_3(2, 2, 1, zzy);
		SWIZZLE_3(2, 2, 2, zzz);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, xxxx);
		SWIZZLE_4(0, 0, 0, 1, xxxy);
		SWIZZLE_4(0, 0, 0, 2, xxxz);
		SWIZZLE_4(0, 0, 1, 0, xxyx);
		SWIZZLE_4(0, 0, 1, 1, xxyy);
		SWIZZLE_4(0, 0, 1, 2, xxyz);
		SWIZZLE_4(0, 0, 2, 0, xxzx);
		SWIZZLE_4(0, 0, 2, 1, xxzy);
		SWIZZLE_4(0, 0, 2, 2, xxzz);
		SWIZZLE_4(0, 1, 0, 0, xyxx);
		SWIZZLE_4(0, 1, 0, 1, xyxy);
		SWIZZLE_4(0, 1, 0, 2, xyxz);
		SWIZZLE_4(0, 1, 1, 0, xyyx);
		SWIZZLE_4(0, 1, 1, 1, xyyy);
		SWIZZLE_4(0, 1, 1, 2, xyyz);
		SWIZZLE_4(0, 1, 2, 0, xyzx);
		SWIZZLE_4(0, 1, 2, 1, xyzy);
		SWIZZLE_4(0, 1, 2, 2, xyzz);
		SWIZZLE_4(0, 2, 0, 0, xzxx);
		SWIZZLE_4(0, 2, 0, 1, xzxy);
		SWIZZLE_4(0, 2, 0, 2, xzxz);
		SWIZZLE_4(0, 2, 1, 0, xzyx);
		SWIZZLE_4(0, 2, 1, 1, xzyy);
		SWIZZLE_4(0, 2, 1, 2, xzyz);
		SWIZZLE_4(0, 2, 2, 0, xzzx);
		SWIZZLE_4(0, 2, 2, 1, xzzy);
		SWIZZLE_4(0, 2, 2, 2, xzzz);
		SWIZZLE_4(1, 0, 0, 0, yxxx);
		SWIZZLE_4(1, 0, 0, 1, yxxy);
		SWIZZLE_4(1, 0, 0, 2, yxxz);
		SWIZZLE_4(1, 0, 1, 0, yxyx);
		SWIZZLE_4(1, 0, 1, 1, yxyy);
		SWIZZLE_4(1, 0, 1, 2, yxyz);
		SWIZZLE_4(1, 0, 2, 0, yxzx);
		SWIZZLE_4(1, 0, 2, 1, yxzy);
		SWIZZLE_4(1, 0, 2, 2, yxzz);
		SWIZZLE_4(1, 1, 0, 0, yyxx);
		SWIZZLE_4(1, 1, 0, 1, yyxy);
		SWIZZLE_4(1, 1, 0, 2, yyxz);
		SWIZZLE_4(1, 1, 1, 0, yyyx);
		SWIZZLE_4(1, 1, 1, 1, yyyy);
		SWIZZLE_4(1, 1, 1, 2, yyyz);
		SWIZZLE_4(1, 1, 2, 0, yyzx);
		SWIZZLE_4(1, 1, 2, 1, yyzy);
		SWIZZLE_4(1, 1, 2, 2, yyzz);
		SWIZZLE_4(1, 2, 0, 0, yzxx);
		SWIZZLE_4(1, 2, 0, 1, yzxy);
		SWIZZLE_4(1, 2, 0, 2, yzxz);
		SWIZZLE_4(1, 2, 1, 0, yzyx);
		SWIZZLE_4(1, 2, 1, 1, yzyy);
		SWIZZLE_4(1, 2, 1, 2, yzyz);
		SWIZZLE_4(1, 2, 2, 0, yzzx);
		SWIZZLE_4(1, 2, 2, 1, yzzy);
		SWIZZLE_4(1, 2, 2, 2, yzzz);
		SWIZZLE_4(2, 0, 0, 0, zxxx);
		SWIZZLE_4(2, 0, 0, 1, zxxy);
		SWIZZLE_4(2, 0, 0, 2, zxxz);
		SWIZZLE_4(2, 0, 1, 0, zxyx);
		SWIZZLE_4(2, 0, 1, 1, zxyy);
		SWIZZLE_4(2, 0, 1, 2, zxyz);
		SWIZZLE_4(2, 0, 2, 0, zxzx);
		SWIZZLE_4(2, 0, 2, 1, zxzy);
		SWIZZLE_4(2, 0, 2, 2, zxzz);
		SWIZZLE_4(2, 1, 0, 0, zyxx);
		SWIZZLE_4(2, 1, 0, 1, zyxy);
		SWIZZLE_4(2, 1, 0, 2, zyxz);
		SWIZZLE_4(2, 1, 1, 0, zyyx);
		SWIZZLE_4(2, 1, 1, 1, zyyy);
		SWIZZLE_4(2, 1, 1, 2, zyyz);
		SWIZZLE_4(2, 1, 2, 0, zyzx);
		SWIZZLE_4(2, 1, 2, 1, zyzy);
		SWIZZLE_4(2, 1, 2, 2, zyzz);
		SWIZZLE_4(2, 2, 0, 0, zzxx);
		SWIZZLE_4(2, 2, 0, 1, zzxy);
		SWIZZLE_4(2, 2, 0, 2, zzxz);
		SWIZZLE_4(2, 2, 1, 0, zzyx);
		SWIZZLE_4(2, 2, 1, 1, zzyy);
		SWIZZLE_4(2, 2, 1, 2, zzyz);
		SWIZZLE_4(2, 2, 2, 0, zzzx);
		SWIZZLE_4(2, 2, 2, 1, zzzy);
		SWIZZLE_4(2, 2, 2, 2, zzzz);

		#endif

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_UVST)

		// 1-Component VectorSwizzlers
		struct
		{
			SWIZZLE_1(0, u);
			SWIZZLE_1(1, v);
			SWIZZLE_1(2, s);
		};

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, uu);
		SWIZZLE_2(0, 1, uv);
		SWIZZLE_2(0, 2, us);
		SWIZZLE_2(1, 0, vu);
		SWIZZLE_2(1, 1, vv);
		SWIZZLE_2(1, 2, vs);
		SWIZZLE_2(2, 0, su);
		SWIZZLE_2(2, 1, sv);
		SWIZZLE_2(2, 2, ss);

		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, uuu);
		SWIZZLE_3(0, 0, 1, uuv);
		SWIZZLE_3(0, 0, 2, uus);
		SWIZZLE_3(0, 1, 0, uvu);
		SWIZZLE_3(0, 1, 1, uvv);
		SWIZZLE_3(0, 1, 2, uvs);
		SWIZZLE_3(0, 2, 0, usu);
		SWIZZLE_3(0, 2, 1, usv);
		SWIZZLE_3(0, 2, 2, uss);
		SWIZZLE_3(1, 0, 0, vuu);
		SWIZZLE_3(1, 0, 1, vuv);
		SWIZZLE_3(1, 0, 2, vus);
		SWIZZLE_3(1, 1, 0, vvu);
		SWIZZLE_3(1, 1, 1, vvv);
		SWIZZLE_3(1, 1, 2, vvs);
		SWIZZLE_3(1, 2, 0, vsu);
		SWIZZLE_3(1, 2, 1, vsv);
		SWIZZLE_3(1, 2, 2, vss);
		SWIZZLE_3(2, 0, 0, suu);
		SWIZZLE_3(2, 0, 1, suv);
		SWIZZLE_3(2, 0, 2, sus);
		SWIZZLE_3(2, 1, 0, svu);
		SWIZZLE_3(2, 1, 1, svv);
		SWIZZLE_3(2, 1, 2, svs);
		SWIZZLE_3(2, 2, 0, ssu);
		SWIZZLE_3(2, 2, 1, ssv);
		SWIZZLE_3(2, 2, 2, sss);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, uuuu);
		SWIZZLE_4(0, 0, 0, 1, uuuv);
		SWIZZLE_4(0, 0, 0, 2, uuus);
		SWIZZLE_4(0, 0, 1, 0, uuvu);
		SWIZZLE_4(0, 0, 1, 1, uuvv);
		SWIZZLE_4(0, 0, 1, 2, uuvs);
		SWIZZLE_4(0, 0, 2, 0, uusu);
		SWIZZLE_4(0, 0, 2, 1, uusv);
		SWIZZLE_4(0, 0, 2, 2, uuss);
		SWIZZLE_4(0, 1, 0, 0, uvuu);
		SWIZZLE_4(0, 1, 0, 1, uvuv);
		SWIZZLE_4(0, 1, 0, 2, uvus);
		SWIZZLE_4(0, 1, 1, 0, uvvu);
		SWIZZLE_4(0, 1, 1, 1, uvvv);
		SWIZZLE_4(0, 1, 1, 2, uvvs);
		SWIZZLE_4(0, 1, 2, 0, uvsu);
		SWIZZLE_4(0, 1, 2, 1, uvsv);
		SWIZZLE_4(0, 1, 2, 2, uvss);
		SWIZZLE_4(0, 2, 0, 0, usuu);
		SWIZZLE_4(0, 2, 0, 1, usuv);
		SWIZZLE_4(0, 2, 0, 2, usus);
		SWIZZLE_4(0, 2, 1, 0, usvu);
		SWIZZLE_4(0, 2, 1, 1, usvv);
		SWIZZLE_4(0, 2, 1, 2, usvs);
		SWIZZLE_4(0, 2, 2, 0, ussu);
		SWIZZLE_4(0, 2, 2, 1, ussv);
		SWIZZLE_4(0, 2, 2, 2, usss);
		SWIZZLE_4(1, 0, 0, 0, vuuu);
		SWIZZLE_4(1, 0, 0, 1, vuuv);
		SWIZZLE_4(1, 0, 0, 2, vuus);
		SWIZZLE_4(1, 0, 1, 0, vuvu);
		SWIZZLE_4(1, 0, 1, 1, vuvv);
		SWIZZLE_4(1, 0, 1, 2, vuvs);
		SWIZZLE_4(1, 0, 2, 0, vusu);
		SWIZZLE_4(1, 0, 2, 1, vusv);
		SWIZZLE_4(1, 0, 2, 2, vuss);
		SWIZZLE_4(1, 1, 0, 0, vvuu);
		SWIZZLE_4(1, 1, 0, 1, vvuv);
		SWIZZLE_4(1, 1, 0, 2, vvus);
		SWIZZLE_4(1, 1, 1, 0, vvvu);
		SWIZZLE_4(1, 1, 1, 1, vvvv);
		SWIZZLE_4(1, 1, 1, 2, vvvs);
		SWIZZLE_4(1, 1, 2, 0, vvsu);
		SWIZZLE_4(1, 1, 2, 1, vvsv);
		SWIZZLE_4(1, 1, 2, 2, vvss);
		SWIZZLE_4(1, 2, 0, 0, vsuu);
		SWIZZLE_4(1, 2, 0, 1, vsuv);
		SWIZZLE_4(1, 2, 0, 2, vsus);
		SWIZZLE_4(1, 2, 1, 0, vsvu);
		SWIZZLE_4(1, 2, 1, 1, vsvv);
		SWIZZLE_4(1, 2, 1, 2, vsvs);
		SWIZZLE_4(1, 2, 2, 0, vssu);
		SWIZZLE_4(1, 2, 2, 1, vssv);
		SWIZZLE_4(1, 2, 2, 2, vsss);
		SWIZZLE_4(2, 0, 0, 0, suuu);
		SWIZZLE_4(2, 0, 0, 1, suuv);
		SWIZZLE_4(2, 0, 0, 2, suus);
		SWIZZLE_4(2, 0, 1, 0, suvu);
		SWIZZLE_4(2, 0, 1, 1, suvv);
		SWIZZLE_4(2, 0, 1, 2, suvs);
		SWIZZLE_4(2, 0, 2, 0, susu);
		SWIZZLE_4(2, 0, 2, 1, susv);
		SWIZZLE_4(2, 0, 2, 2, suss);
		SWIZZLE_4(2, 1, 0, 0, svuu);
		SWIZZLE_4(2, 1, 0, 1, svuv);
		SWIZZLE_4(2, 1, 0, 2, svus);
		SWIZZLE_4(2, 1, 1, 0, svvu);
		SWIZZLE_4(2, 1, 1, 1, svvv);
		SWIZZLE_4(2, 1, 1, 2, svvs);
		SWIZZLE_4(2, 1, 2, 0, svsu);
		SWIZZLE_4(2, 1, 2, 1, svsv);
		SWIZZLE_4(2, 1, 2, 2, svss);
		SWIZZLE_4(2, 2, 0, 0, ssuu);
		SWIZZLE_4(2, 2, 0, 1, ssuv);
		SWIZZLE_4(2, 2, 0, 2, ssus);
		SWIZZLE_4(2, 2, 1, 0, ssvu);
		SWIZZLE_4(2, 2, 1, 1, ssvv);
		SWIZZLE_4(2, 2, 1, 2, ssvs);
		SWIZZLE_4(2, 2, 2, 0, sssu);
		SWIZZLE_4(2, 2, 2, 1, sssv);
		SWIZZLE_4(2, 2, 2, 2, ssss);

		#endif
	};
};

template<class T>
class Epic::detail::VectorBase<T, 4>
{
public:
	using value_type = T;
	using container_type = VectorData<T, 4>;

	static constexpr size_t Size = 4;

public:
	union
	{
		#ifndef NDEBUG
		struct { T _x; T _y; T _z; T _w; };
		#endif

		// Value Array
		container_type Values;

		// 1-Component VectorSwizzlers
		SWIZZLE_1(0, x);
		SWIZZLE_1(1, y);
		SWIZZLE_1(2, z);
		SWIZZLE_1(3, w);

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_XYZW)

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, xx);
		SWIZZLE_2(0, 1, xy);
		SWIZZLE_2(0, 2, xz);
		SWIZZLE_2(0, 3, xw);
		SWIZZLE_2(1, 0, yx);
		SWIZZLE_2(1, 1, yy);
		SWIZZLE_2(1, 2, yz);
		SWIZZLE_2(1, 3, yw);
		SWIZZLE_2(2, 0, zx);
		SWIZZLE_2(2, 1, zy);
		SWIZZLE_2(2, 2, zz);
		SWIZZLE_2(2, 3, zw);
		SWIZZLE_2(3, 0, wx);
		SWIZZLE_2(3, 1, wy);
		SWIZZLE_2(3, 2, wz);
		SWIZZLE_2(3, 3, ww);

		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, xxx);
		SWIZZLE_3(0, 0, 1, xxy);
		SWIZZLE_3(0, 0, 2, xxz);
		SWIZZLE_3(0, 0, 3, xxw);
		SWIZZLE_3(0, 1, 0, xyx);
		SWIZZLE_3(0, 1, 1, xyy);
		SWIZZLE_3(0, 1, 2, xyz);
		SWIZZLE_3(0, 1, 3, xyw);
		SWIZZLE_3(0, 2, 0, xzx);
		SWIZZLE_3(0, 2, 1, xzy);
		SWIZZLE_3(0, 2, 2, xzz);
		SWIZZLE_3(0, 2, 3, xzw);
		SWIZZLE_3(0, 3, 0, xwx);
		SWIZZLE_3(0, 3, 1, xwy);
		SWIZZLE_3(0, 3, 2, xwz);
		SWIZZLE_3(0, 3, 3, xww);
		SWIZZLE_3(1, 0, 0, yxx);
		SWIZZLE_3(1, 0, 1, yxy);
		SWIZZLE_3(1, 0, 2, yxz);
		SWIZZLE_3(1, 0, 3, yxw);
		SWIZZLE_3(1, 1, 0, yyx);
		SWIZZLE_3(1, 1, 1, yyy);
		SWIZZLE_3(1, 1, 2, yyz);
		SWIZZLE_3(1, 1, 3, yyw);
		SWIZZLE_3(1, 2, 0, yzx);
		SWIZZLE_3(1, 2, 1, yzy);
		SWIZZLE_3(1, 2, 2, yzz);
		SWIZZLE_3(1, 2, 3, yzw);
		SWIZZLE_3(1, 3, 0, ywx);
		SWIZZLE_3(1, 3, 1, ywy);
		SWIZZLE_3(1, 3, 2, ywz);
		SWIZZLE_3(1, 3, 3, yww);
		SWIZZLE_3(2, 0, 0, zxx);
		SWIZZLE_3(2, 0, 1, zxy);
		SWIZZLE_3(2, 0, 2, zxz);
		SWIZZLE_3(2, 0, 3, zxw);
		SWIZZLE_3(2, 1, 0, zyx);
		SWIZZLE_3(2, 1, 1, zyy);
		SWIZZLE_3(2, 1, 2, zyz);
		SWIZZLE_3(2, 1, 3, zyw);
		SWIZZLE_3(2, 2, 0, zzx);
		SWIZZLE_3(2, 2, 1, zzy);
		SWIZZLE_3(2, 2, 2, zzz);
		SWIZZLE_3(2, 2, 3, zzw);
		SWIZZLE_3(2, 3, 0, zwx);
		SWIZZLE_3(2, 3, 1, zwy);
		SWIZZLE_3(2, 3, 2, zwz);
		SWIZZLE_3(2, 3, 3, zww);
		SWIZZLE_3(3, 0, 0, wxx);
		SWIZZLE_3(3, 0, 1, wxy);
		SWIZZLE_3(3, 0, 2, wxz);
		SWIZZLE_3(3, 0, 3, wxw);
		SWIZZLE_3(3, 1, 0, wyx);
		SWIZZLE_3(3, 1, 1, wyy);
		SWIZZLE_3(3, 1, 2, wyz);
		SWIZZLE_3(3, 1, 3, wyw);
		SWIZZLE_3(3, 2, 0, wzx);
		SWIZZLE_3(3, 2, 1, wzy);
		SWIZZLE_3(3, 2, 2, wzz);
		SWIZZLE_3(3, 2, 3, wzw);
		SWIZZLE_3(3, 3, 0, wwx);
		SWIZZLE_3(3, 3, 1, wwy);
		SWIZZLE_3(3, 3, 2, wwz);
		SWIZZLE_3(3, 3, 3, www);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, xxxx);
		SWIZZLE_4(0, 0, 0, 1, xxxy);
		SWIZZLE_4(0, 0, 0, 2, xxxz);
		SWIZZLE_4(0, 0, 0, 3, xxxw);
		SWIZZLE_4(0, 0, 1, 0, xxyx);
		SWIZZLE_4(0, 0, 1, 1, xxyy);
		SWIZZLE_4(0, 0, 1, 2, xxyz);
		SWIZZLE_4(0, 0, 1, 3, xxyw);
		SWIZZLE_4(0, 0, 2, 0, xxzx);
		SWIZZLE_4(0, 0, 2, 1, xxzy);
		SWIZZLE_4(0, 0, 2, 2, xxzz);
		SWIZZLE_4(0, 0, 2, 3, xxzw);
		SWIZZLE_4(0, 0, 3, 0, xxwx);
		SWIZZLE_4(0, 0, 3, 1, xxwy);
		SWIZZLE_4(0, 0, 3, 2, xxwz);
		SWIZZLE_4(0, 0, 3, 3, xxww);
		SWIZZLE_4(0, 1, 0, 0, xyxx);
		SWIZZLE_4(0, 1, 0, 1, xyxy);
		SWIZZLE_4(0, 1, 0, 2, xyxz);
		SWIZZLE_4(0, 1, 0, 3, xyxw);
		SWIZZLE_4(0, 1, 1, 0, xyyx);
		SWIZZLE_4(0, 1, 1, 1, xyyy);
		SWIZZLE_4(0, 1, 1, 2, xyyz);
		SWIZZLE_4(0, 1, 1, 3, xyyw);
		SWIZZLE_4(0, 1, 2, 0, xyzx);
		SWIZZLE_4(0, 1, 2, 1, xyzy);
		SWIZZLE_4(0, 1, 2, 2, xyzz);
		SWIZZLE_4(0, 1, 2, 3, xyzw);
		SWIZZLE_4(0, 1, 3, 0, xywx);
		SWIZZLE_4(0, 1, 3, 1, xywy);
		SWIZZLE_4(0, 1, 3, 2, xywz);
		SWIZZLE_4(0, 1, 3, 3, xyww);
		SWIZZLE_4(0, 2, 0, 0, xzxx);
		SWIZZLE_4(0, 2, 0, 1, xzxy);
		SWIZZLE_4(0, 2, 0, 2, xzxz);
		SWIZZLE_4(0, 2, 0, 3, xzxw);
		SWIZZLE_4(0, 2, 1, 0, xzyx);
		SWIZZLE_4(0, 2, 1, 1, xzyy);
		SWIZZLE_4(0, 2, 1, 2, xzyz);
		SWIZZLE_4(0, 2, 1, 3, xzyw);
		SWIZZLE_4(0, 2, 2, 0, xzzx);
		SWIZZLE_4(0, 2, 2, 1, xzzy);
		SWIZZLE_4(0, 2, 2, 2, xzzz);
		SWIZZLE_4(0, 2, 2, 3, xzzw);
		SWIZZLE_4(0, 2, 3, 0, xzwx);
		SWIZZLE_4(0, 2, 3, 1, xzwy);
		SWIZZLE_4(0, 2, 3, 2, xzwz);
		SWIZZLE_4(0, 2, 3, 3, xzww);
		SWIZZLE_4(0, 3, 0, 0, xwxx);
		SWIZZLE_4(0, 3, 0, 1, xwxy);
		SWIZZLE_4(0, 3, 0, 2, xwxz);
		SWIZZLE_4(0, 3, 0, 3, xwxw);
		SWIZZLE_4(0, 3, 1, 0, xwyx);
		SWIZZLE_4(0, 3, 1, 1, xwyy);
		SWIZZLE_4(0, 3, 1, 2, xwyz);
		SWIZZLE_4(0, 3, 1, 3, xwyw);
		SWIZZLE_4(0, 3, 2, 0, xwzx);
		SWIZZLE_4(0, 3, 2, 1, xwzy);
		SWIZZLE_4(0, 3, 2, 2, xwzz);
		SWIZZLE_4(0, 3, 2, 3, xwzw);
		SWIZZLE_4(0, 3, 3, 0, xwwx);
		SWIZZLE_4(0, 3, 3, 1, xwwy);
		SWIZZLE_4(0, 3, 3, 2, xwwz);
		SWIZZLE_4(0, 3, 3, 3, xwww);
		SWIZZLE_4(1, 0, 0, 0, yxxx);
		SWIZZLE_4(1, 0, 0, 1, yxxy);
		SWIZZLE_4(1, 0, 0, 2, yxxz);
		SWIZZLE_4(1, 0, 0, 3, yxxw);
		SWIZZLE_4(1, 0, 1, 0, yxyx);
		SWIZZLE_4(1, 0, 1, 1, yxyy);
		SWIZZLE_4(1, 0, 1, 2, yxyz);
		SWIZZLE_4(1, 0, 1, 3, yxyw);
		SWIZZLE_4(1, 0, 2, 0, yxzx);
		SWIZZLE_4(1, 0, 2, 1, yxzy);
		SWIZZLE_4(1, 0, 2, 2, yxzz);
		SWIZZLE_4(1, 0, 2, 3, yxzw);
		SWIZZLE_4(1, 0, 3, 0, yxwx);
		SWIZZLE_4(1, 0, 3, 1, yxwy);
		SWIZZLE_4(1, 0, 3, 2, yxwz);
		SWIZZLE_4(1, 0, 3, 3, yxww);
		SWIZZLE_4(1, 1, 0, 0, yyxx);
		SWIZZLE_4(1, 1, 0, 1, yyxy);
		SWIZZLE_4(1, 1, 0, 2, yyxz);
		SWIZZLE_4(1, 1, 0, 3, yyxw);
		SWIZZLE_4(1, 1, 1, 0, yyyx);
		SWIZZLE_4(1, 1, 1, 1, yyyy);
		SWIZZLE_4(1, 1, 1, 2, yyyz);
		SWIZZLE_4(1, 1, 1, 3, yyyw);
		SWIZZLE_4(1, 1, 2, 0, yyzx);
		SWIZZLE_4(1, 1, 2, 1, yyzy);
		SWIZZLE_4(1, 1, 2, 2, yyzz);
		SWIZZLE_4(1, 1, 2, 3, yyzw);
		SWIZZLE_4(1, 1, 3, 0, yywx);
		SWIZZLE_4(1, 1, 3, 1, yywy);
		SWIZZLE_4(1, 1, 3, 2, yywz);
		SWIZZLE_4(1, 1, 3, 3, yyww);
		SWIZZLE_4(1, 2, 0, 0, yzxx);
		SWIZZLE_4(1, 2, 0, 1, yzxy);
		SWIZZLE_4(1, 2, 0, 2, yzxz);
		SWIZZLE_4(1, 2, 0, 3, yzxw);
		SWIZZLE_4(1, 2, 1, 0, yzyx);
		SWIZZLE_4(1, 2, 1, 1, yzyy);
		SWIZZLE_4(1, 2, 1, 2, yzyz);
		SWIZZLE_4(1, 2, 1, 3, yzyw);
		SWIZZLE_4(1, 2, 2, 0, yzzx);
		SWIZZLE_4(1, 2, 2, 1, yzzy);
		SWIZZLE_4(1, 2, 2, 2, yzzz);
		SWIZZLE_4(1, 2, 2, 3, yzzw);
		SWIZZLE_4(1, 2, 3, 0, yzwx);
		SWIZZLE_4(1, 2, 3, 1, yzwy);
		SWIZZLE_4(1, 2, 3, 2, yzwz);
		SWIZZLE_4(1, 2, 3, 3, yzww);
		SWIZZLE_4(1, 3, 0, 0, ywxx);
		SWIZZLE_4(1, 3, 0, 1, ywxy);
		SWIZZLE_4(1, 3, 0, 2, ywxz);
		SWIZZLE_4(1, 3, 0, 3, ywxw);
		SWIZZLE_4(1, 3, 1, 0, ywyx);
		SWIZZLE_4(1, 3, 1, 1, ywyy);
		SWIZZLE_4(1, 3, 1, 2, ywyz);
		SWIZZLE_4(1, 3, 1, 3, ywyw);
		SWIZZLE_4(1, 3, 2, 0, ywzx);
		SWIZZLE_4(1, 3, 2, 1, ywzy);
		SWIZZLE_4(1, 3, 2, 2, ywzz);
		SWIZZLE_4(1, 3, 2, 3, ywzw);
		SWIZZLE_4(1, 3, 3, 0, ywwx);
		SWIZZLE_4(1, 3, 3, 1, ywwy);
		SWIZZLE_4(1, 3, 3, 2, ywwz);
		SWIZZLE_4(1, 3, 3, 3, ywww);
		SWIZZLE_4(2, 0, 0, 0, zxxx);
		SWIZZLE_4(2, 0, 0, 1, zxxy);
		SWIZZLE_4(2, 0, 0, 2, zxxz);
		SWIZZLE_4(2, 0, 0, 3, zxxw);
		SWIZZLE_4(2, 0, 1, 0, zxyx);
		SWIZZLE_4(2, 0, 1, 1, zxyy);
		SWIZZLE_4(2, 0, 1, 2, zxyz);
		SWIZZLE_4(2, 0, 1, 3, zxyw);
		SWIZZLE_4(2, 0, 2, 0, zxzx);
		SWIZZLE_4(2, 0, 2, 1, zxzy);
		SWIZZLE_4(2, 0, 2, 2, zxzz);
		SWIZZLE_4(2, 0, 2, 3, zxzw);
		SWIZZLE_4(2, 0, 3, 0, zxwx);
		SWIZZLE_4(2, 0, 3, 1, zxwy);
		SWIZZLE_4(2, 0, 3, 2, zxwz);
		SWIZZLE_4(2, 0, 3, 3, zxww);
		SWIZZLE_4(2, 1, 0, 0, zyxx);
		SWIZZLE_4(2, 1, 0, 1, zyxy);
		SWIZZLE_4(2, 1, 0, 2, zyxz);
		SWIZZLE_4(2, 1, 0, 3, zyxw);
		SWIZZLE_4(2, 1, 1, 0, zyyx);
		SWIZZLE_4(2, 1, 1, 1, zyyy);
		SWIZZLE_4(2, 1, 1, 2, zyyz);
		SWIZZLE_4(2, 1, 1, 3, zyyw);
		SWIZZLE_4(2, 1, 2, 0, zyzx);
		SWIZZLE_4(2, 1, 2, 1, zyzy);
		SWIZZLE_4(2, 1, 2, 2, zyzz);
		SWIZZLE_4(2, 1, 2, 3, zyzw);
		SWIZZLE_4(2, 1, 3, 0, zywx);
		SWIZZLE_4(2, 1, 3, 1, zywy);
		SWIZZLE_4(2, 1, 3, 2, zywz);
		SWIZZLE_4(2, 1, 3, 3, zyww);
		SWIZZLE_4(2, 2, 0, 0, zzxx);
		SWIZZLE_4(2, 2, 0, 1, zzxy);
		SWIZZLE_4(2, 2, 0, 2, zzxz);
		SWIZZLE_4(2, 2, 0, 3, zzxw);
		SWIZZLE_4(2, 2, 1, 0, zzyx);
		SWIZZLE_4(2, 2, 1, 1, zzyy);
		SWIZZLE_4(2, 2, 1, 2, zzyz);
		SWIZZLE_4(2, 2, 1, 3, zzyw);
		SWIZZLE_4(2, 2, 2, 0, zzzx);
		SWIZZLE_4(2, 2, 2, 1, zzzy);
		SWIZZLE_4(2, 2, 2, 2, zzzz);
		SWIZZLE_4(2, 2, 2, 3, zzzw);
		SWIZZLE_4(2, 2, 3, 0, zzwx);
		SWIZZLE_4(2, 2, 3, 1, zzwy);
		SWIZZLE_4(2, 2, 3, 2, zzwz);
		SWIZZLE_4(2, 2, 3, 3, zzww);
		SWIZZLE_4(2, 3, 0, 0, zwxx);
		SWIZZLE_4(2, 3, 0, 1, zwxy);
		SWIZZLE_4(2, 3, 0, 2, zwxz);
		SWIZZLE_4(2, 3, 0, 3, zwxw);
		SWIZZLE_4(2, 3, 1, 0, zwyx);
		SWIZZLE_4(2, 3, 1, 1, zwyy);
		SWIZZLE_4(2, 3, 1, 2, zwyz);
		SWIZZLE_4(2, 3, 1, 3, zwyw);
		SWIZZLE_4(2, 3, 2, 0, zwzx);
		SWIZZLE_4(2, 3, 2, 1, zwzy);
		SWIZZLE_4(2, 3, 2, 2, zwzz);
		SWIZZLE_4(2, 3, 2, 3, zwzw);
		SWIZZLE_4(2, 3, 3, 0, zwwx);
		SWIZZLE_4(2, 3, 3, 1, zwwy);
		SWIZZLE_4(2, 3, 3, 2, zwwz);
		SWIZZLE_4(2, 3, 3, 3, zwww);
		SWIZZLE_4(3, 0, 0, 0, wxxx);
		SWIZZLE_4(3, 0, 0, 1, wxxy);
		SWIZZLE_4(3, 0, 0, 2, wxxz);
		SWIZZLE_4(3, 0, 0, 3, wxxw);
		SWIZZLE_4(3, 0, 1, 0, wxyx);
		SWIZZLE_4(3, 0, 1, 1, wxyy);
		SWIZZLE_4(3, 0, 1, 2, wxyz);
		SWIZZLE_4(3, 0, 1, 3, wxyw);
		SWIZZLE_4(3, 0, 2, 0, wxzx);
		SWIZZLE_4(3, 0, 2, 1, wxzy);
		SWIZZLE_4(3, 0, 2, 2, wxzz);
		SWIZZLE_4(3, 0, 2, 3, wxzw);
		SWIZZLE_4(3, 0, 3, 0, wxwx);
		SWIZZLE_4(3, 0, 3, 1, wxwy);
		SWIZZLE_4(3, 0, 3, 2, wxwz);
		SWIZZLE_4(3, 0, 3, 3, wxww);
		SWIZZLE_4(3, 1, 0, 0, wyxx);
		SWIZZLE_4(3, 1, 0, 1, wyxy);
		SWIZZLE_4(3, 1, 0, 2, wyxz);
		SWIZZLE_4(3, 1, 0, 3, wyxw);
		SWIZZLE_4(3, 1, 1, 0, wyyx);
		SWIZZLE_4(3, 1, 1, 1, wyyy);
		SWIZZLE_4(3, 1, 1, 2, wyyz);
		SWIZZLE_4(3, 1, 1, 3, wyyw);
		SWIZZLE_4(3, 1, 2, 0, wyzx);
		SWIZZLE_4(3, 1, 2, 1, wyzy);
		SWIZZLE_4(3, 1, 2, 2, wyzz);
		SWIZZLE_4(3, 1, 2, 3, wyzw);
		SWIZZLE_4(3, 1, 3, 0, wywx);
		SWIZZLE_4(3, 1, 3, 1, wywy);
		SWIZZLE_4(3, 1, 3, 2, wywz);
		SWIZZLE_4(3, 1, 3, 3, wyww);
		SWIZZLE_4(3, 2, 0, 0, wzxx);
		SWIZZLE_4(3, 2, 0, 1, wzxy);
		SWIZZLE_4(3, 2, 0, 2, wzxz);
		SWIZZLE_4(3, 2, 0, 3, wzxw);
		SWIZZLE_4(3, 2, 1, 0, wzyx);
		SWIZZLE_4(3, 2, 1, 1, wzyy);
		SWIZZLE_4(3, 2, 1, 2, wzyz);
		SWIZZLE_4(3, 2, 1, 3, wzyw);
		SWIZZLE_4(3, 2, 2, 0, wzzx);
		SWIZZLE_4(3, 2, 2, 1, wzzy);
		SWIZZLE_4(3, 2, 2, 2, wzzz);
		SWIZZLE_4(3, 2, 2, 3, wzzw);
		SWIZZLE_4(3, 2, 3, 0, wzwx);
		SWIZZLE_4(3, 2, 3, 1, wzwy);
		SWIZZLE_4(3, 2, 3, 2, wzwz);
		SWIZZLE_4(3, 2, 3, 3, wzww);
		SWIZZLE_4(3, 3, 0, 0, wwxx);
		SWIZZLE_4(3, 3, 0, 1, wwxy);
		SWIZZLE_4(3, 3, 0, 2, wwxz);
		SWIZZLE_4(3, 3, 0, 3, wwxw);
		SWIZZLE_4(3, 3, 1, 0, wwyx);
		SWIZZLE_4(3, 3, 1, 1, wwyy);
		SWIZZLE_4(3, 3, 1, 2, wwyz);
		SWIZZLE_4(3, 3, 1, 3, wwyw);
		SWIZZLE_4(3, 3, 2, 0, wwzx);
		SWIZZLE_4(3, 3, 2, 1, wwzy);
		SWIZZLE_4(3, 3, 2, 2, wwzz);
		SWIZZLE_4(3, 3, 2, 3, wwzw);
		SWIZZLE_4(3, 3, 3, 0, wwwx);
		SWIZZLE_4(3, 3, 3, 1, wwwy);
		SWIZZLE_4(3, 3, 3, 2, wwwz);
		SWIZZLE_4(3, 3, 3, 3, wwww);

		#endif

		#if defined(EPIC_SWIZZLE) || defined(EPIC_SWIZZLE_UVST)

		// 1-Component VectorSwizzlers
		struct
		{
			SWIZZLE_1(0, u);
			SWIZZLE_1(1, v);
			SWIZZLE_1(2, s);
			SWIZZLE_1(3, t);
		};

		// 2-Component VectorSwizzlers
		SWIZZLE_2(0, 0, uu);
		SWIZZLE_2(0, 1, uv);
		SWIZZLE_2(0, 2, us);
		SWIZZLE_2(0, 3, ut);
		SWIZZLE_2(1, 0, vu);
		SWIZZLE_2(1, 1, vv);
		SWIZZLE_2(1, 2, vs);
		SWIZZLE_2(1, 3, vt);
		SWIZZLE_2(2, 0, su);
		SWIZZLE_2(2, 1, sv);
		SWIZZLE_2(2, 2, ss);
		SWIZZLE_2(2, 3, st);
		SWIZZLE_2(3, 0, tu);
		SWIZZLE_2(3, 1, tv);
		SWIZZLE_2(3, 2, ts);
		SWIZZLE_2(3, 3, tt);

		// 3-Component VectorSwizzlers
		SWIZZLE_3(0, 0, 0, uuu);
		SWIZZLE_3(0, 0, 1, uuv);
		SWIZZLE_3(0, 0, 2, uus);
		SWIZZLE_3(0, 0, 3, uut);
		SWIZZLE_3(0, 1, 0, uvu);
		SWIZZLE_3(0, 1, 1, uvv);
		SWIZZLE_3(0, 1, 2, uvs);
		SWIZZLE_3(0, 1, 3, uvt);
		SWIZZLE_3(0, 2, 0, usu);
		SWIZZLE_3(0, 2, 1, usv);
		SWIZZLE_3(0, 2, 2, uss);
		SWIZZLE_3(0, 2, 3, ust);
		SWIZZLE_3(0, 3, 0, utu);
		SWIZZLE_3(0, 3, 1, utv);
		SWIZZLE_3(0, 3, 2, uts);
		SWIZZLE_3(0, 3, 3, utt);
		SWIZZLE_3(1, 0, 0, vuu);
		SWIZZLE_3(1, 0, 1, vuv);
		SWIZZLE_3(1, 0, 2, vus);
		SWIZZLE_3(1, 0, 3, vut);
		SWIZZLE_3(1, 1, 0, vvu);
		SWIZZLE_3(1, 1, 1, vvv);
		SWIZZLE_3(1, 1, 2, vvs);
		SWIZZLE_3(1, 1, 3, vvt);
		SWIZZLE_3(1, 2, 0, vsu);
		SWIZZLE_3(1, 2, 1, vsv);
		SWIZZLE_3(1, 2, 2, vss);
		SWIZZLE_3(1, 2, 3, vst);
		SWIZZLE_3(1, 3, 0, vtu);
		SWIZZLE_3(1, 3, 1, vtv);
		SWIZZLE_3(1, 3, 2, vts);
		SWIZZLE_3(1, 3, 3, vtt);
		SWIZZLE_3(2, 0, 0, suu);
		SWIZZLE_3(2, 0, 1, suv);
		SWIZZLE_3(2, 0, 2, sus);
		SWIZZLE_3(2, 0, 3, sut);
		SWIZZLE_3(2, 1, 0, svu);
		SWIZZLE_3(2, 1, 1, svv);
		SWIZZLE_3(2, 1, 2, svs);
		SWIZZLE_3(2, 1, 3, svt);
		SWIZZLE_3(2, 2, 0, ssu);
		SWIZZLE_3(2, 2, 1, ssv);
		SWIZZLE_3(2, 2, 2, sss);
		SWIZZLE_3(2, 2, 3, sst);
		SWIZZLE_3(2, 3, 0, stu);
		SWIZZLE_3(2, 3, 1, stv);
		SWIZZLE_3(2, 3, 2, sts);
		SWIZZLE_3(2, 3, 3, stt);
		SWIZZLE_3(3, 0, 0, tuu);
		SWIZZLE_3(3, 0, 1, tuv);
		SWIZZLE_3(3, 0, 2, tus);
		SWIZZLE_3(3, 0, 3, tut);
		SWIZZLE_3(3, 1, 0, tvu);
		SWIZZLE_3(3, 1, 1, tvv);
		SWIZZLE_3(3, 1, 2, tvs);
		SWIZZLE_3(3, 1, 3, tvt);
		SWIZZLE_3(3, 2, 0, tsu);
		SWIZZLE_3(3, 2, 1, tsv);
		SWIZZLE_3(3, 2, 2, tss);
		SWIZZLE_3(3, 2, 3, tst);
		SWIZZLE_3(3, 3, 0, ttu);
		SWIZZLE_3(3, 3, 1, ttv);
		SWIZZLE_3(3, 3, 2, tts);
		SWIZZLE_3(3, 3, 3, ttt);

		// 4-Component VectorSwizzlers
		SWIZZLE_4(0, 0, 0, 0, uuuu);
		SWIZZLE_4(0, 0, 0, 1, uuuv);
		SWIZZLE_4(0, 0, 0, 2, uuus);
		SWIZZLE_4(0, 0, 0, 3, uuut);
		SWIZZLE_4(0, 0, 1, 0, uuvu);
		SWIZZLE_4(0, 0, 1, 1, uuvv);
		SWIZZLE_4(0, 0, 1, 2, uuvs);
		SWIZZLE_4(0, 0, 1, 3, uuvt);
		SWIZZLE_4(0, 0, 2, 0, uusu);
		SWIZZLE_4(0, 0, 2, 1, uusv);
		SWIZZLE_4(0, 0, 2, 2, uuss);
		SWIZZLE_4(0, 0, 2, 3, uust);
		SWIZZLE_4(0, 0, 3, 0, uutu);
		SWIZZLE_4(0, 0, 3, 1, uutv);
		SWIZZLE_4(0, 0, 3, 2, uuts);
		SWIZZLE_4(0, 0, 3, 3, uutt);
		SWIZZLE_4(0, 1, 0, 0, uvuu);
		SWIZZLE_4(0, 1, 0, 1, uvuv);
		SWIZZLE_4(0, 1, 0, 2, uvus);
		SWIZZLE_4(0, 1, 0, 3, uvut);
		SWIZZLE_4(0, 1, 1, 0, uvvu);
		SWIZZLE_4(0, 1, 1, 1, uvvv);
		SWIZZLE_4(0, 1, 1, 2, uvvs);
		SWIZZLE_4(0, 1, 1, 3, uvvt);
		SWIZZLE_4(0, 1, 2, 0, uvsu);
		SWIZZLE_4(0, 1, 2, 1, uvsv);
		SWIZZLE_4(0, 1, 2, 2, uvss);
		SWIZZLE_4(0, 1, 2, 3, uvst);
		SWIZZLE_4(0, 1, 3, 0, uvtu);
		SWIZZLE_4(0, 1, 3, 1, uvtv);
		SWIZZLE_4(0, 1, 3, 2, uvts);
		SWIZZLE_4(0, 1, 3, 3, uvtt);
		SWIZZLE_4(0, 2, 0, 0, usuu);
		SWIZZLE_4(0, 2, 0, 1, usuv);
		SWIZZLE_4(0, 2, 0, 2, usus);
		SWIZZLE_4(0, 2, 0, 3, usut);
		SWIZZLE_4(0, 2, 1, 0, usvu);
		SWIZZLE_4(0, 2, 1, 1, usvv);
		SWIZZLE_4(0, 2, 1, 2, usvs);
		SWIZZLE_4(0, 2, 1, 3, usvt);
		SWIZZLE_4(0, 2, 2, 0, ussu);
		SWIZZLE_4(0, 2, 2, 1, ussv);
		SWIZZLE_4(0, 2, 2, 2, usss);
		SWIZZLE_4(0, 2, 2, 3, usst);
		SWIZZLE_4(0, 2, 3, 0, ustu);
		SWIZZLE_4(0, 2, 3, 1, ustv);
		SWIZZLE_4(0, 2, 3, 2, usts);
		SWIZZLE_4(0, 2, 3, 3, ustt);
		SWIZZLE_4(0, 3, 0, 0, utuu);
		SWIZZLE_4(0, 3, 0, 1, utuv);
		SWIZZLE_4(0, 3, 0, 2, utus);
		SWIZZLE_4(0, 3, 0, 3, utut);
		SWIZZLE_4(0, 3, 1, 0, utvu);
		SWIZZLE_4(0, 3, 1, 1, utvv);
		SWIZZLE_4(0, 3, 1, 2, utvs);
		SWIZZLE_4(0, 3, 1, 3, utvt);
		SWIZZLE_4(0, 3, 2, 0, utsu);
		SWIZZLE_4(0, 3, 2, 1, utsv);
		SWIZZLE_4(0, 3, 2, 2, utss);
		SWIZZLE_4(0, 3, 2, 3, utst);
		SWIZZLE_4(0, 3, 3, 0, uttu);
		SWIZZLE_4(0, 3, 3, 1, uttv);
		SWIZZLE_4(0, 3, 3, 2, utts);
		SWIZZLE_4(0, 3, 3, 3, uttt);
		SWIZZLE_4(1, 0, 0, 0, vuuu);
		SWIZZLE_4(1, 0, 0, 1, vuuv);
		SWIZZLE_4(1, 0, 0, 2, vuus);
		SWIZZLE_4(1, 0, 0, 3, vuut);
		SWIZZLE_4(1, 0, 1, 0, vuvu);
		SWIZZLE_4(1, 0, 1, 1, vuvv);
		SWIZZLE_4(1, 0, 1, 2, vuvs);
		SWIZZLE_4(1, 0, 1, 3, vuvt);
		SWIZZLE_4(1, 0, 2, 0, vusu);
		SWIZZLE_4(1, 0, 2, 1, vusv);
		SWIZZLE_4(1, 0, 2, 2, vuss);
		SWIZZLE_4(1, 0, 2, 3, vust);
		SWIZZLE_4(1, 0, 3, 0, vutu);
		SWIZZLE_4(1, 0, 3, 1, vutv);
		SWIZZLE_4(1, 0, 3, 2, vuts);
		SWIZZLE_4(1, 0, 3, 3, vutt);
		SWIZZLE_4(1, 1, 0, 0, vvuu);
		SWIZZLE_4(1, 1, 0, 1, vvuv);
		SWIZZLE_4(1, 1, 0, 2, vvus);
		SWIZZLE_4(1, 1, 0, 3, vvut);
		SWIZZLE_4(1, 1, 1, 0, vvvu);
		SWIZZLE_4(1, 1, 1, 1, vvvv);
		SWIZZLE_4(1, 1, 1, 2, vvvs);
		SWIZZLE_4(1, 1, 1, 3, vvvt);
		SWIZZLE_4(1, 1, 2, 0, vvsu);
		SWIZZLE_4(1, 1, 2, 1, vvsv);
		SWIZZLE_4(1, 1, 2, 2, vvss);
		SWIZZLE_4(1, 1, 2, 3, vvst);
		SWIZZLE_4(1, 1, 3, 0, vvtu);
		SWIZZLE_4(1, 1, 3, 1, vvtv);
		SWIZZLE_4(1, 1, 3, 2, vvts);
		SWIZZLE_4(1, 1, 3, 3, vvtt);
		SWIZZLE_4(1, 2, 0, 0, vsuu);
		SWIZZLE_4(1, 2, 0, 1, vsuv);
		SWIZZLE_4(1, 2, 0, 2, vsus);
		SWIZZLE_4(1, 2, 0, 3, vsut);
		SWIZZLE_4(1, 2, 1, 0, vsvu);
		SWIZZLE_4(1, 2, 1, 1, vsvv);
		SWIZZLE_4(1, 2, 1, 2, vsvs);
		SWIZZLE_4(1, 2, 1, 3, vsvt);
		SWIZZLE_4(1, 2, 2, 0, vssu);
		SWIZZLE_4(1, 2, 2, 1, vssv);
		SWIZZLE_4(1, 2, 2, 2, vsss);
		SWIZZLE_4(1, 2, 2, 3, vsst);
		SWIZZLE_4(1, 2, 3, 0, vstu);
		SWIZZLE_4(1, 2, 3, 1, vstv);
		SWIZZLE_4(1, 2, 3, 2, vsts);
		SWIZZLE_4(1, 2, 3, 3, vstt);
		SWIZZLE_4(1, 3, 0, 0, vtuu);
		SWIZZLE_4(1, 3, 0, 1, vtuv);
		SWIZZLE_4(1, 3, 0, 2, vtus);
		SWIZZLE_4(1, 3, 0, 3, vtut);
		SWIZZLE_4(1, 3, 1, 0, vtvu);
		SWIZZLE_4(1, 3, 1, 1, vtvv);
		SWIZZLE_4(1, 3, 1, 2, vtvs);
		SWIZZLE_4(1, 3, 1, 3, vtvt);
		SWIZZLE_4(1, 3, 2, 0, vtsu);
		SWIZZLE_4(1, 3, 2, 1, vtsv);
		SWIZZLE_4(1, 3, 2, 2, vtss);
		SWIZZLE_4(1, 3, 2, 3, vtst);
		SWIZZLE_4(1, 3, 3, 0, vttu);
		SWIZZLE_4(1, 3, 3, 1, vttv);
		SWIZZLE_4(1, 3, 3, 2, vtts);
		SWIZZLE_4(1, 3, 3, 3, vttt);
		SWIZZLE_4(2, 0, 0, 0, suuu);
		SWIZZLE_4(2, 0, 0, 1, suuv);
		SWIZZLE_4(2, 0, 0, 2, suus);
		SWIZZLE_4(2, 0, 0, 3, suut);
		SWIZZLE_4(2, 0, 1, 0, suvu);
		SWIZZLE_4(2, 0, 1, 1, suvv);
		SWIZZLE_4(2, 0, 1, 2, suvs);
		SWIZZLE_4(2, 0, 1, 3, suvt);
		SWIZZLE_4(2, 0, 2, 0, susu);
		SWIZZLE_4(2, 0, 2, 1, susv);
		SWIZZLE_4(2, 0, 2, 2, suss);
		SWIZZLE_4(2, 0, 2, 3, sust);
		SWIZZLE_4(2, 0, 3, 0, sutu);
		SWIZZLE_4(2, 0, 3, 1, sutv);
		SWIZZLE_4(2, 0, 3, 2, suts);
		SWIZZLE_4(2, 0, 3, 3, sutt);
		SWIZZLE_4(2, 1, 0, 0, svuu);
		SWIZZLE_4(2, 1, 0, 1, svuv);
		SWIZZLE_4(2, 1, 0, 2, svus);
		SWIZZLE_4(2, 1, 0, 3, svut);
		SWIZZLE_4(2, 1, 1, 0, svvu);
		SWIZZLE_4(2, 1, 1, 1, svvv);
		SWIZZLE_4(2, 1, 1, 2, svvs);
		SWIZZLE_4(2, 1, 1, 3, svvt);
		SWIZZLE_4(2, 1, 2, 0, svsu);
		SWIZZLE_4(2, 1, 2, 1, svsv);
		SWIZZLE_4(2, 1, 2, 2, svss);
		SWIZZLE_4(2, 1, 2, 3, svst);
		SWIZZLE_4(2, 1, 3, 0, svtu);
		SWIZZLE_4(2, 1, 3, 1, svtv);
		SWIZZLE_4(2, 1, 3, 2, svts);
		SWIZZLE_4(2, 1, 3, 3, svtt);
		SWIZZLE_4(2, 2, 0, 0, ssuu);
		SWIZZLE_4(2, 2, 0, 1, ssuv);
		SWIZZLE_4(2, 2, 0, 2, ssus);
		SWIZZLE_4(2, 2, 0, 3, ssut);
		SWIZZLE_4(2, 2, 1, 0, ssvu);
		SWIZZLE_4(2, 2, 1, 1, ssvv);
		SWIZZLE_4(2, 2, 1, 2, ssvs);
		SWIZZLE_4(2, 2, 1, 3, ssvt);
		SWIZZLE_4(2, 2, 2, 0, sssu);
		SWIZZLE_4(2, 2, 2, 1, sssv);
		SWIZZLE_4(2, 2, 2, 2, ssss);
		SWIZZLE_4(2, 2, 2, 3, ssst);
		SWIZZLE_4(2, 2, 3, 0, sstu);
		SWIZZLE_4(2, 2, 3, 1, sstv);
		SWIZZLE_4(2, 2, 3, 2, ssts);
		SWIZZLE_4(2, 2, 3, 3, sstt);
		SWIZZLE_4(2, 3, 0, 0, stuu);
		SWIZZLE_4(2, 3, 0, 1, stuv);
		SWIZZLE_4(2, 3, 0, 2, stus);
		SWIZZLE_4(2, 3, 0, 3, stut);
		SWIZZLE_4(2, 3, 1, 0, stvu);
		SWIZZLE_4(2, 3, 1, 1, stvv);
		SWIZZLE_4(2, 3, 1, 2, stvs);
		SWIZZLE_4(2, 3, 1, 3, stvt);
		SWIZZLE_4(2, 3, 2, 0, stsu);
		SWIZZLE_4(2, 3, 2, 1, stsv);
		SWIZZLE_4(2, 3, 2, 2, stss);
		SWIZZLE_4(2, 3, 2, 3, stst);
		SWIZZLE_4(2, 3, 3, 0, sttu);
		SWIZZLE_4(2, 3, 3, 1, sttv);
		SWIZZLE_4(2, 3, 3, 2, stts);
		SWIZZLE_4(2, 3, 3, 3, sttt);
		SWIZZLE_4(3, 0, 0, 0, tuuu);
		SWIZZLE_4(3, 0, 0, 1, tuuv);
		SWIZZLE_4(3, 0, 0, 2, tuus);
		SWIZZLE_4(3, 0, 0, 3, tuut);
		SWIZZLE_4(3, 0, 1, 0, tuvu);
		SWIZZLE_4(3, 0, 1, 1, tuvv);
		SWIZZLE_4(3, 0, 1, 2, tuvs);
		SWIZZLE_4(3, 0, 1, 3, tuvt);
		SWIZZLE_4(3, 0, 2, 0, tusu);
		SWIZZLE_4(3, 0, 2, 1, tusv);
		SWIZZLE_4(3, 0, 2, 2, tuss);
		SWIZZLE_4(3, 0, 2, 3, tust);
		SWIZZLE_4(3, 0, 3, 0, tutu);
		SWIZZLE_4(3, 0, 3, 1, tutv);
		SWIZZLE_4(3, 0, 3, 2, tuts);
		SWIZZLE_4(3, 0, 3, 3, tutt);
		SWIZZLE_4(3, 1, 0, 0, tvuu);
		SWIZZLE_4(3, 1, 0, 1, tvuv);
		SWIZZLE_4(3, 1, 0, 2, tvus);
		SWIZZLE_4(3, 1, 0, 3, tvut);
		SWIZZLE_4(3, 1, 1, 0, tvvu);
		SWIZZLE_4(3, 1, 1, 1, tvvv);
		SWIZZLE_4(3, 1, 1, 2, tvvs);
		SWIZZLE_4(3, 1, 1, 3, tvvt);
		SWIZZLE_4(3, 1, 2, 0, tvsu);
		SWIZZLE_4(3, 1, 2, 1, tvsv);
		SWIZZLE_4(3, 1, 2, 2, tvss);
		SWIZZLE_4(3, 1, 2, 3, tvst);
		SWIZZLE_4(3, 1, 3, 0, tvtu);
		SWIZZLE_4(3, 1, 3, 1, tvtv);
		SWIZZLE_4(3, 1, 3, 2, tvts);
		SWIZZLE_4(3, 1, 3, 3, tvtt);
		SWIZZLE_4(3, 2, 0, 0, tsuu);
		SWIZZLE_4(3, 2, 0, 1, tsuv);
		SWIZZLE_4(3, 2, 0, 2, tsus);
		SWIZZLE_4(3, 2, 0, 3, tsut);
		SWIZZLE_4(3, 2, 1, 0, tsvu);
		SWIZZLE_4(3, 2, 1, 1, tsvv);
		SWIZZLE_4(3, 2, 1, 2, tsvs);
		SWIZZLE_4(3, 2, 1, 3, tsvt);
		SWIZZLE_4(3, 2, 2, 0, tssu);
		SWIZZLE_4(3, 2, 2, 1, tssv);
		SWIZZLE_4(3, 2, 2, 2, tsss);
		SWIZZLE_4(3, 2, 2, 3, tsst);
		SWIZZLE_4(3, 2, 3, 0, tstu);
		SWIZZLE_4(3, 2, 3, 1, tstv);
		SWIZZLE_4(3, 2, 3, 2, tsts);
		SWIZZLE_4(3, 2, 3, 3, tstt);
		SWIZZLE_4(3, 3, 0, 0, ttuu);
		SWIZZLE_4(3, 3, 0, 1, ttuv);
		SWIZZLE_4(3, 3, 0, 2, ttus);
		SWIZZLE_4(3, 3, 0, 3, ttut);
		SWIZZLE_4(3, 3, 1, 0, ttvu);
		SWIZZLE_4(3, 3, 1, 1, ttvv);
		SWIZZLE_4(3, 3, 1, 2, ttvs);
		SWIZZLE_4(3, 3, 1, 3, ttvt);
		SWIZZLE_4(3, 3, 2, 0, ttsu);
		SWIZZLE_4(3, 3, 2, 1, ttsv);
		SWIZZLE_4(3, 3, 2, 2, ttss);
		SWIZZLE_4(3, 3, 2, 3, ttst);
		SWIZZLE_4(3, 3, 3, 0, tttu);
		SWIZZLE_4(3, 3, 3, 1, tttv);
		SWIZZLE_4(3, 3, 3, 2, ttts);
		SWIZZLE_4(3, 3, 3, 3, tttt);

		#endif
	};
};

//////////////////////////////////////////////////////////////////////////////

#undef SWIZZLE_1
#undef SWIZZLE_2
#undef SWIZZLE_3
#undef SWIZZLE_4
