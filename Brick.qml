import QtQuick 2.12

Rectangle {
    width: 60
    height: 60
    color: "darkgray"

    property int config: 14
    property bool light: false

    border.width: 1
    border.color: "black"

    function rotate() {
        config = (config >>> 1) | ((config & 1) << 3)
    }

    signal rotated(int config)

    Rectangle {
        x: 29
        y: 1
        width: 2
        height: 30
        color: light ? "yellow" : "white"
        visible: (parent.config & 8) !== 0
    }

    Rectangle {
        x: 1
        y: 29
        width: 30
        height: 2
        color: light ? "yellow" : "white"
        visible: (parent.config & 4) !== 0
    }

    Rectangle {
        x: 29
        y: 29
        width: 2
        height: 30
        color: light ? "yellow" : "white"
        visible: (parent.config & 2) !== 0
    }

    Rectangle {
        x: 29
        y: 29
        width: 30
        height: 2
        color: light ? "yellow" : "white"
        visible: (parent.config & 1) !== 0
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            rotate()
            rotated(parent.config)
        }
    }
}
