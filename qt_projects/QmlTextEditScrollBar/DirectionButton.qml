import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12
Item {
    id:root    
    property alias imagesource: image.source //设置不同图片
    signal     clicked //设置点击事件，方便引用

    Rectangle
    {
        id:background
        width: root.width
        height:root.height
        anchors.fill: parent
    }


    //轮廓
    Image {
        id: mask
        source: "qrc:/1.png"
        anchors.fill: parent
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true
        visible: false

    }

    OpacityMask {
        anchors.fill: background
        source: background
        maskSource: mask
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            root.clicked();//引用该自定义元素时，可以在使用onclick事件。
        }

    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
