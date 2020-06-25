import QtQuick 2.0
import FileIO 1.0

Rectangle{
    id: page3Content
    color: "#6E6E6E"
    property int row1Interval: 128
    property int row2Interval: 72
    property int row3Interval: 48
    property int row4Interval: 4

    FileIO {
        id: myFile
        source: "IP.txt"
        onError: console.log(msg)
    }

//    ListModel {  //使用ListModel，并加入测试数据
//        id: myModel3
//        ListElement {
//            recordId: 1
//            s5Proxy: 1
//            speedMeasure: "test"
//            state: "test"
//        }
//    }

    Rectangle{
        id: tableRec3
        width: parent.width
        height: 7*parent.height/10 + 32

        DataShowTable {
            id: table2
            anchors.fill: parent
            width: parent.width
            height: parent.height

            property var bankPaySearchTableArray: [["序号","s5代理","测速","状态"],
                                                       [64,256,256,256],
                                                       ["recordId","s5Proxy","speedMeasure","state"]]

            Component.onCompleted: {
               table2.createTable(bankPaySearchTableArray);    //创建表
            }
        }

        DropArea {
            anchors.fill: parent;
            onEntered: {
                if (drag.urls.length !== 1) { // 过滤事件，只能拖拽一个项目
                    drag.accepted = false
                    return false;
                }
            }

            onDropped: {
                console.log(drop.urls.length);
                for(var i = 0; i < drop.urls.length; i++){
                    var fileName = drop.urls[i].substring(8,drop.urls[i].length);
                    myFile.source = fileName;
                    var fileContent = myFile.read();
                    for(var lineId = 0; lineId < fileContent.length; lineId++){
                        if(fileContent[lineId].length > 9) {
                            console.log("line["+lineId+"]: "+fileContent[lineId]);
                            var lineData = fileContent[lineId].split(":");
                            var rowData = new Array();
                            rowData[0] = lineId;
                            rowData[1] = lineData[0];
                            rowData[2] = " ";
                            rowData[3] = " ";

                            //var rowData = ["1", "2", "test", "test"];
                            table2.insertRowData(rowData);
                        }
                    }
                }
                //table2.model = myModel3;
            }
        }
    }


    // ------------------------------------------------------ 底部功能区 -----------------------------------------------------------

    Row {
        id: row1
        spacing: page3Content.width - 2 * 124

        anchors.bottom: page3Content.bottom
        anchors.bottomMargin: row1Interval
        anchors.left: page3Content.left
        anchors.leftMargin: 8

        BasicButton{
            id: clearTableButton
            width: 124
            height: 36

            text: "清空列表"
            textColor: "white"
            backgroundTheme: "#1874CD"

            onClicked: {
                console.log("pressed basic button");
            }
        }
    }

    Row {
        id: row2
        spacing: page3Content.width - 2 * 124

        anchors.bottom: page3Content.bottom
        anchors.bottomMargin: row2Interval
        anchors.left: page3Content.left
        anchors.leftMargin: 8

        BasicButton {
           id: startQueryButton
           width: 124
           height: 36

           text: "检查列表"
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

        anchors.bottom: page3Content.bottom
        anchors.bottomMargin: row3Interval
        anchors.left: page3Content.left
        anchors.leftMargin: 0

        Canvas {
            id: root
            width: page3Content.width; height: 4
            onPaint: {
                var ctx = getContext("2d")
                var gradient = ctx.createLinearGradient(0,0,page3Content.width,page3Content.height - row3Interval - 2)
                gradient.addColorStop(0, "blue")
                gradient.addColorStop(0.5, "lightsteelblue")
                ctx.fillStyle = gradient
                ctx.fillRect(0, 0, page3Content.width, page3Content.height - row3Interval - 2)
            }
        }
    }

    Row {
        id: row4
        //spacing: page3Content.width / 20 - 4
        spacing: 32

        anchors.bottom: page3Content.bottom
        anchors.bottomMargin: row4Interval
        anchors.left: page3Content.left
        anchors.leftMargin: -16

        Rectangle{
            id: userLoginState
            color: "#6E6E6E"
            width: 2*page3Content.width / 10
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
            width: page3Content.width / 10
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
            width: page3Content.width / 10
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
            width: page3Content.width / 10
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
            width: 4*page3Content.width / 10
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
