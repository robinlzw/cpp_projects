import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 832
    height: 768
    title: qsTr("SNKRS")
    //color: "#87CEFA"
    color: "#6E6E6E"

    MTabBar {
        id: tabBarViewer
        anchors.top: root.top
        anchors.topMargin: 2
        anchors.left: root.left
        anchors.leftMargin: 0
        width: parent.width
        height: 64
    }

    Rectangle{
        id: tableRec1
        anchors.top: tabBarViewer.bottom
        anchors.topMargin: 2
        anchors.left: root.left
        anchors.leftMargin: 0
        width: parent.width
        height: 7*parent.height/9
        visible: (tabBarViewer.index == 0) ? true : false

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
//    Button {
//       id: clearTableButton
//       width: 128
//       height: 36

//       anchors.bottom: parent.bottom
//       anchors.bottomMargin: 2
//       anchors.left: parent.left
//       anchors.leftMargin: 2

//       contentItem: Text {
//           text: "清空列表"
//           font.family: "microsoft yahei"
//           font.pixelSize: 23
//           opacity: 1.0
//           color: "#FFFFFF"
//           horizontalAlignment: Text.AlignHCenter
//           verticalAlignment: Text.AlignVCenter
//           elide: Text.ElideRight
//       }

//       background: Image{
//           id: clearTableImage
//           anchors.horizontalCenter:parent.horizontalCenter
//           anchors.verticalCenter:parent.verticalCenter
//           anchors.fill: parent
//           source:"qrc:/Resources/notClick.png"
//           opacity: 0.33
//       }
//       onClicked: {
//           //openTable();
//       }
//   }

    BasicButton{
        id: clearTableButton
        width: 128
        height: 36

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2


        text: "清空列表"
        textColor: "white"
        backgroundTheme: "#1874CD"
    }

    Button {
       id: startLoginButton
       width: 128
       height: 36

       anchors.bottom: parent.bottom
       anchors.bottomMargin: 2
       anchors.left: clearTableButton.right
       anchors.leftMargin: 32

       contentItem: Text {
           text: "开始登录"
           font.family: "microsoft yahei"
           font.pixelSize: 23
           opacity: 1.0
           color: "#FFFFFF"
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideRight
       }

       background: Image{
           id: startLoginImage
           anchors.horizontalCenter:parent.horizontalCenter
           anchors.verticalCenter:parent.verticalCenter
           anchors.fill: parent
           source:"qrc:/Resources/notClick.png"
           opacity: 0.33
       }
       onClicked: {
           //openTable();
       }
   }

    Button {
       id: startDrawButton
       width: 128
       height: 36

       anchors.bottom: parent.bottom
       anchors.bottomMargin: 2
       anchors.left: startLoginButton.right
       anchors.leftMargin: 32

       contentItem: Text {
           text: "开始加车"
           font.family: "microsoft yahei"
           font.pixelSize: 23
           opacity: 1.0
           color: "#FFFFFF"
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideRight
       }

       background: Image{
           id: startDrawImage
           anchors.horizontalCenter:parent.horizontalCenter
           anchors.verticalCenter:parent.verticalCenter
           anchors.fill: parent
           source:"qrc:/Resources/notClick.png"
           opacity: 0.33
       }
       onClicked: {
           //openTable();
       }
   }

    Button {
       id: startQueryButton
       width: 128
       height: 36

       anchors.bottom: parent.bottom
       anchors.bottomMargin: 2
       anchors.left: startDrawButton.right
       anchors.leftMargin: 32

       contentItem: Text {
           text: "开始查询"
           font.family: "microsoft yahei"
           font.pixelSize: 23
           opacity: 1.0
           color: "#FFFFFF"
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideRight
       }

       background: Image{
           id: startQueryImage
           anchors.horizontalCenter:parent.horizontalCenter
           anchors.verticalCenter:parent.verticalCenter
           anchors.fill: parent
           source:"qrc:/Resources/notClick.png"
           opacity: 0.33
       }
       onClicked: {
           //openTable();
       }
   }

    BasicSpinBox{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2
                anchors.right: parent.right
                anchors.rightMargin: 2
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
