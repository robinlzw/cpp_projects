import QtQuick 2.5
import QtQuick.Controls 2.5

MenuBarItem {
	id: menuBarItem
	height: 48
	width: 150
	font: Qt.font({
	family: "微软雅黑",
	pointSize: 12}) 
                   //weight: Font.Bold                   })

     contentItem: Text {
         text: menuBarItem.text
         font: menuBarItem.font
         opacity: enabled ? 1.0 : 0.3
         color:  "#ffffff"
         horizontalAlignment: Text.AlignHCenter
         verticalAlignment: Text.AlignVCenter
         elide: Text.ElideRight
     }

     background: Rectangle {
         implicitWidth: 40
         implicitHeight: 40
         opacity: enabled ? 1 : 0.3
         //color: menuBarItem.highlighted ? "#8ACE00" : "transparent"
		 color: menuBarItem.highlighted ? "#797a7b" : "transparent"

         //左边灰白色的竖线
         Rectangle {
             color: "#808080"
             height: parent.height
             width: 1
             anchors.left: parent.left
             opacity: 0.5
         }

         //右边的竖线
         Rectangle {
             color: "#696969"
             height: parent.height
             width: 1
             anchors.right: parent.right
             opacity: 0.5
         }
     }
}
