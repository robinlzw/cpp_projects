import QtQuick 2.0
Rectangle{
    id: page2Content
    color: "#6E6E6E"
    property int row1Interval: 128
    property int row2Interval: 72
    property int row3Interval: 48
    property int row4Interval: 4


    Rectangle{
        id: tableRec2
        width: parent.width
        height: 7*parent.height/10 + 32

        DataShowTable {
            id: table2
            anchors.fill: parent
            width: parent.width
            height: parent.height

            property var bankPaySearchTableArray: [["序号","账号","商品信息","支付链接"],
                                                       [64,256,256,256],
                                                       ["recordId","accountId","productInfo","payLink"]]

            Component.onCompleted: {
               table2.createTable(bankPaySearchTableArray);    //创建表
            }
        }
    }


    Row {
       id: row3
       spacing: 0

       anchors.bottom: page2Content.bottom
       anchors.bottomMargin: row3Interval
       anchors.left: page2Content.left
       anchors.leftMargin: 0

       Canvas {
           id: root
           width: page2Content.width; height: 4
           onPaint: {
               var ctx = getContext("2d")
               var gradient = ctx.createLinearGradient(0,0,page2Content.width,page2Content.height - row3Interval - 2)
               gradient.addColorStop(0, "blue")
               gradient.addColorStop(0.5, "lightsteelblue")
               ctx.fillStyle = gradient
               ctx.fillRect(0, 0, page2Content.width, page2Content.height - row3Interval - 2)
           }
       }
    }

    Row {
       id: row4
       //spacing: page2Content.width / 20 - 4
       spacing: 32

       anchors.bottom: page2Content.bottom
       anchors.bottomMargin: row4Interval
       anchors.left: page2Content.left
       anchors.leftMargin: -16

       Rectangle{
           id: userLoginState
           color: "#6E6E6E"
           width: 2*page2Content.width / 10
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
           width: page2Content.width / 10
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
           width: page2Content.width / 10
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
           width: page2Content.width / 10
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
           width: 4*page2Content.width / 10
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
