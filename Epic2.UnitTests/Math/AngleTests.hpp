#include <gtest/gtest.h>

#include <Math/Angle.h>

using Epic::Degree;
using Epic::Radian;

class RadianTests : public testing::Test
{
};

TEST_F(RadianTests, Constructor_WithConvertibleRadian_HasConvertedValue)
{
	Radian<int> test = 10;
	Radian<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 10.0f);
}

TEST_F(RadianTests, Constructor_WithValue_HasValue) 
{
	float test = 10.0f;
	Radian<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 10.0f);
}

TEST_F(RadianTests, Constructor_WithConvertibleValue_HasConvertedValue)
{
	int test = 10;
	Radian<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 10.0f);
}

TEST_F(RadianTests, Constructor_WithDegree_HasValue)
{
	Degree<float> test = 180.0f;
	Radian<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 3.141593f);
}

TEST_F(RadianTests, Constructor_WithConvertibleDegree_HasConvertedValue)
{
	Degree<int> test = 180;
	Radian<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 3.141593f);
}

TEST_F(RadianTests, Sin_ReturnsSinOfValue)
{
	Radian<float> expected1{ Epic::DegreesToRadians(30.0f) };
	Radian<float> expected2{ Epic::DegreesToRadians(90.0f) };
	Radian<float> expected3{ Epic::DegreesToRadians(180.0f) };

	EXPECT_NEAR(expected1.Sin(), 0.5f, 0.01f);
	EXPECT_NEAR(expected2.Sin(), 1.0f, 0.01f);
	EXPECT_NEAR(expected3.Sin(), 0.0f, 0.01f);
}

TEST_F(RadianTests, Cos_ReturnsCosOfValue)
{
	Radian<float> expected1{ Epic::DegreesToRadians(60.0f) };
	Radian<float> expected2{ Epic::DegreesToRadians(90.0f) };
	Radian<float> expected3{ Epic::DegreesToRadians(180.0f) };

	EXPECT_NEAR(expected1.Cos(), 0.5f, 0.01f);
	EXPECT_NEAR(expected2.Cos(), 0.0f, 0.01f);
	EXPECT_NEAR(expected3.Cos(), -1.0f, 0.01f);
}

TEST_F(RadianTests, Tan_ReturnsTanOfValue)
{
	Radian<float> expected1{ Epic::DegreesToRadians(60.0f) };
	Radian<float> expected2{ Epic::DegreesToRadians(10.0f) };
	Radian<float> expected3{ Epic::DegreesToRadians(225.0f) };

	EXPECT_NEAR(expected1.Tan(), 1.732051f, 0.01f);
	EXPECT_NEAR(expected2.Tan(), 0.176327f, 0.01f);
	EXPECT_NEAR(expected3.Tan(), 1.0f, 0.01f);
}

TEST_F(RadianTests, SinCos_ReturnsSinAndCosOfValue)
{
	Radian<float> test1{ Epic::DegreesToRadians(30.0f) };
	Radian<float> test2{ Epic::DegreesToRadians(60.0f) };
	Radian<float> test3{ Epic::DegreesToRadians(90.0f) };

	auto[expected1Sin, expected1Cos] = test1.SinCos();
	auto[expected2Sin, expected2Cos] = test2.SinCos();
	auto[expected3Sin, expected3Cos] = test3.SinCos();

	EXPECT_NEAR(expected1Sin, 0.5f, 0.01f);
	EXPECT_NEAR(expected1Cos, 0.866025f, 0.01f);
	EXPECT_NEAR(expected2Sin, 0.866025f, 0.01f);
	EXPECT_NEAR(expected2Cos, 0.5f, 0.01f);
	EXPECT_NEAR(expected3Sin, 1.0f, 0.01f);
	EXPECT_NEAR(expected3Cos, 0.0f, 0.01f);
}

TEST_F(RadianTests, Normalize_NormalizesValue)
{
	Radian<float> expected1{ Epic::DegreesToRadians(180.0f) };
	Radian<float> expected2{ Epic::DegreesToRadians(720.0f) };
	Radian<float> expected3{ Epic::DegreesToRadians(2000.0f) };
	Radian<float> expected4{ Epic::DegreesToRadians(-180.f) };
	Radian<float> expected5{ Epic::DegreesToRadians(-2000.0f) };

	expected1.Normalize();
	expected2.Normalize();
	expected3.Normalize();
	expected4.Normalize();
	expected5.Normalize();

	EXPECT_NEAR(expected1.Value(), Epic::DegreesToRadians(180.0f), 0.01f);
	EXPECT_NEAR(expected2.Value(), Epic::DegreesToRadians(0.0f), 0.01f);
	EXPECT_NEAR(expected3.Value(), Epic::DegreesToRadians(200.0f), 0.01f);
	EXPECT_NEAR(expected4.Value(), Epic::DegreesToRadians(180.0f), 0.01f);
	EXPECT_NEAR(expected5.Value(), Epic::DegreesToRadians(160.0f), 0.01f);
}

TEST_F(RadianTests, NormalOf_NormalizesValue)
{
	Radian<float> test1{ Epic::DegreesToRadians(180.0f) };
	Radian<float> test2{ Epic::DegreesToRadians(720.0f) };
	Radian<float> test3{ Epic::DegreesToRadians(2000.0f) };
	Radian<float> test4{ Epic::DegreesToRadians(-180.f) };
	Radian<float> test5{ Epic::DegreesToRadians(-2000.0f) };

	Radian<float> expected1 = Radian<float>::NormalOf(test1);
	Radian<float> expected2 = Radian<float>::NormalOf(test2);
	Radian<float> expected3 = Radian<float>::NormalOf(test3);
	Radian<float> expected4 = Radian<float>::NormalOf(test4);
	Radian<float> expected5 = Radian<float>::NormalOf(test5);

	EXPECT_NEAR(expected1.Value(), Epic::DegreesToRadians(180.0f), 0.01f);
	EXPECT_NEAR(expected2.Value(), Epic::DegreesToRadians(0.0f), 0.01f);
	EXPECT_NEAR(expected3.Value(), Epic::DegreesToRadians(200.0f), 0.01f);
	EXPECT_NEAR(expected4.Value(), Epic::DegreesToRadians(180.0f), 0.01f);
	EXPECT_NEAR(expected5.Value(), Epic::DegreesToRadians(160.0f), 0.01f);
}

//////////////////////////////////////////////////////////////////////////////

class DegreeTests : public testing::Test
{
};

TEST_F(DegreeTests, Constructor_WithConvertibleDegree_HasConvertedValue)
{
	Degree<int> test = 10;
	Degree<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 10.0f);
}

TEST_F(DegreeTests, Constructor_WithValue_HasValue)
{
	float test = 10.0f;
	Degree<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 10.0f);
}

TEST_F(DegreeTests, Constructor_WithConvertibleValue_HasConvertedValue)
{
	int test = 10;
	Degree<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 10.0f);
}

TEST_F(DegreeTests, Constructor_WithRadian_HasValue)
{
	Radian<float> test = 3.141593f;
	Degree<float> expected{ test };

	EXPECT_FLOAT_EQ(expected.Value(), 180.0f);
}

TEST_F(DegreeTests, Constructor_WithConvertibleRadian_HasConvertedValue)
{
	Radian<float> test = 3.141593f;
	Degree<int> expected{ test };

	EXPECT_EQ(expected.Value(), 180);
}

TEST_F(DegreeTests, Sin_ReturnsSinOfValue)
{
	Degree<float> expected1{ 30.0f };
	Degree<float> expected2{ 90.0f };
	Degree<float> expected3{ 180.0f };

	EXPECT_NEAR(expected1.Sin(), 0.5f, 0.01f);
	EXPECT_NEAR(expected2.Sin(), 1.0f, 0.01f);
	EXPECT_NEAR(expected3.Sin(), 0.0f, 0.01f);
}

TEST_F(DegreeTests, Cos_ReturnsCosOfValue)
{
	Degree<float> expected1{ 60.0f };
	Degree<float> expected2{ 90.0f };
	Degree<float> expected3{ 180.0f };

	EXPECT_NEAR(expected1.Cos(), 0.5f, 0.01f);
	EXPECT_NEAR(expected2.Cos(), 0.0f, 0.01f);
	EXPECT_NEAR(expected3.Cos(), -1.0f, 0.01f);
}

TEST_F(DegreeTests, Tan_ReturnsTanOfValue)
{
	Degree<float> expected1{ 60.0f };
	Degree<float> expected2{ 10.0f };
	Degree<float> expected3{ 225.0f };

	EXPECT_NEAR(expected1.Tan(), 1.732051f, 0.01f);
	EXPECT_NEAR(expected2.Tan(), 0.176327f, 0.01f);
	EXPECT_NEAR(expected3.Tan(), 1.0f, 0.01f);
}

TEST_F(DegreeTests, SinCos_ReturnsSinAndCosOfValue)
{
	Degree<float> test1{ 30.0f };
	Degree<float> test2{ 60.0f };
	Degree<float> test3{ 90.0f };

	auto[expected1Sin, expected1Cos] = test1.SinCos();
	auto[expected2Sin, expected2Cos] = test2.SinCos();
	auto[expected3Sin, expected3Cos] = test3.SinCos();

	EXPECT_NEAR(expected1Sin, 0.5f, 0.01f);
	EXPECT_NEAR(expected1Cos, 0.866025f, 0.01f);
	EXPECT_NEAR(expected2Sin, 0.866025f, 0.01f);
	EXPECT_NEAR(expected2Cos, 0.5f, 0.01f);
	EXPECT_NEAR(expected3Sin, 1.0f, 0.01f);
	EXPECT_NEAR(expected3Cos, 0.0f, 0.01f);
}

TEST_F(DegreeTests, Normalize_NormalizesValue)
{
	Degree<float> expected1{ 180.0f };
	Degree<float> expected2{ 720.0f };
	Degree<float> expected3{ 2000.0f };
	Degree<float> expected4{ -180.f };
	Degree<float> expected5{ -2000.0f };

	expected1.Normalize();
	expected2.Normalize();
	expected3.Normalize();
	expected4.Normalize();
	expected5.Normalize();

	EXPECT_NEAR(expected1.Value(), 180.0f, 0.01f);
	EXPECT_NEAR(expected2.Value(), 0.0f, 0.01f);
	EXPECT_NEAR(expected3.Value(), 200.0f, 0.01f);
	EXPECT_NEAR(expected4.Value(), 180.0f, 0.01f);
	EXPECT_NEAR(expected5.Value(), 160.0f, 0.01f);
}

TEST_F(DegreeTests, NormalOf_NormalizesValue)
{
	Degree<float> test1{ 180.0f };
	Degree<float> test2{ 720.0f };
	Degree<float> test3{ 2000.0f };
	Degree<float> test4{ -180.f };
	Degree<float> test5{ -2000.0f };
	
	Degree<float> expected1 = Degree<float>::NormalOf(test1);
	Degree<float> expected2 = Degree<float>::NormalOf(test2);
	Degree<float> expected3 = Degree<float>::NormalOf(test3);
	Degree<float> expected4 = Degree<float>::NormalOf(test4);
	Degree<float> expected5 = Degree<float>::NormalOf(test5);

	EXPECT_NEAR(expected1.Value(), 180.0f, 0.01f);
	EXPECT_NEAR(expected2.Value(), 0.0f, 0.01f);
	EXPECT_NEAR(expected3.Value(), 200.0f, 0.01f);
	EXPECT_NEAR(expected4.Value(), 180.0f, 0.01f);
	EXPECT_NEAR(expected5.Value(), 160.0f, 0.01f);
}
