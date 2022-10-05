import QtQuick 2.12
import QtQuick.Layouts 1.12

GridLayout {
    id: gl

    width: 600
    height: 600

    columns: 10
    rows: 10

    columnSpacing: 0
    rowSpacing: 0

    signal stopTimer()
    signal startTimer()

    function newGame() {
        var newGameConfigs = helper.newGame()
        for (var i = 0; i < newGameConfigs.length; i++)
            bricks.itemAt(i).config = newGameConfigs[i]
        gl.light()
        toolbar.seconds = 120
        startTimer()
    }

    function light() {
        var brickConfigs = []
        for (var i = 0; i < bricks.count; i++)
            brickConfigs.push(bricks.itemAt(i).config)

        var lightenedBricks = 0
        var brickLights = helper.light(brickConfigs)
        for (i = 0; i < brickLights.length; i++) {
            bricks.itemAt(i).light = brickLights[i]
            if (brickLights[i] === true)
                lightenedBricks++
        }

        if (lightenedBricks === 100) {
            stopTimer()
            winDialog.open()
        }
    }

    Repeater {
        id: bricks
        model: 100

        Brick {
            onRotated: gl.light()
        }
    }

    Component.onCompleted: {
        newGame()
        gl.light()
    }
}
