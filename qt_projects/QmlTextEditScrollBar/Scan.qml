import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

import QmlKey 1.0
import QmlScan 1.0

Rectangle {
    id: sacnRoot
    visible: true
    color: "#F0FFFF"	//color: "#E1FFFF"
    //width: parent.width
    //height: parent.height
    width: rootWidth*0.925
    height: rootHeight*0.925


    property bool startScan: false
    property bool ret: false

    Image{
        anchors.horizontalCenter:sacnRoot.horizontalCenter
        anchors.verticalCenter:sacnRoot.verticalCenter
        anchors.fill: parent
        source:"qrc:/Resources/wifibackground.png"
    }

    QmlScan{
        id:mapScanControl
    }

    Rectangle {
            id: scanViewer;
            x:sacnRoot.width*0.025
            y:sacnRoot.height*0.05

            width: sacnRoot.width*0.8
            height: sacnRoot.height*0.925
            //anchors.top: sacnRoot
            //anchors.topMargin: sacnRoot.height*0.25
            visible: true
			color:"#808080"

            Flickable {

                width: parent.width; height: parent.height
                contentWidth: scanpainter.width; contentHeight: scanpainter.height
                clip:               true
                //Image { id: scanpainter; source: "file:"+"test.png" }
                Image { id: scanpainter; source: "" ;cache:false}
            }
    }

    Connections{
        target: skey_event
        onFileUpdate:{
	
           //scanpainter.addNewPicture("test.png")
	   scanpainter.source=""
           scanpainter.source="file:"+"image/test.png"
        }

    }

    Rectangle

        {
            //这个是最外层的圆

            id:pie

            x:rootWidth*0.7825
            y:rootHeight*0.1

            width: rootWidth*0.12

            height: rootWidth*0.12

            color: Qt.rgba(0.5,0.5,0.5,0.0)//透明，并且透明度为0

            border.color: "#00000000"


            radius: rootWidth*0.06


            Item {
                id:buttonup
                x:rootWidth*0.035
                y:0
                signal     clicked //设置点击事件，方便引用
                width: rootWidth*0.0525
                height: rootHeight*0.055

                Image {
                    id: backgroundup
                    source: "qrc:/Resources/upbackground.png"
                    sourceSize: Qt.size(parent.width, parent.height)
                    anchors.fill: parent
                    smooth: true
                    visible: false
                }

                //轮廓
                Image {
                    id: maskup
                    source: "qrc:/Resources/up.png"
                    anchors.fill: parent
                    sourceSize: Qt.size(parent.width, parent.height)
                    smooth: true
                    visible: false

                }

                OpacityMask {
                    anchors.fill: backgroundup
                    source: backgroundup
                    maskSource: maskup
                }

                MouseArea
                {
                    anchors.fill: buttonup
                    onClicked:
                    {
                        buttonup.clicked();//引用该自定义元素时，可以在使用onclick事件。

                    }

                }
            }

            Item {
                id:buttondown
                x:rootWidth*0.0375
                y:rootHeight*0.16

                signal     clicked //设置点击事件，方便引用
                width: rootWidth*0.05
                height: rootHeight*0.055

                Image {
                    id: backgrounddown
                    source: "qrc:/Resources/downbackground.png"
                    sourceSize: Qt.size(parent.width, parent.height)
                    anchors.fill: parent
                    smooth: true
                    visible: false
                }

                //轮廓
                Image {
                    id: maskdown
                    source: "qrc:/Resources/down.png"
                    anchors.fill: parent
                    sourceSize: Qt.size(parent.width, parent.height)
                    smooth: true
                    visible: false

                }

                OpacityMask {
                    anchors.fill: backgrounddown
                    source: backgrounddown
                    maskSource: maskdown
                }

                MouseArea
                {
                    anchors.fill: buttondown
                    onClicked:
                    {
                        buttonup.clicked();//引用该自定义元素时，可以在使用onclick事件。
                        console.log("down.png")
                        console.log("rootWidth:"+rootWidth)
                        console.log("rootHeight:"+rootHeight)
                    }

                }
            }


            Item {
                id:buttonleft
                //x:rootWidth*0.03275
                //y:5
                x:0
                y:rootHeight*0.055

                signal     clicked //设置点击事件，方便引用
                width: rootHeight*0.055

                height:rootWidth*0.05

                Image {
                    id: backgroundleft
                    source: "qrc:/Resources/leftbackground.png"
                    sourceSize: Qt.size(parent.width, parent.height)
                    anchors.fill: parent
                    smooth: true
                    visible: false
                }

                //轮廓
                Image {
                    id: maskleft
                    source: "qrc:/Resources/left.png"
                    anchors.fill: parent
                    sourceSize: Qt.size(parent.width, parent.height)
                    smooth: true
                    visible: false

                }

                OpacityMask {
                    anchors.fill: backgroundleft
                    source: backgroundleft
                    maskSource: maskleft
                }

                MouseArea
                {
                    anchors.fill: buttonleft
                    onClicked:
                    {
                        buttonleft.clicked();//引用该自定义元素时，可以在使用onclick事件。
                        console.log("left.png")
                    }

                }
            }

            Item {
                id:buttonright
                //x:rootWidth*0.03275
                //y:5
                x:rootWidth*0.0925

                y:rootHeight*0.06

                signal     clicked //设置点击事件，方便引用
                width: rootHeight*0.055

                height:rootWidth*0.05

                Image {
                    id: backgroundright
                    source: "qrc:/Resources/rightbackground.png"
                    sourceSize: Qt.size(parent.width, parent.height)
                    anchors.fill: parent
                    smooth: true
                    visible: false
                }

                //轮廓
                Image {
                    id: maskright
                    source: "qrc:/Resources/right.png"
                    anchors.fill: parent
                    sourceSize: Qt.size(parent.width, parent.height)
                    smooth: true
                    visible: false

                }

                OpacityMask {
                    anchors.fill: backgroundright
                    source: backgroundright
                    maskSource: maskright
                }

                MouseArea
                {
                    anchors.fill: buttonright
                    onClicked:
                    {
                        buttonright.clicked();//引用该自定义元素时，可以在使用onclick事件。
                        console.log("right.png")
                    }

                }
            }


            Item {
                id:buttonmid
                //x:rootWidth*0.03275
                //y:5
                x:rootWidth*0.042
                y:rootHeight*0.07

                signal     clicked //设置点击事件，方便引用
                width: rootWidth*0.04

                height:rootHeight*0.0725

                Image {
                    id: backgroundmid
                    source: "qrc:/Resources/stop.png"
                    sourceSize: Qt.size(parent.width, parent.height)
                    anchors.fill: parent
                    smooth: true
                    visible: false
                }

                //轮廓
                Image {
                    id: maskmid
                    source: "qrc:/Resources/stop.png"
                    anchors.fill: parent
                    sourceSize: Qt.size(parent.width, parent.height)
                    smooth: true
                    visible: false

                }

                OpacityMask {
                    anchors.fill: backgroundmid
                    source: backgroundmid
                    maskSource: maskmid
                }

                MouseArea
                {
                    anchors.fill: buttonmid
                    onClicked:
                    {
                        buttonmid.clicked();//引用该自定义元素时，可以在使用onclick事件。
                        console.log("mid.png")
                    }

                }
            }

//            Button{
//                 x:rootWidth*0.0425
//                 y:rootWidth*0.04
//                 //text: "A button"
//                 style: ButtonStyle {
//                      background:Rectangle  //中间小圆形的实现
//                      {
//                          //y:65
//                          //z:5

//                          anchors.centerIn: parent

//                          implicitWidth: rootWidth*0.0375

//                          implicitHeight: rootHeight/15

//                          radius: rootHeight/30

//                          color: "white"

//                          Image {

//                              //z:6

//                              id: multitaskimage

//                              anchors.fill: parent
//                              smooth: true
//                              visible: false
//                              source: "qrc:/Resources/stop.png"
//                              sourceSize: Qt.size(parent.size, parent.size)
//                              antialiasing: true
//                          }

//                          Rectangle {
//                                      id: _mask
//                                      color: "black"
//                                      anchors.fill: parent
//                                      radius: width/2
//                                      visible: false
//                                      antialiasing: true
//                                      smooth: true
//                                  }


//                          OpacityMask {
//                                      id:mask_image
//                                      anchors.fill: multitaskimage
//                                      source: multitaskimage
//                                      maskSource: _mask
//                                      visible: true
//                                      antialiasing: true
//                                  }

//                      }
//                  }

//                  onClicked:

//                  {
//                       console.log("mid.png")
//                      //pieimage.source = "/pie/keyboard-bg.png"

//                  }
//            }

    }


    Grid {

        id: scanGrid
        //x: sacnRoot.width*0.85
        x:rootWidth*0.035
        y: sacnRoot.height*0.7
        anchors.left: scanViewer.right
        anchors.leftMargin: rootWidth*0.028125
        rows: 2
        columns: 2
        //anchors.centerIn: parent
        spacing: 10
        opacity:1.0
        Item{
            width: rootWidth*0.05
            height: rootHeight*0.05

            Button {
                    //text: "开始"
                    Text {
                        text: qsTr("开始")
						font.family: "微软雅黑";
						font.pixelSize:16
                        color :"white"
                        anchors.horizontalCenter:parent.horizontalCenter
                        anchors.verticalCenter:parent.verticalCenter
                    }

                    anchors.fill: parent
                    //iconSource: "qrc:/Resources/scanButton.png"
                    background:
                    Image {
                        anchors.fill: parent
                        source: "qrc:/Resources/scanButton.png"
                    }
                    onClicked: {
                        scanViewer.visible=true
                        //skey_event.testJson()
                        ret=mapScanControl.startScan()
                        if(ret)
                        {
                            startScan=true
                        }
                        //mapImage.source="file:"+"test.png"
                        //var imagePath="file:"+"test.png"
                        //scanpainter.addNewPicture("test.png")
                    }
                }
        }

        Item{
            width: rootWidth*0.05
            height: rootHeight*0.05
            Button {

                    Text {
                        text: qsTr("暂停")
						font.family: "微软雅黑";
						font.pixelSize:16
                        color :"white"
                        anchors.horizontalCenter:parent.horizontalCenter
                        anchors.verticalCenter:parent.verticalCenter
                    }
                    anchors.fill: parent
                    background:
                    Image {
                        anchors.fill: parent
                        source: "qrc:/Resources/scanButton.png"
                    }
                    onClicked: {

                        ret=mapScanControl.stopScan()
                        if(ret)
                        {
                            startScan=false
                        }
                    }
                }
        }


        Item{
            width: rootWidth*0.05
            height: rootHeight*0.05

            Button {
                    Text {
                        text: qsTr("恢复")
						font.family: "微软雅黑";
						font.pixelSize:16
                        color :"white"
                        anchors.horizontalCenter:parent.horizontalCenter
                        anchors.verticalCenter:parent.verticalCenter
                    }
                    anchors.fill: parent
                    background:
                    Image {
                        anchors.fill: parent
                        source: "qrc:/Resources/scanButton.png"
                    }
                    onClicked: {
                        ret=mapScanControl.resumeScan()
                        if(ret)
                        {
                            startScan=true
                        }
                    }
                }
        }


        Item{
            width: rootWidth*0.05
            height: rootHeight*0.05

            Button {
                    Text {
                        text: qsTr("取消")
						font.family: "微软雅黑";
						font.pixelSize:16
                        color :"white"
                        anchors.horizontalCenter:parent.horizontalCenter
                        anchors.verticalCenter:parent.verticalCenter
                    }
                    anchors.fill: parent
                    background:
                    Image {
                        anchors.fill: parent
                        source: "qrc:/Resources/scanButton.png"
                    }
                    onClicked: {
                        scanViewer.visible=false
                        ret=mapScanControl.cancleScan()
                        if(ret)
                        {
                            startScan=false
                        }
                    }
                }
        }


    }

    Item{
        x:rootWidth*0.035
        y: rootHeight/9*7
        anchors.left: scanViewer.right
        anchors.leftMargin: rootWidth*0.028125
        width: rootWidth*0.10625
        height: rootHeight*0.05
        Button {
                Text {
                    text: qsTr("结束并保存")
					font.family: "微软雅黑";
					font.pixelSize:16
                    color :"white"
                    anchors.horizontalCenter:parent.horizontalCenter
                    anchors.verticalCenter:parent.verticalCenter
                }
                anchors.fill: parent
                background:
                Image {
                    anchors.fill: parent
                    source: "qrc:/Resources/scanButton2.png"
                }
                onClicked: {
                    ret=mapScanControl.saveScan()
                    if(ret)
                    {
                        startScan=false
                    }
                }
            }
    }

    /* 4.移动控制机器人 */
    focus: true;
    Keys.forwardTo: moveRobot

    Rectangle{
        id: moveRobot
        //width:  mapViewer.width; height: mapViewer.height
        color: "#F0FFFF"
        QmlKey {
            id: skey_event
        }

        /* focus: true; Keys.enabled: true; Keys.onEscapePressed: Qt.quit();	Keys.forwardTo: [moveText, control]; */
        Keys.onPressed: {
            console.log("move ...")
            //if(startScan)
            //{
                switch (event.key){
                case Qt.Key_Left:
                    skey_event.moveRobot(1);
                    break;
                case Qt.Key_Right:
                    skey_event.moveRobot(2);
                    break;
                case Qt.Key_Up:
                    skey_event.moveRobot(3);
                    break;
                case Qt.Key_Down:
                    skey_event.moveRobot(4);
                    break;
                case Qt.Key_1:
                    skey_event.testJson(0)
                    break;
				case Qt.Key_2:
                    skey_event.testJson(1)
                    break;
                default:
                    return;
                }
                skey_event.sendSpeedJson()  // 发命令
                event.accepted = true;
                //console.log("linearspeed =  ", skey_event.getLinearSpeed(), ", angularspeed = " + skey_event.getAngularSpeed())
//            }
//            else
//            {
//                 console.log("stop ...")
//            }

        }
    }


}

