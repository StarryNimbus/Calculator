#include "math_engine.h"
#include <QSignalSpy>
#include <gtest/gtest.h>

class TestMathEngine : public ::testing::Test {};

TEST_F(TestMathEngine, Constructor) {
  MathEngine engine;
  EXPECT_EQ(engine.getLeftValue(), "0");
  EXPECT_EQ(engine.getRightValue(), "");
  EXPECT_EQ(engine.getOperationValue(), "");
  EXPECT_EQ(engine.isLeftDigitStarted(), false);
  EXPECT_EQ(engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, Clear) {
  MathEngine engine;
  engine.inputDigit("1");
  engine.inputDigit("2");
  engine.inputDigit("3");
  engine.setOperation("+");
  engine.inputDigit("4");
  engine.inputDigit("5");
  engine.inputDigit("6");

  EXPECT_EQ(engine.getLeftValue(), "123");
  EXPECT_EQ(engine.getRightValue(), "456");
  EXPECT_EQ(engine.getOperationValue(), "+");
  EXPECT_EQ(engine.isLeftDigitStarted(), true);
  EXPECT_EQ(engine.isRightDigitStarted(), true);

  engine.clear();

  EXPECT_EQ(engine.getLeftValue(), "0");
  EXPECT_EQ(engine.getRightValue(), "");
  EXPECT_EQ(engine.getOperationValue(), "");
  EXPECT_EQ(engine.isLeftDigitStarted(), false);
  EXPECT_EQ(engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveInvalidOperation) {
  MathEngine engine;
  engine.setOperation("invalid");
  EXPECT_FALSE(engine.resolve());
}

TEST_F(TestMathEngine, ResolveAddition) {
  MathEngine engine;
  engine.inputDigit("1");
  engine.inputDigit(".");
  engine.inputDigit("5");
  engine.setOperation("+");
  engine.inputDigit("2");
  engine.inputDigit(".");
  engine.inputDigit("4");
  EXPECT_TRUE(engine.resolve());
  EXPECT_EQ(engine.getLeftValue(), QString("3.90000"));
  EXPECT_EQ(engine.getRightValue(), "");
  EXPECT_EQ(engine.getOperationValue(), "");
  EXPECT_EQ(engine.isLeftDigitStarted(), false);
  EXPECT_EQ(engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveSubtraction) {
  MathEngine engine;
  engine.inputDigit("1");
  engine.inputDigit(".");
  engine.inputDigit("5");
  engine.setOperation("-");
  engine.inputDigit("2");
  engine.inputDigit(".");
  engine.inputDigit("4");
  EXPECT_TRUE(engine.resolve());
  EXPECT_EQ(engine.getLeftValue(), QString("-0.90000"));
  EXPECT_EQ(engine.getRightValue(), "");
  EXPECT_EQ(engine.getOperationValue(), "");
  EXPECT_EQ(engine.isLeftDigitStarted(), false);
  EXPECT_EQ(engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveMultiplication) {
  MathEngine engine;
  engine.inputDigit("1");
  engine.inputDigit(".");
  engine.inputDigit("5");
  engine.setOperation("*");
  engine.inputDigit("2");
  engine.inputDigit(".");
  engine.inputDigit("4");
  EXPECT_TRUE(engine.resolve());
  EXPECT_EQ(engine.getLeftValue(), QString("3.60000"));
  EXPECT_EQ(engine.getRightValue(), "");
  EXPECT_EQ(engine.getOperationValue(), "");
  EXPECT_EQ(engine.isLeftDigitStarted(), false);
  EXPECT_EQ(engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveDivisionByZero) {
  MathEngine engine;
  engine.inputDigit("1");
  engine.setOperation("/");
  engine.inputDigit("0");

  EXPECT_FALSE(engine.resolve());
  EXPECT_EQ(engine.getLeftValue(), "0");
  EXPECT_EQ(engine.getRightValue(), "");
  EXPECT_EQ(engine.getOperationValue(), "");
  EXPECT_EQ(engine.isLeftDigitStarted(), false);
  EXPECT_EQ(engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, ResolveDivision) {
  MathEngine engine;
  engine.inputDigit("1");
  engine.inputDigit(".");
  engine.inputDigit("5");
  engine.setOperation("/");
  engine.inputDigit("2");
  engine.inputDigit(".");
  engine.inputDigit("4");
  EXPECT_TRUE(engine.resolve());
  EXPECT_EQ(engine.getLeftValue(), QString("0.62500"));
  EXPECT_EQ(engine.getRightValue(), "");
  EXPECT_EQ(engine.getOperationValue(), "");
  EXPECT_EQ(engine.isLeftDigitStarted(), false);
  EXPECT_EQ(engine.isRightDigitStarted(), false);
}

TEST_F(TestMathEngine, InputDigitInvalidDigit) {
  MathEngine engine;
  EXPECT_FALSE(engine.inputDigit("90"));
  EXPECT_FALSE(engine.inputDigit("invalid"));
}

TEST_F(TestMathEngine, InputDigitValidDigits) {
  MathEngine engine;
  EXPECT_TRUE(engine.inputDigit("0"));
  EXPECT_TRUE(engine.inputDigit("1"));
  EXPECT_TRUE(engine.inputDigit("2"));
  EXPECT_TRUE(engine.inputDigit("3"));
  EXPECT_TRUE(engine.inputDigit("4"));
  EXPECT_TRUE(engine.inputDigit("5"));
  EXPECT_TRUE(engine.inputDigit("6"));
  EXPECT_TRUE(engine.inputDigit("7"));
  EXPECT_TRUE(engine.inputDigit("8"));
  EXPECT_TRUE(engine.inputDigit("9"));
  EXPECT_TRUE(engine.inputDigit("."));
}

TEST_F(TestMathEngine, InputDigitMultipleDecimalPoints) {
  MathEngine engine;
  engine.inputDigit("1");
  engine.inputDigit(".");
  EXPECT_EQ(engine.getLeftValue(), "1.");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  // add another decimal point
  EXPECT_FALSE(engine.inputDigit("."));
  EXPECT_EQ(engine.getLeftValue(), "1.");
}

TEST_F(TestMathEngine, InputDigitStartingWithDecimal) {
  MathEngine engine;
  engine.inputDigit(".");
  EXPECT_EQ(engine.getLeftValue(), "0.");
  EXPECT_TRUE(engine.isLeftDigitStarted());
}

TEST_F(TestMathEngine, InputDigitsStartingWithZero) {
  MathEngine engine;
  engine.inputDigit("0");
  EXPECT_EQ(engine.getLeftValue(), "0");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  engine.inputDigit(".");
  EXPECT_EQ(engine.getLeftValue(), "0.");
  EXPECT_TRUE(engine.isLeftDigitStarted());
}

TEST_F(TestMathEngine, InputDigitsHappyPath) {
  MathEngine engine;
  engine.inputDigit("1");
  EXPECT_EQ(engine.getLeftValue(), "1");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  engine.inputDigit("2");
  EXPECT_EQ(engine.getLeftValue(), "12");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  engine.inputDigit("3");
  EXPECT_EQ(engine.getLeftValue(), "123");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  engine.inputDigit(".");
  EXPECT_EQ(engine.getLeftValue(), "123.");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  engine.inputDigit("4");
  EXPECT_EQ(engine.getLeftValue(), "123.4");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  engine.inputDigit("5");
  EXPECT_EQ(engine.getLeftValue(), "123.45");
  EXPECT_TRUE(engine.isLeftDigitStarted());

  engine.inputDigit("6");
  EXPECT_EQ(engine.getLeftValue(), "123.456");
  EXPECT_TRUE(engine.isLeftDigitStarted());
}

// Note that setting the left or right operand is dependent on the operation
TEST_F(TestMathEngine, InputDigitsRightOperand) {
  MathEngine engine;
  engine.setOperation("+");
  engine.inputDigit("7");
  EXPECT_EQ(engine.getRightValue(), "7");
  EXPECT_TRUE(engine.isRightDigitStarted());

  engine.inputDigit("8");
  EXPECT_EQ(engine.getRightValue(), "78");
  EXPECT_TRUE(engine.isRightDigitStarted());

  engine.inputDigit("9");
  EXPECT_EQ(engine.getRightValue(), "789");
  EXPECT_TRUE(engine.isRightDigitStarted());
}

TEST_F(TestMathEngine, InvalidOperation) {
  MathEngine engine;
  EXPECT_FALSE(engine.setOperation("1"));
  EXPECT_EQ(engine.getOperationValue(), "");
}

TEST_F(TestMathEngine, ValidOperations) {
  MathEngine engine;
  EXPECT_TRUE(engine.setOperation("+"));
  EXPECT_EQ(engine.getOperationValue(), "+");

  // Previous operation should be resolved then overwritten
  EXPECT_TRUE(engine.setOperation("-"));
  EXPECT_EQ(engine.getOperationValue(), "-");

  EXPECT_TRUE(engine.setOperation("*"));
  EXPECT_EQ(engine.getOperationValue(), "*");

  EXPECT_TRUE(engine.setOperation("/"));
  EXPECT_EQ(engine.getOperationValue(), "/");
}
