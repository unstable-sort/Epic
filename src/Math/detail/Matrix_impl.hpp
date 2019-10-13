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

#include "Matrix_decl.h"

#include <cassert>

#include "Quaternion_decl.h"
#include "MatrixBase.hpp"
#include "MetaHelpers.hpp"
#include "../Angle.h"
#include "../Tags.h"
#include "../Vector.h"

//////////////////////////////////////////////////////////////////////////////

// Matrix
template<class T, size_t N>
class Epic::Matrix : public Epic::detail::MatrixBase<T, N>
{
public:
	using type = Epic::Matrix<T, N>;
	using base_type = Epic::detail::MatrixBase<T, N>;
	using column_type = base_type::column_type;
	using value_type = base_type::value_type;

public:
	using base_type::Columns;
	using base_type::Values;
	
	static constexpr size_t ColumnCount = base_type::ColumnCount;
	static constexpr size_t ElementCount = base_type::ElementCount;

private:
	template<class, size_t>
	friend class Epic::Matrix;

public:
	Matrix() noexcept = default;
	Matrix(const Matrix&) noexcept = default;
	Matrix(Matrix&&) noexcept = default;
	~Matrix() noexcept = default;

	Matrix(const ZeroesTag&) noexcept
	{ 
		for (size_t n = 0; n < ElementCount; ++n)
			at(n) = T(0);
	}

	Matrix(const OnesTag&) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			at(n) = T(1);
	}

	Matrix(const IdentityTag&) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] = T(0);

		for (size_t n = 0; n < ColumnCount; ++n)
			Values[column_type::Size * n + n] = T(1);
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	explicit Matrix(Quaternion<T> q) noexcept
	{
		MakeRotation(std::move(q));
	}

	template<typename EnabledFor3x3 = std::enable_if_t<(N == 3)>>
	Matrix(Vector<T, 2> translation, Radian<T> rotation, Vector<T, 2> scale) noexcept
	{
		MakeTRS(std::move(translation), std::move(rotation), std::move(scale));
	}

	template<typename EnabledFor4x4 = std::enable_if_t<(N == 4)>>
	Matrix(Vector<T, 3> translation, Quaternion<T> rotation, Vector<T, 3> scale) noexcept
	{
		MakeTRS(std::move(translation), std::move(rotation), std::move(scale));
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	Matrix(Radian<T> pitch, Radian<T> heading, Radian<T> roll) noexcept
	{
		MakeRotation(std::move(pitch), std::move(heading), std::move(roll));
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	Matrix(const XRotationTag&, Radian<T> phi) noexcept
	{
		MakeXRotation(std::move(phi));
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	Matrix(const YRotationTag&, Radian<T> theta) noexcept
	{
		MakeYRotation(std::move(theta));
	}

	Matrix(const ZRotationTag&, Radian<T> psi) noexcept
	{
		MakeZRotation(std::move(psi));
	}

	Matrix(const RotationTag&, Radian<T> psi) noexcept
	{
		MakeRotation(std::move(psi));
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	Matrix(const RotationTag&, Vector<T, 3> axis, Radian<T> angle) noexcept
	{
		MakeRotation(std::move(axis), std::move(angle));
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	Matrix(const RotationTag&, Quaternion<T> q) noexcept
		: type(q)
	{ }

	template<typename EnabledFor4x4 = std::enable_if_t<(N == 4)>>
	Matrix(const LookAtTag&, 
		Vector<T, 3> target,
		Vector<T, 3> eye = { T(0), T(0), T(0) },
		Vector<T, 3> up  = { T(0), T(1), T(0) }) noexcept
	{
		LookAt(std::move(target), std::move(eye), std::move(up));
	}

	template<typename EnabledFor4x4 = std::enable_if_t<(N == 4)>>
	Matrix(const LookAtTag&,
		Vector<T, 4> target,
		Vector<T, 4> eye = { T(0), T(0), T(0), T(1) },
		Vector<T, 4> up = { T(0), T(1), T(0), T(0) }) noexcept
	{
		LookAt(std::move(target), std::move(eye), std::move(up));
	}

	template<class... Us, typename = std::enable_if_t<
		(detail::Span<Us...>::value <= column_type::Size)>>
	Matrix(const TranslationTag&, Us&&... values) noexcept
	{
		MakeTranslation(std::forward<Us>(values)...);
	}

	template<class... Us, typename = std::enable_if_t<
		(detail::Span<Us...>::value <= column_type::Size)>>
	Matrix(const ScaleTag&, const Us&&... values) noexcept
	{
		MakeScale(std::forward<Us>(values)...);
	}

	template<class... Us, typename = std::enable_if_t<
		!Meta::IsVariadicTypeOf<type, Us...> &&
		!detail::HasTag_v<Us...> &&
		detail::Span_v<Us...> == ElementCount>>
	Matrix(Us&&... values) noexcept
	{
		detail::SpanConstructor<T>::Construct(std::begin(Values), std::forward<Us>(values)...);
	}
	
public:
	constexpr const column_type& at(size_t index) const
	{
		return Columns[index];
	}

	constexpr column_type& at(size_t index)
	{
		return Columns[index];
	}

	constexpr const column_type& operator[] (size_t index) const
	{
		return Columns[index];
	}

	constexpr column_type& operator[] (size_t index)
	{
		return Columns[index];
	}

public:
	void Transform(Vector<T, N>& vec) const noexcept
	{
		const auto src = vec;

		for (size_t i = 0; i < ColumnCount; ++i)
		{
			vec[i] = src[0] * Values[i];

			for (size_t j = 1; j < ColumnCount; ++j)
				vec[i] += src[j] * Values[(column_type::Size * j) + i];
		}
	}

	void Transform(Vector<T, N - 1>& vec) const noexcept
	{
		const auto src = vec;

		for (size_t i = 0; i < ColumnCount - 1; ++i)
		{
			vec[i] = src[0] * Values[i];

			for (size_t j = 1; j < (ColumnCount - 1); ++j)
				vec[i] += src[j] * Values[(column_type::Size * j) + i];

			vec[i] += Values[(column_type::Size * (ColumnCount - 1)) + i];
		}
	}

	void TransformRM(Vector<T, N>& vec) const noexcept
	{
		auto src = vec;

		for (size_t i = 0; i < column_type::Size; ++i)
		{
			vec[i] = src[0] * Values[ColumnCount * i];

			for (size_t j = 1; j < column_type::Size; ++j)
				vec[i] += src[j] * Values[(ColumnCount * i) + j];
		}
	}

	void TransformRM(Vector<T, N - 1>& vec) const noexcept
	{
		const auto src = vec;

		for (size_t i = 0; i < column_type::Size; ++i)
		{
			vec[i] = src[0] * Values[ColumnCount * i];

			for (size_t j = 1; j < (column_type::Size - 1); ++j)
				vec[i] += src[j] * Values[(ColumnCount * i) + j];

			vec[i] += Values[(ColumnCount * i) + column_type::Size - 1];
		}
	}

public:
	template<class... Us, typename = std::enable_if_t<detail::Span_v<Us...> == ElementCount>>
	constexpr type& Reset(Us&&... values) noexcept
	{
		detail::SpanConstructor<T>::Construct(std::begin(Values), std::forward<Us>(values)...);

		return *this;
	}

	constexpr type& Fill(T value) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			at(n) = value;

		return *this;
	}

	constexpr type& MakeIdentity() noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			at(n) = T(0);

		for (size_t n = 0; n < ColumnCount; ++n)
			at(ColumnCount * n + n) = T(1);

		return *this;
	}

	template<typename EnabledFor3x3 = std::enable_if_t<(N == 3)>>
	type& MakeTRS(Vector<T, 2> translation, Radian<T> rotation, Vector<T, 2> scale) noexcept
	{
		MakeRotation(std::move(rotation));

		Columns[0] *= scale.x;
		Columns[1] *= scale.y;

		Columns[2] = std::move(translation);

		return *this;
	}

	template<typename EnabledFor4x4 = std::enable_if_t<(N == 4)>>
	type& MakeTRS(Vector<T, 2> translation, Quaternion<T> rotation, Vector<T, 3> scale) noexcept
	{
		MakeRotation(std::move(rotation));

		Columns[0] *= scale.x;
		Columns[1] *= scale.y;
		Columns[2] *= scale.z;

		Columns[3] = std::move(translation);

		return *this;
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	type& MakeXRotation(Radian<T> phi) noexcept
	{
		MakeIdentity();

		const auto[sinx, cosx] = phi.SinCos();

		Values[1 * column_type::Size + 1] = cosx;
		Values[1 * column_type::Size + 2] = sinx;
		Values[2 * column_type::Size + 1] = -sinx;
		Values[2 * column_type::Size + 2] = cosx;

		return *this;
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	type& MakeYRotation(Radian<T> theta) noexcept
	{
		MakeIdentity();

		const auto[sinx, cosx] = theta.SinCos();

		Values[0 * column_type::Size + 0] = cosx;
		Values[0 * column_type::Size + 2] = -sinx;
		Values[2 * column_type::Size + 0] = sinx;
		Values[2 * column_type::Size + 2] = cosx;

		return *this;
	}

	type& MakeZRotation(Radian<T> psi) noexcept
	{
		MakeIdentity();

		const auto[sinx, cosx] = psi.SinCos();

		Values[0 * column_type::Size + 0] = cosx;
		Values[0 * column_type::Size + 1] = sinx;
		Values[1 * column_type::Size + 0] = -sinx;
		Values[1 * column_type::Size + 1] = cosx;

		return *this;
	}

	type& MakeRotation(Radian<T> rotation) noexcept
	{
		return MakeZRotation(std::move(rotation));
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	type& MakeRotation(Radian<T> pitch, Radian<T> heading, Radian<T> roll) noexcept
	{
		return MakeRotation(Epic::Quaternion<T> { std::move(pitch), std::move(heading), std::move(roll) });
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	type& MakeRotation(Vector<T, 3> axis, Radian<T> angle) noexcept
	{
		MakeIdentity();

		const auto[sinx, cosx] = angle.SinCos();
		const T cos1x = T(1) - cosx;

		const T cxx = cos1x * axis.Values[0] * axis.Values[0];
		const T cyy = cos1x * axis.Values[1] * axis.Values[1];
		const T czz = cos1x * axis.Values[2] * axis.Values[2];
		const T cxy = cos1x * axis.Values[0] * axis.Values[1];
		const T cxz = cos1x * axis.Values[0] * axis.Values[2];
		const T cyz = cos1x * axis.Values[1] * axis.Values[2];

		const T sx = sinx * axis.Values[0];
		const T sy = sinx * axis.Values[1];
		const T sz = sinx * axis.Values[2];

		Values[0 * column_type::Size + 0] = cxx + cosx;
		Values[0 * column_type::Size + 1] = cxy + sz;
		Values[0 * column_type::Size + 2] = cxz - sy;

		Values[1 * column_type::Size + 0] = cxy - sz;
		Values[1 * column_type::Size + 1] = cyy + cosx;
		Values[1 * column_type::Size + 2] = cyz + sx;

		Values[2 * column_type::Size + 0] = cxz + sy;
		Values[2 * column_type::Size + 1] = cyz - sx;
		Values[2 * column_type::Size + 2] = czz + cosx;

		return *this;
	}

	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	type& MakeRotation(Quaternion<T> q) noexcept
	{
		MakeIdentity();

		const auto qx = static_cast<T>(q.x);
		const auto qy = static_cast<T>(q.y);
		const auto qz = static_cast<T>(q.z);
		const auto qw = static_cast<T>(q.w);

		const auto qxx = qx * qx;
		const auto qyy = qy * qy;
		const auto qzz = qz * qz;
		const auto qxz = qx * qz;
		const auto qxy = qx * qy;
		const auto qyz = qy * qz;
		const auto qwx = qw * qx;
		const auto qwy = qw * qy;
		const auto qwz = qw * qz;

		Values[0 * column_type::Size + 0] = T(1) - T(2) * (qyy + qzz);
		Values[0 * column_type::Size + 1] = T(2) * (qxy + qwz);
		Values[0 * column_type::Size + 2] = T(2) * (qxz - qwy);

		Values[1 * column_type::Size + 0] = T(2) * (qxy - qwz);
		Values[1 * column_type::Size + 1] = T(1) - T(2) * (qxx + qzz);
		Values[1 * column_type::Size + 2] = T(2) * (qyz + qwx);

		Values[2 * column_type::Size + 0] = T(2) * (qxz + qwy);
		Values[2 * column_type::Size + 1] = T(2) * (qyz - qwx);
		Values[2 * column_type::Size + 2] = T(1) - T(2) * (qxx + qyy);

		return *this;
	}

	template<typename EnabledFor4x4 = std::enable_if_t<(N == 4)>>
	type& LookAt(
		Vector<T, 3> target,
		Vector<T, 3> eye = { T(0), T(0), T(0) },
		Vector<T, 3> up = { T(0), T(1), T(0) }) noexcept
	{
		const auto zaxis = Vector<T, 3>::SafeNormalOf(target - eye);
		const auto xaxis = Vector<T, 3>::SafeNormalOf(zaxis.Cross(up));
		const auto yaxis = xaxis.Cross(zaxis);

		Values =
		{
			xaxis.x, yaxis.x, -zaxis.x, T(0),
			xaxis.y, yaxis.y, -zaxis.y, T(0),
			xaxis.z, yaxis.z, -zaxis.z, T(0),
			-xaxis.Dot(eye), -yaxis.Dot(eye), zaxis.Dot(eye), T(1)
		};

		return *this;
	}

	template<typename EnabledFor4x4 = std::enable_if_t<(N == 4)>>
	type& LookAt(
		Vector<T, 4> target,
		Vector<T, 4> eye = { T(0), T(0), T(0), T(0) },
		Vector<T, 4> up = { T(0), T(1), T(0), T(0) }) noexcept
	{
		const auto zaxis = Vector<T, 4>::SafeNormalOf(target - eye);
		const auto xaxis = Vector<T, 4>::SafeNormalOf(zaxis.Cross(up));
		const auto yaxis = xaxis.Cross(zaxis);

		Values =
		{
			xaxis.x, yaxis.x, -zaxis.x, T(0),
			xaxis.y, yaxis.y, -zaxis.y, T(0),
			xaxis.z, yaxis.z, -zaxis.z, T(0),
			-xaxis.Dot(eye), -yaxis.Dot(eye), zaxis.Dot(eye), T(1)
		};

		return *this;
	}

	template<class... Us, typename = std::enable_if_t<(detail::Span_v<Us...> <= column_type::Size)>>
	type& MakeTranslation(Us&&... values) noexcept
	{
		constexpr size_t SpanSize = detail::Span_v<Us...>;
		constexpr size_t ColumnIndex = ElementCount - column_type::Size;

		MakeIdentity();

		Vector<T, SpanSize> values{ std::forward<Us>(values)... };

		for (size_t n = 0; n < SpanSize; ++n)
			Values[ColumnIndex + n] = values[n];

		return *this;
	}

	template<class... Us, typename = std::enable_if_t<(detail::Span_v<Us...> <= column_type::Size)>>
	type& MakeScale(Us&&... values) noexcept
	{
		constexpr size_t SpanSize = detail::Span_v<Us...>;

		MakeIdentity();

		Vector<T, SpanSize> values{ std::forward<Us>(values)... };

		for (size_t n = 0; n < SpanSize; ++n)
			Values[ColumnCount * n + n] = values[n];

		return *this;
	}

public:
	template<typename EnabledFor3x3OrGreater = std::enable_if_t<(N >= 3)>>
	Quaternion<T> ToQuaternion() const noexcept
	{
		const auto trace = Trace();

		if (trace > T(0.000001))
		{
			const auto sqt = std::sqrt(trace) * T(2);

			return
			{
				(Columns[1][2] - Columns[2][1]) / sqt,
				(Columns[2][0] - Columns[0][2]) / sqt,
				(Columns[0][1] - Columns[1][0]) / sqt,
				sqt / T(4)
			};
		}
		else if (Columns[0][0] > Columns[1][1] && Columns[0][0] > Columns[2][2])
		{
			const auto sqt = std::sqrt(T(1) + Columns[0][0] - Columns[1][1] - Columns[2][2]) * T(2);

			return
			{
				sqt / T(4),
				(Columns[0][1] + Columns[1][0]) / sqt,
				(Columns[2][0] + Columns[0][2]) / sqt,
				(Columns[1][2] + Columns[2][1]) / sqt
			};
		}
		else if (Columns[1][1] > Columns[2][2])
		{
			const auto sqt = std::sqrt(T(1) + Columns[1][1] - Columns[0][0] - Columns[2][2]) * T(2);

			return
			{
				(Columns[0][1] + Columns[1][0]) / sqt,
				sqt / T(4),
				(Columns[1][2] + Columns[2][1]) / sqt,
				(Columns[2][0] + Columns[0][2]) / sqt
			};
		}
		else
		{
			const auto sqt = std::sqrt(T(1) + Columns[2][2] - Columns[0][0] - Columns[1][1]) * T(2);

			return
			{
				(Columns[2][0] + Columns[0][2]) / sqt,
				(Columns[1][2] + Columns[2][1]) / sqt,
				sqt / T(4),
				(Columns[0][1] + Columns[1][0]) / sqt
			};
		}
	}

public:
	constexpr T Trace() const noexcept
	{
		T result = T(0);

		for (size_t n = 0; n < ColumnCount; ++n)
			result += Values[(n * column_type::Size) + n];

		return result;
	}

	T Determinant() const noexcept
	{
		return CalculateDeterminant<ColumnCount>();
	}

	type& Compose(const type& mat) noexcept
	{
		type result = Zero;

		for (size_t i = 0; i < ColumnCount; ++i)
		{
			for (size_t j = 0; j < column_type::Size; ++j)
				result.Columns[i] += Columns[j] * mat[i][j];
		}

		return (*this = result);
	}

	type& Transpose() noexcept
	{
		for (size_t i = 0; i < ColumnCount; ++i)
		{
			for (size_t j = i + 1; j < ColumnCount; ++j)
			{
				std::swap
				(
					Values[(i * column_type::Size) + j],
					Values[(j * column_type::Size) + i]
				);
			}
		}

		return *this;
	}

	type& InvertRigid() noexcept
	{
		return TransposeInvertRigid().Transpose();
	}

	type& Invert() noexcept
	{
		const T det = Determinant();
		if (det == T(0))
			return *this;

		if constexpr (ColumnCount == 1)
		{
			if (Values[0] != T(0))
				Values[0] = T(1) / det;
		}

		else if constexpr (ColumnCount == 2)
		{
			const auto t = Values[0];

			Values[0] = Values[3];
			Values[1] = -Values[1];
			Values[2] = -Values[2];
			Values[3] = t;

			*this *= T(1) / det;
		}

		else if constexpr (ColumnCount == 3)
		{
			type adj;

			adj.Values[0] = (Values[4] * Values[8]) - (Values[5] * Values[7]);
			adj.Values[1] = -(Values[1] * Values[8]) + (Values[2] * Values[7]);
			adj.Values[2] = (Values[1] * Values[5]) - (Values[2] * Values[4]);
			adj.Values[3] = -(Values[3] * Values[8]) + (Values[5] * Values[6]);
			adj.Values[4] = (Values[0] * Values[8]) - (Values[2] * Values[6]);
			adj.Values[5] = -(Values[0] * Values[5]) + (Values[2] * Values[3]);
			adj.Values[6] = (Values[3] * Values[7]) - (Values[4] * Values[6]);
			adj.Values[7] = -(Values[0] * Values[7]) + (Values[1] * Values[6]);
			adj.Values[8] = (Values[0] * Values[4]) - (Values[1] * Values[3]);

			*this = adj;
			*this *= T(1) / det;
		}

		else
		{
			type lower = Identity;
			type& upper = *this;

			for (size_t i = 0; i < ColumnCount; ++i)
			{
				T v = std::abs(upper.Values[(i * column_type::Size) + i]);
				size_t column = i;

				for (size_t j = i + 1; j < ColumnCount; ++j)
				{
					const T iv = std::abs(upper.Values[(j * column_type::Size) + i]);
					if (iv > v)
					{
						column = j;
						v = iv;
					}
				}

				if (column != i)
				{
					auto cv = upper[column];
					upper[column] = upper[i];
					upper[i] = cv;

					cv = lower[column];
					lower[column] = lower[i];
					lower[i] = cv;
				}

				const T tc = T(1) / upper.Values[(i * column_type::Size) + i];
				lower[i] *= tc;
				upper[i] *= tc;

				for (size_t j = i + 1; j < ColumnCount; ++j)
				{
					const T t = upper.Values[(j * column_type::Size) + i];
					upper[j] -= upper[i] * t;
					lower[j] -= lower[i] * t;

					upper.Values[(j * column_type::Size) + i] = T(0);
				}
			}

			for (size_t i = ColumnCount - 1; i > 0; --i)
			{
				for (long long j = i - 1; j >= 0; --j)
				{
					size_t js = static_cast<size_t>(j);

					const T t = upper.Values[(js * column_type::Size) + i];
					lower[js] -= lower[i] * t;
					upper[js] -= upper[i] * t;
				}
			}

			*this = lower;
		}

		return *this;
	}

	type& TransposeInvertRigid() noexcept
	{
		for (size_t i = 0; i < ColumnCount - 1; ++i)
			Columns[i][column_type::Size - 1] = -Columns[i].Dot(Columns[ColumnCount - 1]);

		Columns[ColumnCount - 1].Fill(T(0));
		Columns[ColumnCount - 1].Values[column_type::Size - 1] = T(1);

		return *this;
	}

	type& TransposeInvert() noexcept
	{
		Invert();

		return Transpose();
	}

	template<size_t I = 0, size_t N = ColumnCount>
	Matrix<T, N> Slice() const noexcept
	{
		static_assert(N > 1, "Resultant Matrix must be at least 2x2");
		static_assert((I + N) <= ColumnCount, "Slice parameters are out of bounds");

		Matrix<T, N> result;
		size_t src = (ColumnCount * I) + I;
		size_t dest = 0;

		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
				result.Values[dest++] = Values[src++];

			src += ColumnCount - N;
		}

		return result;
	}

	template<size_t Amount = 1>
	auto Contract() const noexcept
	{
		static_assert(Amount < ColumnCount, "Resultant Matrix must be at least 2x2");

		return Slice<0, ColumnCount - Amount>();
	}

	template<size_t Amount = 1>
	auto Expand() const noexcept
	{
		constexpr size_t ExpandedSz = ColumnCount + Amount;

		Matrix<T, ExpandedSz> result(*this);

		for (size_t c = 0; c < ColumnCount; ++c)
		{
			const auto o = c * ExpandedSz;
			for (size_t r = column_type::Size; r < ExpandedSz; ++r)
				result.Values[o + r] = T(0);
		}

		for (size_t c = ColumnCount; c < ExpandedSz; ++c)
		{
			const auto o2 = ExpandedSz * c;
			for (size_t r = 0; r < ExpandedSz; ++r)
				result.Values[o2 + r] = (c == r) ? T(1) : T(0);
		}

		return result;
	}

public:
	static type CompositeOf(const type& matA, const type& matB) noexcept
	{
		return type(matA).Compose(matB);
	}

	static type TransposeOf(const type& mat) noexcept
	{
		return type(mat).Transpose();
	}

	static type RigidInverseOf(const type& mat) noexcept
	{
		return type(mat).InvertRigid();
	}

	static type InverseOf(const type& mat) noexcept
	{
		return type(mat).Invert();
	}

	static type TransposedRigidInverseOf(const type& mat) noexcept
	{
		return type(mat).TransposeInvertRigid();
	}

	static type TransposedInverseOf(const type& mat) noexcept
	{
		return type(mat).TransposeInvert();
	}

public:
	type operator - () const noexcept
	{
		type result;

		for (size_t n = 0; n < ElementCount; ++n)
			result.Values[n] = -Values[n];

		return result;
	}

	type operator ~ () const noexcept
	{
		return type::RigidInverseOf(*this);
	}

public:
	#pragma region Assignment Operators

	type& operator = (const ZeroesTag&) noexcept
	{
		return Fill(T(0));
	}

	type& operator = (const OnesTag&) noexcept
	{
		return Fill(T(1));
	}

	type& operator = (const IdentityTag&) noexcept
	{
		return MakeIdentity();
	}

	type& operator *= (const type& m) noexcept
	{
		return Compose(m);
	}

	type& operator = (T value) noexcept
	{
		return Fill(std::move(value));
	}

	type& operator += (T value) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] += value;

		return *this;
	}

	type& operator -= (T value) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] -= value;

		return *this;
	}

	type& operator *= (T value) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] *= value;

		return *this;
	}

	type& operator /= (T value) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] /= value;

		return *this;
	}

	type& operator = (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] = values[n];

		return *this;
	}

	type& operator += (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] += values[n];

		return *this;
	}

	type& operator -= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] -= values[n];

		return *this;
	}

	type& operator *= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] *= values[n];

		return *this;
	}

	type& operator /= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] /= values[n];

		return *this;
	}

	type& operator = (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] = mat.Values[n];

		return *this;
	}

	type& operator = (type&& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] = mat.Values[n];

		return *this;
	}

	type& operator += (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] += mat.Values[n];

		return *this;
	}

	type& operator -= (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] -= mat.Values[n];

		return *this;
	}

	#pragma endregion

public:
	#pragma region Logic Assignment Operators

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator |= (T value) noexcept
	{
		for (size_t n = 0; n < ColumnCount; ++n)
			Columns[n] |= value;
		
		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator &= (T value) noexcept
	{
		for (size_t n = 0; n < ColumnCount; ++n)
			Columns[n] &= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator ^= (T value) noexcept
	{
		for (size_t n = 0; n < ColumnCount; ++n)
			Columns[n] ^= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator %= (T value) noexcept
	{
		for (size_t n = 0; n < ColumnCount; ++n)
			Columns[n] %= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator <<= (T value) noexcept
	{
		for (size_t n = 0; n < ColumnCount; ++n)
			Columns[n] <<= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator >>= (T value) noexcept
	{
		for (size_t n = 0; n < ColumnCount; ++n)
			Columns[n] >>= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator |= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] |= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator &= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] &= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator ^= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] ^= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator %= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] %= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator <<= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] <<= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator >>= (const T(&values)[ElementCount]) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] >>= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator |= (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] |= mat.Values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator &= (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] &= mat.Values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator ^= (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] ^= mat.Values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator %= (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] %= mat.Values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator <<= (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] <<= mat.Values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator >>= (const type& mat) noexcept
	{
		for (size_t n = 0; n < ElementCount; ++n)
			Values[n] >>= mat.Values[n];

		return *this;
	}

	#pragma endregion

public:
	#pragma region Arithmetic Operators

	type operator * (const type& mat) const noexcept
	{
		return type::CompositeOf(*this, mat);
	}

	type operator + (T value) const noexcept
	{
		return type(*this) += std::move(value);
	}

	type operator - (T value) const noexcept
	{
		return type(*this) -= std::move(value);
	}

	type operator * (T value) const noexcept
	{
		return type(*this) *= std::move(value);
	}

	type operator / (T value) const noexcept
	{
		return type(*this) /= std::move(value);
	}
	
	type operator + (const T(&values)[ElementCount]) const noexcept
	{
		return type(*this) += values;
	}

	type operator - (const T(&values)[ElementCount]) const noexcept
	{
		return type(*this) -= values;
	}

	type operator * (const T(&values)[ElementCount]) const noexcept
	{
		return type(*this) *= values;
	}

	type operator / (const T(&values)[ElementCount]) const noexcept
	{
		return type(*this) /= values;
	}

	type operator + (const type& mat) const noexcept
	{
		return type(*this) += mat;
	}

	type operator - (const type& mat) const noexcept
	{
		return type(*this) -= mat;
	}

	friend type operator + (T value, const type& mat) noexcept
	{
		return type(mat) += std::move(value);
	}

	friend type operator - (T value, const type& mat) noexcept
	{
		return type(mat) -= std::move(value);
	}

	friend type operator * (T value, const type& mat) noexcept
	{
		return type(mat) *= std::move(value);
	}

	friend type operator / (T value, const type& mat) noexcept
	{
		return type(mat) /= std::move(value);
	}
	
	#pragma endregion

private:
	template<size_t N>
	T CalculateDeterminant() const noexcept
	{
		if constexpr (N == 0)
			return 0;

		else if constexpr (N == 1)
			return Values[0];

		else if constexpr (N == 2)
			return (Values[0] * Values[3]) - (Values[1] * Values[2]);

		else if constexpr (N == 3)
		{
			return (Values[0] * Values[4] * Values[8])
				 + (Values[1] * Values[5] * Values[6])
				 + (Values[2] * Values[3] * Values[7])
				 - (Values[6] * Values[4] * Values[2])
				 - (Values[7] * Values[5] * Values[0])
				 - (Values[8] * Values[3] * Values[1]);
		}

		else
		{
			auto minors = CalculateMinors<N>();

			for (size_t i = 1; i < N; i += 2)
				minors.Values[i] = -minors.Values[i];

			return minors.Dot(Columns[0]);
		}
	}

	template<size_t N>
	auto CalculateMinors() const noexcept
	{
		Vector<T, N> minors;
		Matrix<T, N - 1> minor;

		for (size_t c = 0; c < N; ++c)
		{
			size_t d = 0;

			for (size_t i = 1; i < N; ++i)
			{
				for (size_t r = 0; r < N; ++r)
				{
					if (r != c)
						minor.Values[d++] = Values[(i * N) + r];
				}
			}

			minors[c] = minor.CalculateDeterminant<N - 1>();
		}

		return minors;
	}
};

//////////////////////////////////////////////////////////////////////////////

// Friend Operators
namespace Epic
{
	template<class T, size_t N>
	inline bool operator == (const Matrix<T, N>& matA, const Matrix<T, N>& matB) noexcept
	{
		for (size_t i = 0; i < N; ++i)
			if (matA[i] != matB[i]) return false;

		return true;
	}

	template<class T, size_t N>
	inline bool operator != (const Matrix<T, N>& matA, const Matrix<T, N>& matB) noexcept
	{
		return !(matA == matB);
	}

	template<class T, size_t N>
	inline std::ostream& operator << (std::ostream& stream, const Matrix<T, N>& mat)
	{
		stream << "[\n";
		stream << std::fixed;
			
		for (size_t n = 0; n < N; ++n)
		{
			stream << ' ' << mat[n];
			if (n < N - 1) stream << ',';
			stream << '\n';
		}
			
		stream << std::defaultfloat;
		stream << ']';

		return stream;
	}

	template<class T, size_t N>
	inline std::wostream& operator << (std::wostream& stream, const Matrix<T, N>& mat)
	{
		stream << L"[\n";
		stream << std::fixed;

		for (size_t n = 0; n < N; ++n)
		{
			stream << L' ' << mat[n];
			if (n < N - 1) stream << L',';
			stream << L'\n';
		}
			
		stream << std::defaultfloat;
		stream << L']';

		return stream;
	}

	template<class T, size_t N>
	inline std::istream& operator >> (std::istream& stream, Matrix<T, N>& mat)
	{
		if (stream.peek() == '[')
			stream.ignore(1);

		for (size_t n = 0; n < N; ++n)
		{
			if (n > 0 && stream.peek() == ',')
				stream.ignore(1);

			stream >> mat[n];
		}

		if (stream.peek() == ']')
			stream.ignore(1);

		return stream;
	}

	template<class T, size_t N>
	inline std::wistream& operator >> (std::wistream& stream, Matrix<T, N>& mat)
	{
		if (stream.peek() == L'[')
			stream.ignore(1);

		for (size_t n = 0; n < N; ++n)
		{
			if (n > 0 && stream.peek() == L',')
				stream.ignore(1);

			stream >> mat[n];
		}

		if (stream.peek() == L']')
			stream.ignore(1);

		return stream;
	}
}

//////////////////////////////////////////////////////////////////////////////

// Deduction Guides
namespace Epic
{
	template<class... Ts, typename = std::enable_if_t<
		!detail::HasTag_v<Ts...> &&
		detail::IsMatrixSquare_v<detail::Span_v<Ts...>>>>
	Matrix(Ts&&... values) -> Matrix<detail::SpanElement_t<Ts...>, (detail::CalculateMatrixSize(detail::Span_v<Ts...>))>;
}

//////////////////////////////////////////////////////////////////////////////

// Vector/Matrix operators
namespace Epic
{
	template<class T, size_t N>
	inline auto operator * (const Matrix<T, N>& m, Vector<T, N> v) noexcept
	{
		auto result = std::move(v);
		m.Transform(result);
		return result;
	}

	template<class T, size_t N>
	inline auto operator * (Vector<T, N> v, const Matrix<T, N>& m) noexcept
	{
		auto result = std::move(v);
		m.TransformRM(result);
		return result;
	}

	template<class T, size_t N>
	inline auto operator * (const Matrix<T, N + 1>& m, Vector<T, N> v) noexcept
	{
		auto result = std::move(v);
		m.Transform(result);
		return result;
	}

	template<class T, size_t N>
	inline auto operator * (Vector<T, N> v, const Matrix<T, N + 1>& m) noexcept
	{
		auto result = std::move(v);
		m.TransformRM(result);
		return result;
	}

	template<class T, size_t N>
	inline auto operator / (const Matrix<T, N>& m, Vector<T, N> v) noexcept
	{
		auto result = std::move(v);
		Matrix<T, N>::InverseOf(m).Transform(result);
		return result;
	}

	template<class T, size_t N>
	inline auto operator / (Vector<T, N> v, const Matrix<T, N>& m) noexcept
	{
		auto result = std::move(v);
		Matrix<T, N>::InverseOf(m).TransformRM(result);
		return result;
	}

	template<class T, size_t N>
	inline auto operator / (const Matrix<T, N + 1>& m, Vector<T, N> v) noexcept
	{
		auto result = std::move(v);
		Matrix<T, N + 1>::InverseOf(m).Transform(result);
		return result;
	}

	template<class T, size_t N>
	inline auto operator / (Vector<T, N> v, const Matrix<T, N + 1>& m) noexcept
	{
		auto result = std::move(v);
		Matrix<T, N + 1>::InverseOf(m).TransformRM(result);
		return result;
	}
}

//////////////////////////////////////////////////////////////////////////////

// Algorithms
namespace Epic
{
	namespace
	{
		template<class T, size_t N>
		Matrix<T, N> CreateShearMatrix(T shear, size_t column, size_t row) noexcept
		{
			Matrix<T, N> result = Identity;

			assert(column >= 0 && column < N);
			assert(row >= 0 && row < N);

			result.Values[(N * column) + row] = std::move(shear);

			return result;
		}

		template<class T>
		Matrix<T, 4> CreateFrustumMatrix(T left, T right, T top, T bottom, T znear, T zfar) noexcept
		{
			Matrix<T, 4> result;

			const auto h = top - bottom;
			const auto w = right - left;
			const auto d = zfar - znear;
			const auto n2 = T(2) * znear;
			const auto z = T(0);

			assert(h != T(0));
			assert(w != T(0));
			assert(d != T(0));

			result.Values =
			{
				n2 / w, T(0), T(0), T(0),
				T(0), n2 / h, T(0), T(0),
				(right + left) / w, (top + bottom) / h, -(zfar + znear) / d, T(-1),
				T(0), T(0), (-n2 * zfar) / d, T(0)
			};

			return result;
		}

		template<class T>
		Matrix<T, 4> CreatePerspectiveMatrix(Radian<T> fovy, T aspectRatio, T znear, T zfar) noexcept
		{
			Matrix<T, 4> result;

			const auto z = T(0);
			const auto f = T(1) / (fovy / T(2)).Tan();
			const auto d = znear - zfar;

			assert(d != T(0));
			assert(aspectRatio != T(0));

			result.Values =
			{
				f / std::move(aspectRatio), z, z, z,
				z, f, z, z,
				z, z, (zfar + znear) / d, T(-1),
				z, z, (T(2) * zfar * znear) / d, z
			};

			return result;
		}

		template<class T>
		Matrix<T, 4> CreatePerspectiveMatrix(Degree<T> fovy, T aspectRatio, T znear, T zfar) noexcept
		{
			return CreatePerspectiveMatrix((Radian<T>) fovy, aspectRatio, znear, zfar);
		}

		template<class T>
		Matrix<T, 4> CreateOrthoMatrix(T left, T right, T top, T bottom, T znear, T zfar) noexcept
		{
			Matrix<T, 4> result;

			const auto h = top - bottom;
			const auto w = right - left;
			const auto d = zfar - znear;
			const auto z = T(0);

			assert(h != T(0));
			assert(w != T(0));
			assert(d != T(0));

			result.Values =
			{
				T(2) / w, z, z, z,
				z, T(2) / h, z, z,
				z, z, T(-2) / d, z,
				-(right + left) / w, -(top + bottom) / h, -(zfar + znear) / d, T(1)
			};

			return result;
		}

		template<class T>
		Matrix<T, 4> CreateOrtho2DMatrix(T left, T right, T top, T bottom) noexcept
		{
			return CreateOrthoMatrix
			(
				std::move(left), 
				std::move(right), 
				std::move(top), 
				std::move(bottom), 
				T(-1), 
				T(1)
			);
		}

		template<class T>
		Matrix<T, 4> CreatePickingMatrix(T pickx, T picky, T pickw, T pickh, T vpX, T vpY, T vpW, T vpH) noexcept
		{
			Matrix<T, 4> result = Identity;

			assert(pickw > T(0));
			assert(pickh > T(0));

			result.Values =
			{
				vpW / pickw, T(0), T(0), T(0),
				T(0), vpH / pickh, T(0), T(0),
				T(0), T(0), T(1), T(0),
				(vpW + (T(2) * (vpX - pickx))) / pickw, (vpH + (T(2) * (vpY - picky))) / pickh, T(0), T(1)
			};

			return result;
		}

		template<class T>
		Matrix<T, 4> CreateShadowMatrix(Vector<T, 4> ground, Vector<T, 4> light) noexcept
		{
			Matrix<T, 4> result;

			const auto dot = ground.Dot(light);

			result.Values =
			{
				dot - light.x * ground.x, -light.x * ground.y, -light.x * ground.z, -light.x * ground.w,
				-light.y * ground.x, dot - light.y * ground.y, -light.y * ground.z, -light.y * ground.w,
				-light.z * ground.x, -light.z * ground.y, dot - light.z * ground.z, -light.z * ground.w,
				-light.w * ground.x, -light.w * ground.y, -light.w * ground.z, dot - light.w * ground.w
			};

			return result;
		}
	}
}
