import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import Poewr_Key 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: root
    visible: true
    width: 832
    height: 768
    title: qsTr("SNKRS")
    //color: "#87CEFA"
    color: "#6E6E6E"

    Dialog {
        id: changePosDialog;
        x:(parent.width-width)/2;
        y:(parent.height-height)/2;
        implicitWidth: 500;
        implicitHeight: 300;
        title: "输入序列号";
        modal: true;
        focus: true;
        visible: false

        standardButtons: Dialog.Ok | Dialog.Cancel


        Column {
            anchors.fill: parent
            Text {
                text: "请输入序列号"
                height: 40
            }
            TextField {
                id: changePosDialogInput
                width: parent.width * 0.75
                focus: true
                onFocusChanged: console.log("Focus changed " + focus)
            }
        }

        onAccepted: {
            console.log("Ok clicked, and changePosDialogInput.text = " + changePosDialogInput.text)
        }
        onRejected: console.log("Cancel clicked")
    }


    Rectangle {
        id: inputSerialNumRec


        Poewr_Key {
            id: powerKey

        }
    }

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

    PageTwo {
        id: page2
        anchors.top: tabBarViewer.bottom
        anchors.topMargin: 2
        anchors.left: root.left
        anchors.leftMargin: 0

        width: parent.width
        height: parent.height - tabBarViewer.height
        visible: (tabBarViewer.index == 1) ? true : false
    }

    PageThree {
        id: page3
        anchors.top: tabBarViewer.bottom
        anchors.topMargin: 2
        anchors.left: root.left
        anchors.leftMargin: 0

        width: parent.width
        height: parent.height - tabBarViewer.height
        visible: (tabBarViewer.index == 2) ? true : false
    }

    PageFour {
        id: page4
        anchors.top: tabBarViewer.bottom
        anchors.topMargin: 2
        anchors.left: root.left
        anchors.leftMargin: 0

        width: parent.width
        height: parent.height - tabBarViewer.height
        visible: (tabBarViewer.index == 3) ? true : false
    }
}
