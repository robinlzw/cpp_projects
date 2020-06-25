import QtQuick 2.0
Rectangle{
    id: page1Content
    color: "#6E6E6E"
    property int row1Interval: 128
    property int row2Interval: 80
    property int row3Interval: 40
    property int row4Interval: 2


    Rectangle{
        id: tableRec1
        width: parent.width
        height: 7*parent.height/10 + 32
        //visible: (tabBarViewer.index == 0) ? true : false

        property var dataRecordJson

        DataShowTable {
            id: table1
            anchors.fill: parent
            width: parent.width
            height: parent.height
        }
    }

    //    TextEdit{
    //        id: textEdit
    //        font.pixelSize: 24
    //        anchors.top: root.top
    //        anchors.topMargin: 64
    //        anchors.left: root.left
    //        anchors.leftMargin: 0
    //        height: 32
    //        width: 64
    //        DropArea{
    //            anchors.fill: parent
    //            onDropped: {
    //                if (drop.hasUrls){
    //                    console.debug("拖放了文件: " + drop.urls.length);
    //                    for(var i = 0; i < drop.urls.length; i++){
    //                        console.debug("文件: " + drop.urls[i]);
    //                        textEdit.append("文件: " + drop.urls[i])
    //                    }
    //                }
    //                else if (drop.hasText){
    //                    console.debug("拖放了本文: " + drop.text.length);
    //                    console.debug("文本: " + drop.text);
    //                    textEdit.append("文本: " + drop.text)
    //                }
    //            }
    //        }
    //    }

    Row {
        id: row1
        spacing: (page1Content.width - 4 * 124 - 8) / 3

        anchors.bottom: page1Content.bottom
        anchors.bottomMargin: row1Interval
        anchors.left: page1Content.left
        anchors.leftMargin: 8

        BasicButton{
            id: clearTableButton
            width: 124
            height: 36

//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: row1Interval
//            anchors.left: parent.left
//            anchors.leftMargin: 2


            text: "清空列表"
            textColor: "white"
            backgroundTheme: "#1874CD"

            onClicked: {
                console.log("pressed basic button");
            }
        }

        BasicButton {
           id: startLoginButton
           width: 124
           height: 36

//           anchors.bottom: parent.bottom
//           anchors.bottomMargin: row1Interval
//           anchors.left: clearTableButton.right
//           anchors.leftMargin: 32

           text: "开始登录"
           textColor: "white"
           backgroundTheme: "#1874CD"

           onClicked: {
               console.log("pressed basic button");
           }
        }

        BasicButton {
           id: startDrawButton
           width: 124
           height: 36

//           anchors.bottom: parent.bottom
//           anchors.bottomMargin: row1Interval
//           anchors.left: startLoginButton.right
//           anchors.leftMargin: 32

           text: "开始加车"
           textColor: "white"
           backgroundTheme: "#1874CD"

           onClicked: {
               console.log("pressed basic button");
           }
        }

        BasicButton {
           id: startQueryButton
           width: 124
           height: 36

//           anchors.bottom: parent.bottom
//           anchors.bottomMargin: row1Interval
//           anchors.left: startDrawButton.right
//           anchors.leftMargin: 32

           text: "开始查询"
           textColor: "white"
           backgroundTheme: "#1874CD"

           onClicked: {
               console.log("pressed basic button");
           }
        }

    }

    Row {
        id: row2
        spacing: page1Content.width / 4 - 4

        anchors.bottom: page1Content.bottom
        anchors.bottomMargin: row2Interval
        anchors.left: page1Content.left
        anchors.leftMargin: -4

        Rectangle{
            id: threadChooseBox
            color: "#6E6E6E"
            width: page1Content.width / 4
            height: 36

            Text{
                anchors.left: parent.left
                //anchors.leftMargin: -2

                width: 96
                text: "线程数:"
                font.pixelSize: 21
                font.family: "microsoft yahei"
                color: "white"
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }

            BasicSpinBox{
                anchors.right: parent.right

                from: 0
                to: 15
                value: 2
                stepSize: 1
                editable: false
                borderVisible: false
                borderColor: "darkCyan"
                textColor: "white"
                btnNormalColor: "darkCyan"
                bgNormalColor: "skyblue"
                bgFocusColor: "blue"
                indicatorNormalColor: "white"
                indicatorDisableColor: "gray"
            }
        }

        Rectangle{
            id: maxPurchaseNumPerAccount
            color: "#6E6E6E"
            width: page1Content.width / 2
            height: 36

            Text{
                anchors.left: parent.left

                width: 256
                text: "单个账号最大购买数量:"
                font.pixelSize: 21
                font.family: "microsoft yahei"
                color: "white"
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }

            BasicSpinBox{
                anchors.right: parent.right

                from: 0
                to: 15
                value: 2
                stepSize: 1
                editable: false
                borderVisible: false
                borderColor: "darkCyan"
                textColor: "white"
                btnNormalColor: "darkCyan"
                bgNormalColor: "skyblue"
                bgFocusColor: "blue"
                indicatorNormalColor: "white"
                indicatorDisableColor: "gray"
            }
        }

    }
}
