#include <cmath>

#include <gtest/gtest.h>

#define EPIC_SWIZZLE_XYZW
#include <Math/Vector.h>

class VectorTests : public testing::Test
{
};

TEST_F(VectorTests, CopyConstructor_CopiesValues)
{
	Epic::Vector4f test{ 1.f, 2.f, 3.f, 4.f };
	Epic::Vector4f expected{ test };

	EXPECT_FLOAT_EQ(expected[0], 1.f);
	EXPECT_FLOAT_EQ(expected[1], 2.f);
	EXPECT_FLOAT_EQ(expected[2], 3.f);
	EXPECT_FLOAT_EQ(expected[3], 4.f);
}

TEST_F(VectorTests, MoveConstructor_CopiesValues)
{
	Epic::Vector4f test{ 1.f, 2.f, 3.f, 4.f };
	Epic::Vector4f expected{ std::move(test) };

	EXPECT_FLOAT_EQ(expected[0], 1.f);
	EXPECT_FLOAT_EQ(expected[1], 2.f);
	EXPECT_FLOAT_EQ(expected[2], 3.f);
	EXPECT_FLOAT_EQ(expected[3], 4.f);
}

TEST_F(VectorTests, Constructor_WithZeroesTag_InitializesVector)
{
	Epic::Vector<float, 1> expected1{ Epic::Zero };
	Epic::Vector<float, 2> expected2{ Epic::Zero };
	Epic::Vector<float, 3> expected3{ Epic::Zero };
	Epic::Vector<float, 4> expected4{ Epic::Zero };
	Epic::Vector<float, 5> expected5{ Epic::Zero };

	for(size_t i=0; i<expected1.Size; ++i)
		EXPECT_FLOAT_EQ(expected1[i], 0.f);

	for (size_t i = 0; i < expected2.Size; ++i)
		EXPECT_FLOAT_EQ(expected2[i], 0.f);

	for (size_t i = 0; i < expected3.Size; ++i)
		EXPECT_FLOAT_EQ(expected3[i], 0.f);
	
	for (size_t i = 0; i < expected4.Size; ++i)
		EXPECT_FLOAT_EQ(expected4[i], 0.f);

	for (size_t i = 0; i < expected5.Size; ++i)
		EXPECT_FLOAT_EQ(expected5[i], 0.f);
}

TEST_F(VectorTests, Constructor_WithOnesTag_InitializesVector)
{
	Epic::Vector<float, 1> expected1{ Epic::One };
	Epic::Vector<float, 2> expected2{ Epic::One };
	Epic::Vector<float, 3> expected3{ Epic::One };
	Epic::Vector<float, 4> expected4{ Epic::One };
	Epic::Vector<float, 5> expected5{ Epic::One };

	for (size_t i = 0; i < expected1.Size; ++i)
		EXPECT_FLOAT_EQ(expected1[i], 1.f);

	for (size_t i = 0; i < expected2.Size; ++i)
		EXPECT_FLOAT_EQ(expected2[i], 1.f);

	for (size_t i = 0; i < expected3.Size; ++i)
		EXPECT_FLOAT_EQ(expected3[i], 1.f);

	for (size_t i = 0; i < expected4.Size; ++i)
		EXPECT_FLOAT_EQ(expected4[i], 1.f);

	for (size_t i = 0; i < expected5.Size; ++i)
		EXPECT_FLOAT_EQ(expected5[i], 1.f);
}

TEST_F(VectorTests, Constructor_WithIdentityTag_InitializesVector)
{
	Epic::Vector<float, 1> expected1{ Epic::Identity };
	Epic::Vector<float, 2> expected2{ Epic::Identity };
	Epic::Vector<float, 3> expected3{ Epic::Identity };
	Epic::Vector<float, 4> expected4{ Epic::Identity };
	Epic::Vector<float, 5> expected5{ Epic::Identity };

	for (size_t i = 0; i < expected1.Size; ++i)
		EXPECT_FLOAT_EQ(expected1[i], i == expected1.Size - 1 ? 1.f : 0.f);

	for (size_t i = 0; i < expected2.Size; ++i)
		EXPECT_FLOAT_EQ(expected2[i], i == expected2.Size - 1 ? 1.f : 0.f);

	for (size_t i = 0; i < expected3.Size; ++i)
		EXPECT_FLOAT_EQ(expected3[i], i == expected3.Size - 1 ? 1.f : 0.f);

	for (size_t i = 0; i < expected4.Size; ++i)
		EXPECT_FLOAT_EQ(expected4[i], i == expected4.Size - 1 ? 1.f : 0.f);

	for (size_t i = 0; i < expected5.Size; ++i)
		EXPECT_FLOAT_EQ(expected5[i], i == expected5.Size - 1 ? 1.f : 0.f);
}

TEST_F(VectorTests, VariadicConstructor_DeducesSize)
{
	Epic::Vector expected1{ 1.f };
	Epic::Vector expected2{ 1.f, 2.f };
	Epic::Vector expected3{ 1.f, 2.f, 3.f };
	Epic::Vector expected4{ 1.f, 2.f, 3.f, expected2 };
	Epic::Vector expected5{ 1.f, 2.f, 3.f, expected4 };

	EXPECT_FLOAT_EQ(expected1.Size, 1);
	EXPECT_FLOAT_EQ(expected2.Size, 2);
	EXPECT_FLOAT_EQ(expected3.Size, 3);
	EXPECT_FLOAT_EQ(expected4.Size, 5);
	EXPECT_FLOAT_EQ(expected5.Size, 8);
}

TEST_F(VectorTests, VariadicConstructor_WithElementArguments_InitializesVector)
{
	Epic::Vector expected{ 3.f, 2.f, 1.f };

	EXPECT_FLOAT_EQ(expected.Size, 3);
	EXPECT_FLOAT_EQ(expected[0], 3.f);
	EXPECT_FLOAT_EQ(expected[1], 2.f);
	EXPECT_FLOAT_EQ(expected[2], 1.f);
}

TEST_F(VectorTests, VariadicConstructor_WithVectorArguments_InitializesVector)
{
	Epic::Vector1f test1{ 10.f };
	Epic::Vector2f test2{ 20.f, 30.f };

	Epic::Vector expected{ test2, test1 };

	EXPECT_FLOAT_EQ(expected.Size, 3);
	EXPECT_FLOAT_EQ(expected[0], 20.f);
	EXPECT_FLOAT_EQ(expected[1], 30.f);
	EXPECT_FLOAT_EQ(expected[2], 10.f);
}

TEST_F(VectorTests, VariadicConstructor_WithVectorSwizzlerArguments_InitializesVector)
{
	Epic::Vector1f test1{ 10.f };
	Epic::Vector2f test2{ 20.f, 30.f };

	Epic::Vector expected{ test2.y, test1.xx };

	EXPECT_FLOAT_EQ(expected.Size, 3);
	EXPECT_FLOAT_EQ(expected[0], 30.f);
	EXPECT_FLOAT_EQ(expected[1], 10.f);
	EXPECT_FLOAT_EQ(expected[2], 10.f);
}

TEST_F(VectorTests, VariadicConstructor_WithArrayArguments_InitializesVector)
{
	float test1[] = { 10.f };
	float test2[] = { 20.f, 30.f };

	Epic::Vector expected{ test2, test1 };

	EXPECT_FLOAT_EQ(expected.Size, 3);
	EXPECT_FLOAT_EQ(expected[0], 20.f);
	EXPECT_FLOAT_EQ(expected[1], 30.f);
	EXPECT_FLOAT_EQ(expected[2], 10.f);
}

TEST_F(VectorTests, VariadicConstructor_WithStdArrayArguments_InitializesVector)
{
	std::array<float, 2> test1 = { 10.f, 30.f };
	std::array<float, 1> test2 = { 20.f };

	Epic::Vector expected{ test2, test1 };

	EXPECT_FLOAT_EQ(expected.Size, 3);
	EXPECT_FLOAT_EQ(expected[0], 20.f);
	EXPECT_FLOAT_EQ(expected[1], 10.f);
	EXPECT_FLOAT_EQ(expected[2], 30.f);
}

TEST_F(VectorTests, VariadicConstructor_WithMixedArguments_InitializesVector)
{
	float test1{ 10.f };
	Epic::Vector test2{ 20.f, 30.f };
	Epic::Vector test3{ 40.f, 50.f };
	float test4[] = { 60.f, 70.f };
	std::array<float, 2> test5 = { 80.f, 90.f };

	Epic::Vector expected{ test5, test4, test3, test2, test1 };

	EXPECT_FLOAT_EQ(expected.Size, 9);
	EXPECT_FLOAT_EQ(expected[0], 80.f);
	EXPECT_FLOAT_EQ(expected[1], 90.f);
	EXPECT_FLOAT_EQ(expected[2], 60.f);
	EXPECT_FLOAT_EQ(expected[3], 70.f);
	EXPECT_FLOAT_EQ(expected[4], 40.f);
	EXPECT_FLOAT_EQ(expected[5], 50.f);
	EXPECT_FLOAT_EQ(expected[6], 20.f);
	EXPECT_FLOAT_EQ(expected[7], 30.f);
	EXPECT_FLOAT_EQ(expected[8], 10.f);
}

TEST_F(VectorTests, ConstAt_RetrievesValue)
{
	const Epic::Vector test{ 11, 22, 33 };

	auto expected = test.at(1);

	EXPECT_EQ(expected, 22);
}

TEST_F(VectorTests, At_RetrievesWritableValue)
{
	Epic::Vector expected{ 11, 2, 33 };

	expected.at(1) = 22;

	EXPECT_EQ(expected[1], 22);
}

TEST_F(VectorTests, ConstIndexOperator_RetrievesValue)
{
	const Epic::Vector test{ 11, 22, 33 };

	auto expected = test[1];

	EXPECT_EQ(expected, 22);
}

TEST_F(VectorTests, IndexOperator_RetrievesWritableValue)
{
	Epic::Vector expected{ 11, 2, 33 };

	expected[1] = 22;

	EXPECT_EQ(expected.at(1), 22);
}

TEST_F(VectorTests, Dot_ReturnsDotProduct)
{
	Epic::Vector v1 = { 3.0f };
	Epic::Vector v2 = { 2.0f, 4.0f };
	Epic::Vector v3 = { v2, 5.0f };
	Epic::Vector v4 = { v3, -6.0f };
	Epic::Vector v5 = { v4, 7.0f };

	EXPECT_FLOAT_EQ(v1.Dot({ 2.0f }), 6.0f);
	EXPECT_FLOAT_EQ(v2.Dot({ 2.5f, 1.5f }), 11.0f);
	EXPECT_FLOAT_EQ(v3.Dot({ 2.5f, 0.0f, 1.5f }), 12.5f);
	EXPECT_FLOAT_EQ(v4.Dot({ 2.5f, 1.5f, 1.5f, -3.0f }), 36.5f);
	EXPECT_FLOAT_EQ(v5.Dot({ 2.5f, 1.5f, 1.5f, -3.0f, -1.5f }), 26.0f);
}

TEST_F(VectorTests, MagnitudeSq_ReturnsSquaredMagnitude)
{
	Epic::Vector v1 = { 3.0f };
	Epic::Vector v2 = { 2.0f, 4.0f };
	Epic::Vector v3 = { v2, 5.0f };
	Epic::Vector v4 = { v3, -6.0f };
	Epic::Vector v5 = { v4, 7.0f };

	float v5m1 = v5.Magnitude();
	float v5m2 = std::sqrt(v5.Dot(v5));

	EXPECT_FLOAT_EQ(v1.MagnitudeSq(), 9.0f);
	EXPECT_FLOAT_EQ(v2.MagnitudeSq(), 20.0f);
	EXPECT_FLOAT_EQ(v3.MagnitudeSq(), 45.0f);
	EXPECT_FLOAT_EQ(v4.MagnitudeSq(), 81.0f);
	EXPECT_FLOAT_EQ(v5.MagnitudeSq(), 130.0f);

	EXPECT_FLOAT_EQ(v5.MagnitudeSq(), v5m1 * v5m1);
	EXPECT_FLOAT_EQ(v5.MagnitudeSq(), v5m2 * v5m2);
}

TEST_F(VectorTests, ProjectionMagnitude_ComputesMagnitudeOfProjection)
{
	const Epic::Vector3d testsA[] = 
	{
		{ 0.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 2.0, 0.0, 0.0 },
		{ 2.0, 0.0, 0.0 }
	};

	const Epic::Vector3d testsB[] = 
	{ 
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 1.0, 1.0 },
		{ -2.0, 0.0, 0.0 }
	};

	const double expected[] = { 0.0, 0.5, 1.0, 2.0 / 3.0, -1.0 };

	const double results[] =
	{
		testsA[0].ProjectionMagnitude(testsB[0]),
		testsA[1].ProjectionMagnitude(testsB[1]),
		testsA[2].ProjectionMagnitude(testsB[2]),
		testsA[3].ProjectionMagnitude(testsB[3]),
		testsA[4].ProjectionMagnitude(testsB[4])
	};

	EXPECT_DOUBLE_EQ(expected[0], results[0]);
	EXPECT_DOUBLE_EQ(expected[1], results[1]);
	EXPECT_DOUBLE_EQ(expected[2], results[2]);
	EXPECT_DOUBLE_EQ(expected[3], results[3]);
	EXPECT_DOUBLE_EQ(expected[4], results[4]);
}

TEST_F(VectorTests, Magnitude_ReturnsMagnitude)
{
	Epic::Vector v1 = { 3.0f };
	Epic::Vector v2 = { 2.0f, 4.0f };
	Epic::Vector v3 = { v2, 5.0f };
	Epic::Vector v4 = { v3, -6.0f };
	Epic::Vector v5 = { v4, 7.0f };

	float v5m1 = v5.MagnitudeSq();
	float v5m2 = v5.Dot(v5);

	EXPECT_NEAR(v1.Magnitude(), 3.0f, 0.001f);
	EXPECT_NEAR(v2.Magnitude(), 4.4721f, 0.001f);
	EXPECT_NEAR(v3.Magnitude(), 6.7082f, 0.001f);
	EXPECT_NEAR(v4.Magnitude(), 9.0f, 0.001f);
	EXPECT_NEAR(v5.Magnitude(), 11.4018f, 0.001f);
		   
	EXPECT_NEAR(v5.Magnitude(), std::sqrt(v5m1), 0.001f);
	EXPECT_NEAR(v5.Magnitude(), std::sqrt(v5m2), 0.001f);
}

TEST_F(VectorTests, Reset_WithElementArguments_ResetsVector)
{
	Epic::Vector<float, 3> expected;
	
	expected.Reset(3.f, 2.f, 1.f);

	EXPECT_FLOAT_EQ(expected[0], 3.f);
	EXPECT_FLOAT_EQ(expected[1], 2.f);
	EXPECT_FLOAT_EQ(expected[2], 1.f);
}

TEST_F(VectorTests, Reset_WithVectorArguments_ResetsVector)
{
	Epic::Vector1f test1{ 10.f };
	Epic::Vector2f test2{ 20.f, 30.f };
	Epic::Vector<float, 3> expected;

	 expected.Reset(test2, test1);

	EXPECT_FLOAT_EQ(expected[0], 20.f);
	EXPECT_FLOAT_EQ(expected[1], 30.f);
	EXPECT_FLOAT_EQ(expected[2], 10.f);
}

TEST_F(VectorTests, Reset_WithVectorSwizzlerArguments_ResetsVector)
{
	Epic::Vector1f test1{ 10.f };
	Epic::Vector2f test2{ 20.f, 30.f };
	Epic::Vector<float, 3> expected;

	expected.Reset(test2.y, test1.xx);

	EXPECT_FLOAT_EQ(expected[0], 30.f);
	EXPECT_FLOAT_EQ(expected[1], 10.f);
	EXPECT_FLOAT_EQ(expected[2], 10.f);
}

TEST_F(VectorTests, Reset_WithArrayArguments_ResetsVector)
{
	float test1[] = { 10.f };
	float test2[] = { 20.f, 30.f };
	Epic::Vector<float, 3> expected;

	expected.Reset(test2, test1);

	EXPECT_FLOAT_EQ(expected[0], 20.f);
	EXPECT_FLOAT_EQ(expected[1], 30.f);
	EXPECT_FLOAT_EQ(expected[2], 10.f);
}

TEST_F(VectorTests, Reset_WithStdArrayArguments_ResetsVector)
{
	std::array<float, 2> test1 = { 10.f, 30.f };
	std::array<float, 1> test2 = { 20.f };
	Epic::Vector<float, 3> expected;

	expected.Reset(test2, test1);

	EXPECT_FLOAT_EQ(expected[0], 20.f);
	EXPECT_FLOAT_EQ(expected[1], 10.f);
	EXPECT_FLOAT_EQ(expected[2], 30.f);
}

TEST_F(VectorTests, Reset_WithMixedArguments_ResetsVector)
{
	float test1{ 10.f };
	Epic::Vector test2{ 20.f, 30.f };
	Epic::Vector test3{ 40.f, 50.f };
	float test4[] = { 60.f, 70.f };
	std::array<float, 2> test5 = { 80.f, 90.f };
	Epic::Vector<float, 9> expected;

	expected.Reset(test5, test4, test3, test2, test1);

	EXPECT_FLOAT_EQ(expected[0], 80.f);
	EXPECT_FLOAT_EQ(expected[1], 90.f);
	EXPECT_FLOAT_EQ(expected[2], 60.f);
	EXPECT_FLOAT_EQ(expected[3], 70.f);
	EXPECT_FLOAT_EQ(expected[4], 40.f);
	EXPECT_FLOAT_EQ(expected[5], 50.f);
	EXPECT_FLOAT_EQ(expected[6], 20.f);
	EXPECT_FLOAT_EQ(expected[7], 30.f);
	EXPECT_FLOAT_EQ(expected[8], 10.f);
}

TEST_F(VectorTests, Fill_WithElementArgument_FillsVectorWithElement)
{
	Epic::Vector<long, 6> expected;

	expected.Fill(4);

	for(size_t i=0; i<expected.Size; ++i)
		EXPECT_EQ(expected[i], 4);
}

TEST_F(VectorTests, Clamp_WithPositiveArguments_ClampsValues)
{
	Epic::Vector4f expected{ -1.0f, 0.5f, 1.0f, 2.0f };

	expected.Clamp(0.0f, 1.0f);

	EXPECT_FLOAT_EQ(expected[0], 0.0f);
	EXPECT_FLOAT_EQ(expected[1], 0.5f);
	EXPECT_FLOAT_EQ(expected[2], 1.0f);
	EXPECT_FLOAT_EQ(expected[3], 1.0f);
}

TEST_F(VectorTests, Clamp_WithNegativeArguments_ClampsValues)
{
	Epic::Vector4f expected{ 1.0f, -0.5f, -1.0f, -2.0f };

	expected.Clamp(-1.0f, 0.0f);

	EXPECT_FLOAT_EQ(expected[0], 0.0f);
	EXPECT_FLOAT_EQ(expected[1], -0.5f);
	EXPECT_FLOAT_EQ(expected[2], -1.0f);
	EXPECT_FLOAT_EQ(expected[3], -1.0f);
}

TEST_F(VectorTests, Clamp_WithNegativeAndPositiveArguments_ClampsValues)
{
	Epic::Vector4f expected{ -2.0f, 0.5f, 1.0f, 2.0f };

	expected.Clamp(-1.0f, 1.0f);

	EXPECT_FLOAT_EQ(expected[0], -1.0f);
	EXPECT_FLOAT_EQ(expected[1], 0.5f);
	EXPECT_FLOAT_EQ(expected[2], 1.0f);
	EXPECT_FLOAT_EQ(expected[3], 1.0f);
}

TEST_F(VectorTests, Normalize_NormalizesVector)
{
	Epic::Vector4d tests[] =
	{
		{ 0.0, 3.0, 4.0, 0.0 },
		{ -1.0, 2.0, 3.0, -4.0},
		{ 10.0, 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d expected[] =
	{
		{ 0.0, 0.6, 0.8, 0.0 },
		{ -0.18257, 0.36515, 0.54772, -0.73030 },
		{ 1.0, 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	for (auto i = 0; i < 4; ++i)
		tests[i].Normalize();

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[0][i], tests[0][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_NEAR(expected[1][i], tests[1][i], 0.001);

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[2][i], tests[2][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_TRUE(std::isnan(tests[3][i]));
}

TEST_F(VectorTests, NormalizeSafe_NormalizesVectorSafely)
{
	Epic::Vector4d tests[] =
	{
		{ 0.0, 3.0, 4.0, 0.0 },
		{ -1.0, 2.0, 3.0, -4.0},
		{ 10.0, 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d expected[] =
	{
		{ 0.0, 0.6, 0.8, 0.0 },
		{ -0.18257, 0.36515, 0.54772, -0.73030 },
		{ 1.0, 0.0, 0.0, 0.0},
		{ tests[3] }
	};

	for (auto i = 0; i < 4; ++i)
		tests[i].NormalizeSafe();

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[0][i], tests[0][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_NEAR(expected[1][i], tests[1][i], 0.001);

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[2][i], tests[2][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[3][i], tests[3][i]);
}

TEST_F(VectorTests, Power_WithElementArgument_RaisesElementsToThatPower)
{
	Epic::Vector test{ 0, 1, -2, 5, 10 };
	Epic::Vector expected{ 0, 1, -8, 125, 1000 };

	auto result = test.Power(3);

	EXPECT_EQ(result[0], expected[0]);
	EXPECT_EQ(result[1], expected[1]);
	EXPECT_EQ(result[2], expected[2]);
	EXPECT_EQ(result[3], expected[3]);
	EXPECT_EQ(result[4], expected[4]);
}

TEST_F(VectorTests, Power_WithVectorArgument_RaisesElementsToEachVectorElementsPower)
{
	Epic::Vector test{ 0.0, 2.0, 4.0, 5.0, -16.0 };
	Epic::Vector powers{ 3.0, -2.0, 0.5f, 0.0, 0.5 };
	Epic::Vector expected{ 0.0, 0.25, 2.0, 1.0, 0.0 };

	auto result = test.Power(powers);

	EXPECT_DOUBLE_EQ(result[0], expected[0]);
	EXPECT_DOUBLE_EQ(result[1], expected[1]);
	EXPECT_DOUBLE_EQ(result[2], expected[2]);
	EXPECT_DOUBLE_EQ(result[3], expected[3]);
	EXPECT_TRUE(std::isnan(result[4]));
}

TEST_F(VectorTests, Cross_WithVector1Argument_FailsAssertion)
{
	Epic::Vector testA = { 1.0 };
	Epic::Vector testB = { 0.0 };

	ASSERT_DEATH({
		testA.Cross(testB);
	}, "Cannot compute the cross product of Vectors of size 1.");
}

TEST_F(VectorTests, Cross_WithVector2Argument_Computes2dCrossProduct)
{
	Epic::Vector testA = { 0.0, 1.0 };
	Epic::Vector testB = { 1.0, 0.0 };

	EXPECT_DOUBLE_EQ(testA.Cross(testB), -1.0);
}

TEST_F(VectorTests, Cross_WithVector3Argument_Computes3dCrossProduct)
{
	Epic::Vector testA = { 0.0, 1.0, 0.0 };
	Epic::Vector testB = { 1.0, 0.0, 0.0 };

	const Epic::Vector expected = { 0.0, 0.0, -1.0 };

	const Epic::Vector result = testA.Cross(testB);

	EXPECT_DOUBLE_EQ(expected[0], result[0]);
	EXPECT_DOUBLE_EQ(expected[1], result[1]);
	EXPECT_DOUBLE_EQ(expected[2], result[2]);
}

TEST_F(VectorTests, Project_ComputesProjection)
{
	const Epic::Vector3d testsA[] =
	{
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 1.0, 1.0 },
		{ -2.0, 0.0, 0.0 }
	};

	const Epic::Vector3d testsB[] =
	{
		Epic::Vector3d::NormalOf({ 0.0, 1.0, 0.0 }),
		Epic::Vector3d::NormalOf({ 1.0, 0.0, 0.0 }),
		Epic::Vector3d::NormalOf({ 1.0, 0.0, 0.0 }),
		Epic::Vector3d::NormalOf({ 2.0, 0.0, 0.0 }),
		Epic::Vector3d::NormalOf({ 2.0, 0.0, 0.0 })
	};

	const Epic::Vector3d expected[] = 
	{
		{ 0.0, 0.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ -2.0, 0.0, 0.0 }
	};

	const Epic::Vector3d results[] =
	{
		testsA[0].Project(testsB[0]),
		testsA[1].Project(testsB[1]),
		testsA[2].Project(testsB[2]),
		testsA[3].Project(testsB[3]),
		testsA[4].Project(testsB[4])
	};

	for (auto r = 0; r < sizeof(results) / sizeof(results[0]); ++r)
		for (auto i = 0; i < 3; ++i)
			EXPECT_DOUBLE_EQ(expected[r][i], results[r][i]);
}

TEST_F(VectorTests, ProjectN_ComputesProjectionOnNormalizedAxis)
{
	const Epic::Vector3d testsA[] =
	{
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 1.0, 1.0 },
		{ -2.0, 0.0, 0.0 }
	};

	const Epic::Vector3d testsB[] =
	{
		{ 0.0, 10.0, 0.0 },
		{ 10.0, 0.0, 0.0 },
		{ 10.0, 0.0, 0.0 },
		{ 2.0, 0.0, 0.0 },
		{ 2.0, 1.0, 3.0 }
	};

	const Epic::Vector3d expected[] =
	{
		{ 0.0, 0.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ -0.57143, -0.28571, -0.85714 }
	};

	const Epic::Vector3d results[] =
	{
		testsA[0].Project(testsB[0]),
		testsA[1].Project(testsB[1]),
		testsA[2].Project(testsB[2]),
		testsA[3].Project(testsB[3]),
		testsA[4].Project(testsB[4])
	};

	for (auto r = 0; r < sizeof(results) / sizeof(results[0]); ++r)
		for (auto i = 0; i < 3; ++i)
			EXPECT_NEAR(expected[r][i], results[r][i], 0.001);
}

TEST_F(VectorTests, Reflect_ComputesReflection)
{
	const Epic::Vector3d tests[] =
	{
		{ 1.0, 2.0, 0.0 },
		{ 1.0, 1.0, 1.0 },
		{ 0.0, 0.0, 2.0 },
		{ 0.8, 1.0, 0.0 }
	};

	const Epic::Vector3d normal = { 0.0, 1.0, 0.0 };

	const Epic::Vector3d expected[] =
	{
		{ -1.0, 2.0, 0.0 },
		{ -1.0, 1.0, -1.0 },
		{ 0.0, 0.0, -2.0 },
		{ -0.8, 1.0, 0.0 }
	};

	const Epic::Vector3d results[] =
	{
		tests[0].Reflect(normal),
		tests[1].Reflect(normal),
		tests[2].Reflect(normal),
		tests[3].Reflect(normal)
	};

	for (auto r = 0; r < sizeof(results) / sizeof(results[0]); ++r)
		for (auto i = 0; i < 3; ++i)
			EXPECT_DOUBLE_EQ(expected[r][i], results[r][i]);
}

TEST_F(VectorTests, Refract_ComputesRefraction)
{
	const Epic::Vector3d tests[] =
	{
		{ 1.0, 2.0, 0.0 },
		{ 1.0, 1.0, 1.0 },
		{ 0.0, 0.0, 1.0 },
		{ 0.8, 1.0, 0.0 }
	};

	const Epic::Vector3d normal = { 0.0, -1.0, 0.0 };

	const Epic::Vector3d expected[] =
	{
		{ 1.1, 1.94679, 0.0 },
		{ 1.1, 0.76158, 1.1 },
		{ 0.0, 0.0, 0.0 },
		{ 0.88, 0.93038, 0.0 }
	};

	const Epic::Vector3d results[] =
	{
		tests[0].Refract(normal, 1.1) * tests[0].Magnitude(),
		tests[1].Refract(normal, 1.1) * tests[1].Magnitude(),
		tests[2].Refract(normal, 1.1) * tests[2].Magnitude(),
		tests[3].Refract(normal, 1.1) * tests[3].Magnitude()
	};

	for (auto r = 0; r < sizeof(results) / sizeof(results[0]); ++r)
		for (auto i = 0; i < 3; ++i)
			EXPECT_NEAR(expected[r][i], results[r][i], 0.001);
}

TEST_F(VectorTests, MixOf_ReturnsInterpolatedVector)
{
	Epic::Vector testA{ 0.0, 0.0, 1.0, -5.0, -1.0, -1.0, 0.0, 1.0 };
	Epic::Vector testB{ 1.0, -1.0, 0.0, 0.0, -2.0, 1.0, 0.0, 1.0 };

	const Epic::Vector<double, 8> results[] = 
	{
		Epic::Vector<double, 8>::MixOf(testA, testB, 0.0),
		Epic::Vector<double, 8>::MixOf(testA, testB, 1.0),
		Epic::Vector<double, 8>::MixOf(testA, testB, 0.25),
		Epic::Vector<double, 8>::MixOf(testA, testB, -1.0),
		Epic::Vector<double, 8>::MixOf(testA, testB, 0.5),
		Epic::Vector<double, 8>::MixOf(testA, testB, -0.5)
	};

	const Epic::Vector<double, 8> expected[] = 
	{
		{testA},
		{testB},
		{0.25, -0.25, 0.75, -3.75, -1.25, -0.5, 0.0, 1.0},
		{-1.0, 1.0, 2.0, -10.0, 0.0, -3.0, 0.0, 1.0},
		{0.5, -0.5, 0.5, -2.5, -1.5, 0.0, 0.0, 1.0},
		{-0.5, 0.5, 1.5, -7.5, -0.5, -2.0, 0.0, 1.0},
	};

	for (auto r = 0; r < sizeof(results) / sizeof(results[0]); ++r)
		for (auto i = 0; i < 8; ++i)
			EXPECT_DOUBLE_EQ(expected[r][i], results[r][i]);
}

TEST_F(VectorTests, NormalOf_ReturnsNormalizedVector)
{
	Epic::Vector4d tests[] =
	{
		{ 0.0, 3.0, 4.0, 0.0 },
		{ -1.0, 2.0, 3.0, -4.0},
		{ 10.0, 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d expected[] =
	{
		{ 0.0, 0.6, 0.8, 0.0 },
		{ -0.18257, 0.36515, 0.54772, -0.73030 },
		{ 1.0, 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d results[] =
	{
		Epic::Vector4d::NormalOf(tests[0]),
		Epic::Vector4d::NormalOf(tests[1]),
		Epic::Vector4d::NormalOf(tests[2]),
		Epic::Vector4d::NormalOf(tests[3])
	};

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[0][i], results[0][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_NEAR(expected[1][i], results[1][i], 0.001);

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[2][i], results[2][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_TRUE(std::isnan(results[3][i]));
}

TEST_F(VectorTests, SafeNormalOf_ReturnsSafelyNormalizedVector)
{
	Epic::Vector4d tests[] =
	{
		{ 0.0, 3.0, 4.0, 0.0 },
		{ -1.0, 2.0, 3.0, -4.0},
		{ 10.0, 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d expected[] =
	{
		{ 0.0, 0.6, 0.8, 0.0 },
		{ -0.18257, 0.36515, 0.54772, -0.73030 },
		{ 1.0, 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d results[] =
	{
		Epic::Vector4d::SafeNormalOf(tests[0]),
		Epic::Vector4d::SafeNormalOf(tests[1]),
		Epic::Vector4d::SafeNormalOf(tests[2]),
		Epic::Vector4d::SafeNormalOf(tests[3])
	};

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[0][i], results[0][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_NEAR(expected[1][i], results[1][i], 0.001);

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[2][i], results[2][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[3][i], results[3][i]);
}

TEST_F(VectorTests, OrthoNormalOf_ReturnsOrthonormalizedVector)
{
	Epic::Vector4d testAs[] =
	{
		{ 0.0, 1.0, 0.0, 0.0 },
		{ -1.0, 2.0, 3.0, -4.0},
		{ -1.0, 2.0, 3.0, -4.0},
		{ 1.0, 0.0, 0.0, 0.0 }
	};

	Epic::Vector4d testBs[] =
	{
		{ 0.0, 0.0, 0.0, 1.0 },
		{ 1.0, -2.0, -3.0, 4.0},
		{ 2.0, 1.0, -1.0, -2.0},
		{ 1.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d expected[] =
	{
		{ 0.0, 1.0, 0.0, 0.0 },
		{ 0.18257, -0.36515, -0.54772, 0.73030 },
		{ -0.72532, -0.19781, 0.52750, 0.39563},
		{ 0.0, 0.0, 0.0, 0.0 }
	};

	const Epic::Vector4d results[] =
	{
		Epic::Vector4d::OrthoNormalOf(testAs[0], testBs[0]),
		Epic::Vector4d::OrthoNormalOf(testAs[1], testBs[1]),
		Epic::Vector4d::OrthoNormalOf(testAs[2], testBs[2]),
		Epic::Vector4d::OrthoNormalOf(testAs[3], testBs[3])
	};

	for (auto i = 0; i < 4; ++i)
		EXPECT_DOUBLE_EQ(expected[0][i], results[0][i]);

	for (auto i = 0; i < 4; ++i)
		EXPECT_NEAR(expected[1][i], results[1][i], 0.001);

	for (auto i = 0; i < 4; ++i)
		EXPECT_NEAR(expected[2][i], results[2][i], 0.001);

	for (auto i = 0; i < 4; ++i)
		EXPECT_TRUE(std::isnan(results[3][i]));
}

TEST_F(VectorTests, OperatorT_InvokedImplicitly_ReturnsElementValue)
{
	Epic::Vector test{ 3.25f };
	float expected = test;

	EXPECT_FLOAT_EQ(expected, test[0]);
}

TEST_F(VectorTests, Distance_ReturnsDistanceBetweenArguments)
{
	Epic::Vector test1A{ 0.0, 0.0, 0.0, 0.0};
	Epic::Vector test1B{ 4.0, -4.0, 4.0, 4.0};

	Epic::Vector test2A{ -12.0, 0.0, -2.0, -60.0 };
	Epic::Vector test2B{ 4.0, -4.0, 2.0, 4.0 };

	const double results[] =
	{
		Epic::Distance(test1A, test1B),
		Epic::Distance(test2A, test2B),
	};

	const double expected[] =
	{
		8.0,
		66.2118
	};

	for (auto r = 0; r < sizeof(results) / sizeof(results[0]); ++r)
		EXPECT_NEAR(expected[r], results[r], 0.001);
}

TEST_F(VectorTests, Mean_ReturnsAveragedElements)
{
	Epic::Vector4d tests[] = 
	{
		{ 1.0, 1.0, 1.0, 1.0 },
		{ -2.0, -3.0, -1.0, -2.0},
		{ -3.0, 4.0, -2.0, 6.0 },
		{ -1.0, -2.0, 1.0, 2.0 }
	};

	const double expected[] = 
	{
		1.0,
		-2.0,
		1.25,
		0.0
	};

	const double results[] = 
	{
		Epic::Mean(tests[0]),
		Epic::Mean(tests[1]),
		Epic::Mean(tests[2]),
		Epic::Mean(tests[3])
	};

	EXPECT_DOUBLE_EQ(expected[0], results[0]);
	EXPECT_DOUBLE_EQ(expected[1], results[1]);
	EXPECT_DOUBLE_EQ(expected[2], results[2]);
	EXPECT_DOUBLE_EQ(expected[3], results[3]);
}

TEST_F(VectorTests, WeightedMean_ReturnsWeightedAveragedElements)
{
	Epic::Vector<double, 5> tests[] =
	{
		{ 1.0, 1.0, 1.0, 1.0, 1.0 },
		{ -2.0, -3.0, -1.0, -2.0, 10.0},
		{ -3.0, 4.0, -2.0, 6.0, 4.0 },
		{ -1.0, -2.0, 1.0, 2.0, 0.0 }
	};
	
	const double weights[] = { 0.5, 1.5, 1.0, -0.5, 0.0 };

	const double expected[] = { 1.0, -2.2, -0.2, -1.4, 0.0 };

	const double results[] =
	{
		Epic::WeightedMean(tests[0], weights),
		Epic::WeightedMean(tests[1], weights),
		Epic::WeightedMean(tests[2], weights),
		Epic::WeightedMean(tests[3], weights)
	};

	EXPECT_DOUBLE_EQ(expected[0], results[0]);
	EXPECT_DOUBLE_EQ(expected[1], results[1]);
	EXPECT_DOUBLE_EQ(expected[2], results[2]);
	EXPECT_DOUBLE_EQ(expected[3], results[3]);
}

TEST_F(VectorTests, Negative_ReturnsVectorWithImageNegativeElements)
{
	Epic::Vector4d tests[] = 
	{
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 0.0, 0.0, 0.0, 0.0 },
		{ -3.0, 4.0, -2.0, 6.0 },
		{ 0.5, 0.25, 0.75, 1.0 }
	};

	const Epic::Vector4d expected[] = 
	{
		{0.0, 0.0, 0.0, 0.0},
		{1.0, 1.0, 1.0, 1.0},
		{4.0, -3.0, 3.0, -5.0},
		{0.5, 0.75, 0.25, 0.0},
	};

	const Epic::Vector4d results[] = 
	{
		Epic::Negative(tests[0], 1.0),
		Epic::Negative(tests[1], 1.0),
		Epic::Negative(tests[2], 1.0),
		Epic::Negative(tests[3], 1.0)
	};

	for (auto r = 0; r < sizeof(results) / sizeof(results[0]); ++r)
		for (auto i = 0; i < 4; ++i)
			EXPECT_DOUBLE_EQ(expected[r][i], results[r][i]);
}

TEST_F(VectorTests, AngleOf_ReturnsAngleBetweenArguments)
{
	Epic::Vector2f testAs[] =
	{
		{ 0.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f }
	};

	Epic::Vector2f testBs[] =
	{
		{ 1.0f, 0.0f },
		{ 0.7071f, 0.7071f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f }
	};

	const float expected[] = { 90.0f, 45.0f, 0.0f, 90.0f };

	const float results[] =
	{
		Epic::Degreef{ Epic::AngleOf(testAs[0], testBs[0]) }.Value(),
		Epic::Degreef{ Epic::AngleOf(testAs[1], testBs[1]) }.Value(),
		Epic::Degreef{ Epic::AngleOf(testAs[2], testBs[2]) }.Value(),
		Epic::Degreef{ Epic::AngleOf(testAs[3], testBs[3]) }.Value()
	};

	EXPECT_NEAR(expected[0], results[0], 0.001f);
	EXPECT_NEAR(expected[1], results[1], 0.001f);
	EXPECT_NEAR(expected[2], results[2], 0.001f);
	EXPECT_NEAR(expected[3], results[3], 0.001f);
}
