import QtQuick 2.12

Rectangle{
    id:root
    //z:1

    //property alias text: text.text  //这样设置可以方便更改text的文字
    property alias imagesource: image.source //设置不同图片
    //property alias textcolor: text.color //设置文字颜色
    //property alias textsize:text.font.pixelSize //设置文字大小
    signal     clicked //设置点击事件，方便引用
    color: "#00000000" //背景设置透明色
	radius: width/2
	
    Rectangle
    {
        id:imageup
        width: 50
        height:50
		//radius: width/2
        color: "#00000000"
        anchors.horizontalCenter:parent.horizontalCenter//设置元素与父元素水平居中。
    Image {
        //z:2
        id: image
		antialiasing: true
		smooth: true
        anchors.fill: parent//填充整个父元素
          }
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

