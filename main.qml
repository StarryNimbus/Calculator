import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.example.MathEngine

Window {
    id: window

    width: 350
    height: 500
    visible: true

    Rectangle {
        id: root
        anchors.fill: parent

        color: "#1C1C1E"

        Text {
            id: displayText

            anchors {
                left: root.left
                right: root.right
                bottom: buttonGrid.top
                bottomMargin: 25
            }

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pixelSize: 24
            text: {
                var operation = MathEngine.operationValue == "" ? "" : MathEngine.operationValue;
                var right = MathEngine.rightValue == "0" ? "" : MathEngine.rightValue;
                return MathEngine.leftValue + " " + operation + " " + right;
            }
            color: "#FFFFFF"
        }

        CalculatorModel {
            id: calcModel
        }

        GridLayout {
            id: buttonGrid

            anchors {
                bottom: root.bottom
                bottomMargin: 25
                horizontalCenter: root.horizontalCenter
            }

            columns: 4
            rows: 5
            columnSpacing: 5
            rowSpacing: 5

            Repeater {
                model: calcModel.model
                CalculatorButton {
                    label: model.name
                    type: model.type

                    Layout.preferredWidth: 75
                    Layout.preferredHeight: 75
                    Layout.minimumWidth: 75
                    Layout.minimumHeight: 75
                    Layout.maximumWidth: 75
                    Layout.maximumHeight: 75
                }
            }
        }
    }
}
