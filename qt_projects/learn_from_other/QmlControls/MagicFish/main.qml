import QtQuick 2.9
import QtQuick.Window 2.2
import an.utility 1.0

Window
{
    id: mainWindow
    visible: true
    width: 1080
    height: 960
//    width: Screen.desktopAvailableWidth
//    height: Screen.desktopAvailableHeight
    //flags: Qt.FramelessWindowHint | Qt.Tool
    flags: Qt.Tool
    color: "transparent"
    title: qsTr("Magic Fish~~~")

    Rectangle
    {
        anchors.fill: parent
        color: "#1109A3DC"
    }

    MagicPool
    {
        id: magicPool
        anchors.fill: parent

        function randomMove()
        {
            var r_x = Math.random() * width;
            var r_y = Math.random() * height;
            magicPool.moveFish(r_x, r_y, false);
        }

        Timer
        {
            interval: 1500
            repeat: true
            running: true
            onTriggered:
            {
                if (Math.random() > 0.6 && !magicPool.moving) magicPool.randomMove();
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
            }
        }
    }
}
