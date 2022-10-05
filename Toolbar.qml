import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    id: toolbar

    signal newGame()
    signal quitApp()

    property int seconds: 120

    function decreaser() {
        if (seconds > 0) {
            var currentTime = (~~(seconds/60) + ":" + (seconds % 60 > 9 ? seconds % 60 : "0" + seconds % 60))
            seconds--
            return currentTime
        }
        if (seconds <= 0) {
            loseDialog.open()
            timer.stop()
            return "0:00"
        }
    }

    function stopTimer() {
        timer.stop()
    }

    function startTimer() {
        timer.start()
    }

    Timer {
        id: timer

        interval: 1000
        running: true
        repeat: true

        onTriggered: {
            time.text = decreaser()
        }

    }

    Button {
        id: newGameButton

        text: "New Game"
        onClicked: newGame()
    }

    Button {
        id: quitButton

        text: "Quit"
        onClicked: quitApp()
    }

    Label {
        id: timerField

        Text {
            id: time

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            font.pointSize: 28
        }

        Layout.fillWidth: true
    }

    Shortcut {
        context: Qt.ApplicationShortcut
        sequences: ["Ctrl+N"]
        onActivated: newGame()
    }

    Shortcut {
        context: Qt.ApplicationShortcut
        sequences: [StandardKey.Close, "Ctrl+Q"]
        onActivated: quitApp()
    }
}
