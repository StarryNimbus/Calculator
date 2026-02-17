#include "math_engine.h"
#include <QSignalSpy>
#include <gtest/gtest.h>

class TestMathEngine : public ::testing::Test {
protected:
  void TearDown() override { m_engine.clear(); }
  MathEngine m_engine;
};

TEST_F(TestMathEngine, Constructor) {
  EXPECT_EQ(m_engine.getLeftValue(), "0");
  EXPECT_EQ(m_engine.getRightValue(), "");
  EXPECT_EQ(m_engine.getOperationValue(), "");
  EXPECT_EQ(m_engine.isLeftDigitStarted(), false);
  EXPECT_EQ(m_engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, Clear) {
  m_engine.inputDigit("1");
  m_engine.inputDigit("2");
  m_engine.inputDigit("3");
  m_engine.setOperation("+");
  m_engine.inputDigit("4");
  m_engine.inputDigit("5");
  m_engine.inputDigit("6");

  m_engine.clear();

  EXPECT_EQ(m_engine.getLeftValue(), "0");
  EXPECT_EQ(m_engine.getRightValue(), "");
  EXPECT_EQ(m_engine.getOperationValue(), "");
  EXPECT_EQ(m_engine.isLeftDigitStarted(), false);
  EXPECT_EQ(m_engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveInvalidOperation) {
  m_engine.setOperation("invalid");
  EXPECT_FALSE(m_engine.resolve());
}

TEST_F(TestMathEngine, ResolveAddition) {
  m_engine.inputDigit("1");
  m_engine.inputDigit(".");
  m_engine.inputDigit("5");
  m_engine.setOperation("+");
  m_engine.inputDigit("2");
  m_engine.inputDigit(".");
  m_engine.inputDigit("4");
  EXPECT_TRUE(m_engine.resolve());
}

TEST_F(TestMathEngine, ResolveSubtraction) {
  m_engine.inputDigit("1");
  m_engine.inputDigit(".");
  m_engine.inputDigit("5");
  m_engine.setOperation("-");
  m_engine.inputDigit("2");
  m_engine.inputDigit(".");
  m_engine.inputDigit("4");
  EXPECT_TRUE(m_engine.resolve());
}

TEST_F(TestMathEngine, ResolveMultiplication) {
  m_engine.inputDigit("1");
  m_engine.inputDigit(".");
  m_engine.inputDigit("5");
  m_engine.setOperation("*");
  m_engine.inputDigit("2");
  m_engine.inputDigit(".");
  m_engine.inputDigit("4");
  EXPECT_TRUE(m_engine.resolve());
  EXPECT_EQ(m_engine.getLeftValue(), QString("3.60000"));
  EXPECT_EQ(m_engine.getRightValue(), "");
  EXPECT_EQ(m_engine.getOperationValue(), "");
  EXPECT_EQ(m_engine.isLeftDigitStarted(), false);
  EXPECT_EQ(m_engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveDivisionByZero) {
  m_engine.inputDigit("1");
  m_engine.setOperation("/");
  m_engine.inputDigit("0");

  EXPECT_FALSE(m_engine.resolve());
  EXPECT_EQ(m_engine.getLeftValue(), "0");
  EXPECT_EQ(m_engine.getRightValue(), "");
  EXPECT_EQ(m_engine.getOperationValue(), "");
  EXPECT_EQ(m_engine.isLeftDigitStarted(), false);
  EXPECT_EQ(m_engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveDivision) {
  m_engine.inputDigit("1");
  m_engine.inputDigit(".");
  m_engine.inputDigit("5");
  m_engine.setOperation("/");
  m_engine.inputDigit("2");
  m_engine.inputDigit(".");
  m_engine.inputDigit("4");
  EXPECT_TRUE(m_engine.resolve());
  EXPECT_EQ(m_engine.getLeftValue(), QString("0.62500"));
  EXPECT_EQ(m_engine.getRightValue(), "");
  EXPECT_EQ(m_engine.getOperationValue(), "");
  EXPECT_EQ(m_engine.isLeftDigitStarted(), false);
  EXPECT_EQ(m_engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, InputDigitInvalidDigit) {
  EXPECT_FALSE(m_engine.inputDigit("90"));
  EXPECT_FALSE(m_engine.inputDigit("invalid"));
}

TEST_F(TestMathEngine, InputDigitValidDigits) {
  EXPECT_TRUE(m_engine.inputDigit("0"));
  EXPECT_TRUE(m_engine.inputDigit("1"));
  EXPECT_TRUE(m_engine.inputDigit("2"));
  EXPECT_TRUE(m_engine.inputDigit("3"));
  EXPECT_TRUE(m_engine.inputDigit("4"));
  EXPECT_TRUE(m_engine.inputDigit("5"));
  EXPECT_TRUE(m_engine.inputDigit("6"));
  EXPECT_TRUE(m_engine.inputDigit("7"));
  EXPECT_TRUE(m_engine.inputDigit("8"));
  EXPECT_TRUE(m_engine.inputDigit("9"));
  EXPECT_TRUE(m_engine.inputDigit("."));
}

TEST_F(TestMathEngine, InputDigitMultipleDecimalPoints) {
  m_engine.inputDigit("1");
  m_engine.inputDigit(".");
  EXPECT_EQ(m_engine.getLeftValue(), "1.");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  // add another decimal point
  EXPECT_FALSE(m_engine.inputDigit("."));
  EXPECT_EQ(m_engine.getLeftValue(), "1.");
}

TEST_F(TestMathEngine, InputDigitStartingWithDecimal) {
  m_engine.inputDigit(".");
  EXPECT_EQ(m_engine.getLeftValue(), "0.");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());
}

TEST_F(TestMathEngine, InputDigitsStartingWithZero) {
  m_engine.inputDigit("0");
  EXPECT_EQ(m_engine.getLeftValue(), "0");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  m_engine.inputDigit(".");
  EXPECT_EQ(m_engine.getLeftValue(), "0.");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());
}

TEST_F(TestMathEngine, InputDigitsHappyPath) {
  m_engine.inputDigit("1");
  EXPECT_EQ(m_engine.getLeftValue(), "1");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  m_engine.inputDigit("2");
  EXPECT_EQ(m_engine.getLeftValue(), "12");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  m_engine.inputDigit("3");
  EXPECT_EQ(m_engine.getLeftValue(), "123");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  m_engine.inputDigit(".");
  EXPECT_EQ(m_engine.getLeftValue(), "123.");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  m_engine.inputDigit("4");
  EXPECT_EQ(m_engine.getLeftValue(), "123.4");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  m_engine.inputDigit("5");
  EXPECT_EQ(m_engine.getLeftValue(), "123.45");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());

  m_engine.inputDigit("6");
  EXPECT_EQ(m_engine.getLeftValue(), "123.456");
  EXPECT_TRUE(m_engine.isLeftDigitStarted());
}

// Note that setting the left or right operand is dependent on the operation
TEST_F(TestMathEngine, InputDigitsRightOperand) {
  m_engine.setOperation("+");
  m_engine.inputDigit("7");
  EXPECT_EQ(m_engine.getRightValue(), "7");
  EXPECT_TRUE(m_engine.isRightDigitStarted());

  m_engine.inputDigit("8");
  EXPECT_EQ(m_engine.getRightValue(), "78");
  EXPECT_TRUE(m_engine.isRightDigitStarted());

  m_engine.inputDigit("9");
  EXPECT_EQ(m_engine.getRightValue(), "789");
  EXPECT_TRUE(m_engine.isRightDigitStarted());
}

TEST_F(TestMathEngine, InvalidOperation) {
  EXPECT_FALSE(m_engine.setOperation("1"));
  EXPECT_EQ(m_engine.getOperationValue(), "");
}

TEST_F(TestMathEngine, ValidOperations) {
  EXPECT_TRUE(m_engine.setOperation("+"));
  EXPECT_EQ(m_engine.getOperationValue(), "+");

  // Previous operation should be resolved then overwritten
  EXPECT_TRUE(m_engine.setOperation("-"));
  EXPECT_EQ(m_engine.getOperationValue(), "-");

  EXPECT_TRUE(m_engine.setOperation("*"));
  EXPECT_EQ(m_engine.getOperationValue(), "*");

  EXPECT_TRUE(m_engine.setOperation("/"));
  EXPECT_EQ(m_engine.getOperationValue(), "/");
}
