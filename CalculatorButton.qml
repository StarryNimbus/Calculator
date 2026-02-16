import QtQuick
import QtQuick.Controls

import com.example.MathEngine

RoundButton {
    id: root

    readonly property real k_buttonSize: 75

    readonly property color k_operationColor: "#FF9F0A"
    readonly property color k_operationPressedColor: "#FFBD5C"
    readonly property color k_numberColor: "#343434"
    readonly property color k_numberPressedColor: "#4A4A4A"
    readonly property color k_functionColor: "#A5A5A5"
    readonly property color k_functionPressedColor: "#BFBFBF"

    // Query these values from CalculatorModel.qml
    property string label: ""
    property string type: ""

    text: root.label

    height: root.k_buttonSize
    width: height
    radius: height / 2

    font.pixelSize: 24
    font.weight: Font.Medium
    palette.buttonText: "#FFFFFF"

    background: Rectangle {
        id: background
        objectName: "background"
        radius: root.radius
        color: {
            if (root.down) {
                switch (root.type) {
                case "operation":
                    return root.k_operationPressedColor;
                case "number":
                    return root.k_numberPressedColor;
                case "function":
                    return root.k_functionPressedColor;
                case "reset":
                    return root.functionPressedColor;
                }
            } else {
                switch (root.type) {
                case "operation":
                    return root.k_operationColor;
                case "number":
                    return root.k_numberColor;
                case "function":
                    return root.k_functionColor;
                case "reset":
                    return root.k_functionColor;
                }
            }
        }
    }

    onClicked: {
        console.log("Button clicked: " + root.label);
        console.log("Button type: " + root.type);
        switch (root.type) {
        case "operation":
            MathEngine.setOperation(root.label);
            break;
        case "number":
            MathEngine.inputDigit(root.label);
            break;
        case "function":
        {
            if(root.label === "C") {
                MathEngine.clear();
            } else if (root.label === "=") {
                MathEngine.resolve();
            }
        }
        break;
        }
    }
}
