import QtQuick.Controls 2.12
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id: page4Content
    color: "#6E6E6E"
    property int row1Interval: parent.height/4  - 64
    property int row2Interval: row1Interval - 48
    property int row3Interval: 48
    property int row4Interval: 4


    Rectangle{
        id: tableRec4
        width: parent.width
        height: 3*parent.height/4

        DataShowTable {
            id: table2
            anchors.fill: parent
            width: parent.width
            height: parent.height

            property var bankPaySearchTableArray: [["序号","监控信息","监控状态"],
                                                       [64,256,256],
                                                       ["recordId","sellInformation","productInfo"]]

            Component.onCompleted: {
               table2.createTable(bankPaySearchTableArray);    //创建表
            }
        }
    }


    LocalMapList {
        id: maplist
        visible: false
    }

    ProductSet {
        id: productCategory
        visible: false
    }

//    Window {
//        id: window
//        visible: false
//        width: 360
//        height: 360
//        TodoList{
//           Layout.fillWidth: true;
//           anchors.horizontalCenter: parent.horizontalCenter
//           anchors.verticalCenter: parent.verticalCenter
//        }
//    }
    Popup
    {
        id:myPopup
        width: parent.width
        height: 3*parent.height/4
        x:(root.width-width)/2
        y:(root.height-height)/2 + 256
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        TodoList{
            width: parent.width
            Layout.fillWidth: true;
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }



    // ------------------------------------------------------ 底部功能区 -----------------------------------------------------------

    Row {
        id: row1
        spacing: page4Content.width - 2 * 124

        anchors.bottom: page4Content.bottom
        anchors.bottomMargin: row1Interval
        anchors.left: page4Content.left
        anchors.leftMargin: 8

        BasicButton{
            id: customMonitorByProductId
            width: 124
            height: 36

            //text: "自定义货号监控"
            text: "监控设置"
            textColor: "white"
            backgroundTheme: "#1874CD"

            onClicked: {
                //window.show()
                myPopup.open()
                console.log("pressed basic button");
                maplist.clearListModel();
                var maxNum = page4Content.width / 80 - 1;
                for(var i=35;i<35 + maxNum;i++){
                   //console.log("fileName = " + data[i].fileName + ", and fileType = " + data[i].fileType);                   
                   var test = String(i) + "码";
                   maplist.setListModel(test, 0);
                   var test2 = String(i) + "号";
                   productCategory.setListModel(test2, 0);
                }
            }
        }

//        RadioButton{
//            checked: true
//            text: "A"
//        }
//        RadioButton{
//            text: "B"
//        }
    }

    Row {
        id: row2
        spacing: page4Content.width - 2 * 124

        anchors.bottom: page4Content.bottom
        anchors.bottomMargin: row2Interval
        anchors.left: page4Content.left
        anchors.leftMargin: 8

        BasicButton {
           id: startMonitorButton
           width: 124
           height: 36

           text: "开始监控"
           textColor: "white"
           backgroundTheme: "#1874CD"

           onClicked: {
               console.log("pressed basic button");
           }
        }
    }

    Row {
        id: row3
        spacing: 0

        anchors.bottom: page4Content.bottom
        anchors.bottomMargin: row3Interval
        anchors.left: page4Content.left
        anchors.leftMargin: 0

        Canvas {
            id: root
            width: page4Content.width; height: 4
            onPaint: {
                var ctx = getContext("2d")
                var gradient = ctx.createLinearGradient(0,0,page4Content.width,page4Content.height - row3Interval - 2)
                gradient.addColorStop(0, "blue")
                gradient.addColorStop(0.5, "lightsteelblue")
                ctx.fillStyle = gradient
                ctx.fillRect(0, 0, page4Content.width, page4Content.height - row3Interval - 2)
            }
        }
    }

    Row {
        id: row4
        //spacing: page4Content.width / 20 - 4
        spacing: 32

        anchors.bottom: page4Content.bottom
        anchors.bottomMargin: row4Interval
        anchors.left: page4Content.left
        anchors.leftMargin: -16

        Rectangle{
            id: userLoginState
            color: "#6E6E6E"
            width: 2*page4Content.width / 10
            height: 36

            Text{
                anchors.left: parent.left
                //anchors.leftMargin: -2

                width: 64 + 128
                text: "状态: 没有登录"
                font.pixelSize: 21
                font.family: "microsoft yahei"
                color: "white"
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
        }
        Rectangle{
            id: accountNum
            color: "#6E6E6E"
            width: page4Content.width / 10
            height: 36

            Text{
                anchors.left: parent.left
                //anchors.leftMargin: -2

                width: 64 + 32
                text: "账号数: 0"
                font.pixelSize: 21
                font.family: "microsoft yahei"
                color: "white"
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
        }
        Rectangle{
            id: alreadyInShoppingCart
            color: "#6E6E6E"
            width: page4Content.width / 10
            height: 36

            Text{
                anchors.left: parent.left
                //anchors.leftMargin: -2

                width: 64 + 32
                text: "已加车: 0"
                font.pixelSize: 21
                font.family: "microsoft yahei"
                color: "white"
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
        }
        Rectangle{
            id: alreadyBuy
            color: "#6E6E6E"
            width: page4Content.width / 10
            height: 36

            Text{
                anchors.left: parent.left
                //anchors.leftMargin: -2

                width: 64 + 32
                text: "已购买: 0"
                font.pixelSize: 21
                font.family: "microsoft yahei"
                color: "white"
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
        }
        Rectangle{
            id: proxeyIP
            color: "#6E6E6E"
            width: 4*page4Content.width / 10
            height: 36

            Text{
                anchors.left: parent.left
                //anchors.leftMargin: -2

                width: parent.width
                text: "代理IP: 192.168.102.122"
                font.pixelSize: 21
                font.family: "microsoft yahei"
                color: "white"
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
        }
    }
}
