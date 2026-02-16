#include "math_engine.h"

#include <cmath>
#include <iostream>

void MathEngine::clear() {
  m_left = "0";
  m_right = "0";
  m_operation = "";

  m_leftDigitStarted = false;
  m_rightDigitStarted = false;

  emit leftValueChanged();
  emit rightValueChanged();
  emit operationChanged();
}

void MathEngine::resolve() {
  // Check if val is a valid operation
  if (m_validOperations.find(m_operation) == m_validOperations.end()) {
    std::cerr << "Invalid operation: " << m_operation.toStdString()
              << std::endl;
    std::cerr << "Nothing to resolve" << std::endl;
    return;
  }

  double result = 0;
  double leftOperand = m_left.toDouble();
  double rightOperand = m_right.toDouble();
  if (m_operation == "+") {
    result = leftOperand + rightOperand;
  } else if (m_operation == "-") {
    result = leftOperand - rightOperand;
  } else if (m_operation == "*") {
    result = leftOperand * rightOperand;
  } else if (m_operation == "/") {
    // division by zero check
    // qFuzzyIsNull is a Qt function that checks if a double is close to zero,
    // it is more robust than checking if rightOperand == 0 because it takes
    // into account floating point precision
    if (qFuzzyIsNull(rightOperand)) {
      // Current behavior is to reset and early return
      std::cerr << "Division by zero" << std::endl;
      clear();
      return;
    }
    result = leftOperand / rightOperand;
  } else {
    // Ideally, this should never happen because we check for valid operations
    std::cerr << "Invalid operation: " << m_operation.toStdString()
              << std::endl;
    clear();
    return;
  }

  m_left = QString::number(result, 'f',
                           5); // arbitrary precision up to 5 decimal places
  m_right = "0";
  m_operation = "";
  m_leftDigitStarted = false;
  m_rightDigitStarted = false;

  emit leftValueChanged();
  emit rightValueChanged();
  emit operationChanged();
}

void MathEngine::inputDigit(const QString &val) {
  // Validate the input digit or decimal point
  if (m_validDigits.find(val) == m_validDigits.end()) {
    std::cerr << "Invalid digit or decimal point: " << val.toStdString()
              << std::endl;
    return;
  }

  // Determine which operand to update
  bool updateLeft = !hasOperator();
  QString &current = updateLeft ? m_left : m_right;
  bool &digitStarted = updateLeft ? m_leftDigitStarted : m_rightDigitStarted;
  auto valueChanged = [&]() {
    emit(updateLeft ? leftValueChanged() : rightValueChanged());
  };

  // Only allow a single decimal point
  if (val == "." && current.contains(".")) {
    std::cerr << "Multiple decimal points" << std::endl;
    return;
  }

  // If not entered yet, start with "0" if input is ".", otherwise with val
  if (!digitStarted) {
    digitStarted = true;
    if (val == ".") {
      std::cout << "Starting with 0." << std::endl;
      current = "0.";
    } else {
      std::cout << "Starting with " << val.toStdString() << std::endl;
      current = val;
    }
    valueChanged();
    return;
  }

  // Prevent weird numbers like "00" or "05"
  if (current == "0" && val != ".") {
    current = val; // Example: "00" becomes "0" and "05" becomes "5")
    valueChanged();
    return;
  }

  // Usual case: append digit/decimal
  current += val;
  valueChanged();
}

void MathEngine::setOperation(const QString &val) {
  // Check if val is a valid operation
  if (m_validOperations.find(val) == m_validOperations.end()) {
    std::cerr << "Invalid operation: " << val.toStdString() << std::endl;
    return;
  }

  // Following requirement; chaining operations should work as it typically does
  // on a 4-function calculator – i.e.,operations are evaluated in input order
  // (no operator precedence).
  if (hasOperator()) {
    resolve();
  }

  m_operation = val;
  emit operationChanged();
}

bool MathEngine::hasOperator() const { return !m_operation.isEmpty(); }
