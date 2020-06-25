import QtQuick 2.2
import QtQuick.Controls 2.5

Rectangle {
    id: root
    width: 368
    height: 346
    color: "#87C056"
    border.width: 2
    opacity: 0.9
    radius: 8

    signal closeBtnClicked()

    property int btnNum: 0

    Rectangle{
        width: 364
        height: 2
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 2
        radius: 8
    }
    Text {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 10
        text: qsTr("loadPage")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    TextArea {
        id: textArea1
        x: 38
        y: 92
        width: 292
        height: 123
    }

    Button {
        id: button1
        x: 138
        y: 280
        text: qsTr("close")
        onClicked: {                    
            if(btnNum === 3)
            {
                //使用creatComponent方式创建时使用destroy()函数销毁
                root.destroy(100)
            }
            else
            {
                root.closeBtnClicked()
            }
        }
    }

    function changeBtnNum(num)
    {
        btnNum = num
    }
}


