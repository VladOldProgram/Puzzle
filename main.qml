import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12


Window {
    id: w

    visible: true

    minimumWidth: 600
    maximumWidth: 600
    width: 600

    minimumHeight: cl.height
    maximumHeight: cl.height
    height: cl.height

    title: qsTr("Light'em up!")

    ColumnLayout {
        id: cl

        anchors.centerIn: w.contentItem
        spacing: 2

        Gameplay {
            id: gameplay

            onStopTimer: toolbar.stopTimer()
            onStartTimer: toolbar.startTimer()
        }

        Toolbar {
            id: toolbar

            onNewGame: gameplay.newGame()
            onQuitApp: Qt.quit()
        }
    }


    Dialog {
        id: loseDialog
        modal: true

        x: (parent.width - width)/2
        y: (parent.height - height)/2

        contentItem: Rectangle {
            Text {
                text: "Lose!"

                anchors.centerIn: parent

                font.pointSize: 28
            }
        }

        standardButtons: Dialog.Ok
    }

    Dialog {
        id: winDialog
        modal: true

        x: (parent.width - width)/2
        y: (parent.height - height)/2

        contentItem: Rectangle {
            Text {
                text: "Win!"

                anchors.centerIn: parent

                font.pointSize: 28
            }
        }

        standardButtons: Dialog.Ok
    }
}
