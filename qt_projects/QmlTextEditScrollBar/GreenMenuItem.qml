import QtQuick 2.5
import QtQuick.Controls 2.5

MenuItem {
    id: menuItem
    implicitWidth: 30
    implicitHeight: 48
    font: Qt.font({
                  family: "微软雅黑",
                  pointSize: 12})
				  //,weight: Font.Bold                  })
    contentItem: Text {
         //leftPadding: menuItem.indicator.width
         //rightPadding: menuItem.arrow.width
         text: menuItem.text
         font: menuItem.font
         opacity: enabled ? 1.0 : 0.3
         color: "#ffffff"
         horizontalAlignment: Text.AlignHCenter
         verticalAlignment: Text.AlignVCenter
         elide: Text.ElideRight
     }

    background: Rectangle {
        implicitWidth: 30
        implicitHeight: 48
        opacity: enabled ? 1 : 0.3
        //color: menuItem.highlighted ? "#8ACE00" : "transparent"
		color: menuItem.highlighted ? "#797a7b" : "transparent"
		
        //上边的横线
        Rectangle {
            //color: "#808080"
			color: "#ffffff"
            height: 1
            width: parent.width
            anchors.top: parent.top
            opacity: 0.5
        }
    }
}
