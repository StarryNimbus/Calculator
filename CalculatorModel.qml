import QtQml
import QtQml.Models

QtObject {
    id: root

    // Order matters for the layout
    property ListModel model: ListModel {
        // First row
        ListElement {
            name: "7"
            type: "number"
        }
        ListElement {
            name: "8"
            type: "number"
        }
        ListElement {
            name: "9"
            type: "number"
        }
        ListElement {
            name: "/"
            type: "operation"
        }

        // Second row
        ListElement {
            name: "4"
            type: "number"
        }
        ListElement {
            name: "5"
            type: "number"
        }
        ListElement {
            name: "6"
            type: "number"
        }
        ListElement {
            name: "*"
            type: "operation"
        }

        // Third row
        ListElement {
            name: "1"
            type: "number"
        }
        ListElement {
            name: "2"
            type: "number"
        }
        ListElement {
            name: "3"
            type: "number"
        }
        ListElement {
            name: "-"
            type: "operation"
        }

        // Fourth row
        ListElement {
            name: "C"
            type: "function"
        }
        ListElement {
            name: "0"
            type: "number"
        }
        ListElement {
            name: "."
            type: "number" // special case for decimal point
        }
        ListElement {
            name: "+"
            type: "operation"
        }

        // Fifth row
        ListElement {
            name: "="
            type: "function"
        }
    }
}
