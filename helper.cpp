#include "helper.h"

#include <QRandomGenerator>
#include <QStack>
#include <QPair>

Helper::Helper(QObject *parent) : QObject(parent)
{

}

QVector<int> Helper::newGame()
{
    QVector<int> bricks = {
        1, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        4, 5, 5, 5, 5, 5, 5, 5, 5, 12,
    };

    // Generating the game board using a depth-first search algorithm
    QStack<QPair<int, int>> stack;
    QVector<int> visited(100);

    int rootRandomX = QRandomGenerator::global()->bounded(0, 9);
    int rootRandomY = QRandomGenerator::global()->bounded(0, 9);
    stack.push(qMakePair(rootRandomX, rootRandomY));
    visited[10 * rootRandomY + rootRandomX] = 0;

    auto offset = [&](int dx, int dy)
    {
        return (10 * (stack.top().second + dy) + stack.top().first + dx);
    };

    while (!stack.isEmpty()) {
        QVector<int> adjBricks;
        int offsetUp = offset(0, -1);
        int offsetLeft = offset(-1, 0);
        int offsetRight = offset(1, 0);
        int offsetDown = offset(0, 1);
        int noOffset = offset(0, 0);

        // Checking availability
        // Up(8)
        if (stack.top().second > 0 && offsetUp > -1 && !visited[offsetUp])
            adjBricks.push_back(0);
        // Left(4)
        if (stack.top().first > 0 && offsetLeft > -1 && !visited[offsetLeft])
            adjBricks.push_back(3);
        // Right(1)
        if (stack.top().first < 10 && offsetRight < 100 && offsetRight % 10 != 0 && !visited[offsetRight])
            adjBricks.push_back(1);
        // Down(2)
        if (stack.top().second < 10 && offsetDown < 100 && !visited[offsetDown])
            adjBricks.push_back(2);

        // Making a tree
        if (!adjBricks.empty()) {
            int nextBrick = adjBricks[QRandomGenerator::global()->bounded(0, adjBricks.size())];

            switch (nextBrick) {
            case 0: // Up
                visited[offsetUp] |= 2;
                visited[noOffset] |= 8;
                stack.push(qMakePair((stack.top().first), (stack.top().second - 1)));
                break;

            case 1: // Right
                visited[offsetRight] |= 4;
                visited[noOffset] |= 1;
                stack.push(qMakePair((stack.top().first + 1), (stack.top().second)));
                break;

            case 2: // Down
                visited[offsetDown] |= 8;
                visited[noOffset] |= 2;
                stack.push(qMakePair((stack.top().first), (stack.top().second + 1)));
                break;

            case 3: // Left
                visited[offsetLeft] |= 1;
                visited[noOffset] |= 4;
                stack.push(qMakePair((stack.top().first - 1), (stack.top().second)));
                break;
            }
        }
        else
            stack.pop();
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            bricks[10 * i + j] = visited[10 * i + j];
    }

    // Random rotating bricks
    for (int i = 0; i < 100; i++) {
        int k = QRandomGenerator::global()->bounded(0, 3);
        for (int j = 0; j < k; j++)
            bricks[i] = (bricks[i] >> 1) | ((bricks[i] & 1) << 3);
    }

    return bricks;
}

QVector<bool> Helper::light(QVector<int> bricks)
{
    QVector<bool> lights;
    QStack<QPair<int, int>> stack;

    lights.push_back(true);
    for (int i = 1; i < 100; i++) {
        lights.push_back(false);
    }

    stack.push_back(qMakePair(0, 0));

    auto offset = [&](int dx, int dy)
    {
        return (10 * (stack.top().second + dy) + stack.top().first + dx);
    };

    // Lightning the bricks using a depth-first search algorithm
    while (!stack.isEmpty()) {
        QVector<int> adjBricks;
        int offsetUp = offset(0, -1);
        int offsetLeft = offset(-1, 0);
        int offsetRight = offset(1, 0);
        int offsetDown = offset(0, 1);
        int noOffset = offset(0, 0);

        // Checking for availability
        // Up(8)
        if (stack.top().second > 0 && offsetUp > -1 && bricks[offsetUp] && !lights[offsetUp]
                && bricks[offsetUp] & 2 && bricks[noOffset] & 8)
            adjBricks.push_back(0);
        // Left(4)
        if (stack.top().first > 0 && offsetLeft > -1 && bricks[offsetLeft] && !lights[offsetLeft]
                && bricks[offsetLeft] & 1 && bricks[noOffset] & 4)
            adjBricks.push_back(3);
        // Right(1)
        if (stack.top().first < 10 && offsetRight < 100 && offsetRight % 10 != 0 && bricks[offsetRight] && !lights[offsetRight]
                && bricks[offsetRight] & 4 && bricks[noOffset] & 1)
            adjBricks.push_back(1);
        // Down(2)
        if (stack.top().second < 10 && offsetDown < 100 && bricks[offsetDown] && !lights[offsetDown]
                && bricks[offsetDown] & 8 && bricks[noOffset] & 2)
            adjBricks.push_back(2);

        // Lightning the bricks
        if (!adjBricks.isEmpty()) {
            int nextBrick = adjBricks[0];

            switch (nextBrick) {
            case 0:
                lights[offsetUp] = true;
                stack.push(qMakePair((stack.top().first), (stack.top().second - 1)));
                break;

            case 1:
                lights[offsetRight] = true;
                stack.push(qMakePair((stack.top().first + 1), (stack.top().second)));
                break;

            case 2:
                lights[offsetDown] = true;
                stack.push(qMakePair((stack.top().first), (stack.top().second + 1)));
                break;

            case 3:
                lights[offsetLeft] = true;
                stack.push(qMakePair((stack.top().first - 1), (stack.top().second)));
                break;
            }
        }
        else
            stack.pop();
    }

    return lights;
}
