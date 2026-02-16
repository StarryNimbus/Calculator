#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <qqml.h>

#include "math_engine.h"

int main(int argc, char *argv[]) {
  const QGuiApplication app(argc, argv);

  MathEngine math_engine;
  qmlRegisterSingletonInstance<MathEngine>("com.example.MathEngine", 1, 0,
                                           "MathEngine", &math_engine);

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/");
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty()) {
    return 1;
  }

  return app.exec();
}
