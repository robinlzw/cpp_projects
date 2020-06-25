import QtQuick 2.12
import QtQuick.Controls 2.5
Rectangle{
    id:root
    //z:1
    property alias imagesource: image.source //设置不同图片

//    property alias text: textname.text  //这样设置可以方便更改text的文字
//    property alias textcolor: textname.color //设置文字颜色
//    property alias textsize:textname.font.pixelSize //设置文字大小
    signal     clicked //设置点击事件，方便引用
    color: "blue" //背景设置透明色
    Rectangle
    {
        id:imageup
        width: root.width
        height:root.height
        //height:(root.height*3)/5
        //color: "#00000000"
        anchors.horizontalCenter:parent.horizontalCenter//设置元素与父元素水平居中。
    Image {
        //z:2
        id: image
        anchors.fill: parent//填充整个父元素
          }
    }
//    Rectangle
//    {
//        y:imageup.height
//        width: root.width
//        height: (root.height*2)/5
//        color: "#00000000"
//        anchors.horizontalCenter:parent.horizontalCenter
//    Text {
//        z:2
//        id: textname
//        font.pixelSize:        14
//        anchors.centerIn:parent
//        color: "#ffffffff"
//        }
//    }
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
