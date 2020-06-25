import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 832
    height: 768
    title: qsTr("SNKRS")
    //color: "#87CEFA"
    color: "#6E6E6E"

    MTabBar {
        id: tabBarViewer
        anchors.top: root.top
        anchors.topMargin: 2
        anchors.left: root.left
        anchors.leftMargin: 0
        width: parent.width
        height: 64
    }

    PageOne {
        id: page1
        anchors.top: tabBarViewer.bottom
        anchors.topMargin: 2
        anchors.left: root.left
        anchors.leftMargin: 0

        width: parent.width
        height: parent.height - tabBarViewer.height
        visible: (tabBarViewer.index == 0) ? true : false
    }
}
