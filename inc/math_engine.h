#ifndef MATH_ENGINE_H_
#define MATH_ENGINE_H_

#include <QObject>
#include <QString>
#include <unordered_set>

class MathEngine : public QObject {
  Q_OBJECT

  // clang-format off
  Q_PROPERTY(QString leftValue
             READ getLeftValue
             NOTIFY leftValueChanged)
  Q_PROPERTY(QString rightValue
             READ getRightValue
             NOTIFY rightValueChanged)
  Q_PROPERTY(QString operationValue
             READ getOperationValue
             NOTIFY operationChanged)
  // clang-format on

public:
  QString getLeftValue() const { return m_left; }
  QString getRightValue() const { return m_right; }
  QString getOperationValue() const { return m_operation; }

  Q_INVOKABLE void clear();
  Q_INVOKABLE void resolve();
  Q_INVOKABLE void inputDigit(const QString &val);
  Q_INVOKABLE void setOperation(const QString &val);

signals:
  void leftValueChanged();
  void rightValueChanged();
  void operationChanged();

private:
  [[nodiscard]] bool hasOperator() const;

  QString m_left{"0"};
  QString m_right{""};
  QString m_operation{""};

  // These variables are purely for this class to track whether the left or
  // right value has started being entered
  bool m_leftDigitStarted{false};
  bool m_rightDigitStarted{false};

  const std::unordered_set<QString> m_validOperations{"+", "-", "*", "/"};
  // The decimal point is a special case for input digits
  const std::unordered_set<QString> m_validDigits{"0", "1", "2", "3", "4", "5",
                                                  "6", "7", "8", "9", "."};
};

#endif /* MATH_ENGINE_H_ */
