import QtQuick 2.9
import QtQuick.Window 2.2
import an.utility 1.0
import MyGlobalShortCut 1.0
Window
{
    id: mainWindow
    visible: true
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    flags: Qt.WA_TransparentForMouseEvent | Qt.WindowStaysOnTopHint
         | Qt.WA_TranslucentBackground | Qt.WA_WindowPropagation
         | Qt.SubWindow | Qt.FramelessWindowHint

    color: "transparent"
    title: qsTr("Magic Fish~~~")

    function receiveActivated() {
        console.log("mainWindow::receiveActivated");
        mainWindow.close();
    }


    Window
    {
        id: showWindow
        visible: true
        width: 256
        height: 256
        flags: Qt.FramelessWindowHint
        x: 0
        y: 0

        color: "transparent"

        Text {
            id: tips
            text: "lzw love gh"
            color: "red"
            font.bold: true
            font.family: "Microsoft YaHei"
            font.pixelSize: 9

            visible: false
        }

        MagicPool
        {
            id: magicPool
            anchors.fill: parent

            property int fish_pos_x: 0
            property int fish_pos_y: 0

            function randomMove()
            {
                magicPool.fish_pos_x = Math.random() * width;
                magicPool.fish_pos_y = Math.random() * height;
                showWindow.x = Math.random() * mainWindow.width;
                showWindow.y = Math.random() * mainWindow.height;
                magicPool.moveFish(magicPool.fish_pos_x, magicPool.fish_pos_y, false);
                console.log("randomMove")
                tips.visible = false
            }

            Timer
            {
                interval: 32
                repeat: true
                running: true
                onTriggered:
                {
                    if (!magicPool.moving) magicPool.randomMove();
                }
            }

            Component.onCompleted: randomMove();

            MouseArea
            {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: magicPool.moveFish(mouse.x, mouse.y, true);
                onReleased: {
                    console.log("menu.released")
                    mouse.accepted = false
                    tips.visible = true
                    tips.x = mouse.x
                    tips.y = mouse.y
                }
            }
        }
    }
}
