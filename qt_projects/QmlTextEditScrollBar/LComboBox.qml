import QtQuick 2.12
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0

ComboBox {
    id:dataList
    property alias _backgroundColor: backRect.color
    anchors.centerIn: parent
    width: 240 * m_ratio
    height: /*80 * m_ratio*/parent.height

    background: Rectangle {
        id:backRect
        implicitWidth: parent.width
        implicitHeight: parent.height
        color: color_background
        border.color: "#979797"
        border.width: /*dataList.visualFocus ? 2 :*/ 0
        radius: radius_real
    }
    delegate: ItemDelegate {
        id:itemDlgt
        width: dataList.width
        contentItem: Text {//下拉字体
            text: modelData
            color: color_vice
            width: parent.width
            font.family: fontFamily
            font.pixelSize: 36 * m_ratioFont
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            anchors.left: parent.left
            anchors.leftMargin: 10 * m_ratio
        }
        background: Rectangle {
            radius:radius_real
            width: parent.width - 6 * m_ratio
            height: parent.height - 6 * m_ratio
            color:itemDlgt.hovered ? color_background : color_white
            anchors.centerIn: parent
        }
        highlighted: dataList.highlightedIndex === index
    }
    contentItem: Text {//显示字体
        text: dataList.displayText
        width: parent.width
        font.family: fontFamily
        font.pixelSize: 36 * m_ratioFont
        color: color_Rosered
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        anchors.left: parent.left
        anchors.leftMargin: 10 * m_ratio

    }
    popup: Popup {
        y: dataList.height/* - 1*/
        width: dataList.width
        implicitHeight: contentItem.implicitHeight
        padding: 0 * m_ratio
        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: dataList.popup.visible ? dataList.delegateModel : null
            currentIndex: dataList.highlightedIndex
            ScrollIndicator.vertical: ScrollIndicator { }
            interactive:false
            anchors.centerIn: parent
        }

        background: Rectangle {
            id:backpop
            width: dataList.width
            height: parent.implicitHeight
            border.color: "#FE4AEC"
            border.width: 1.0 * m_ratio
            radius: radius_real
            color: color_white
            Rectangle{
                id:backRect2
                width: parent.width
                height: parent.height
                radius: radius_real
                color: color_white
                anchors.centerIn: parent
            }
            DropShadow {
                anchors.fill: backRect2
                radius: 4
                samples: 9
                color: "#FE4AEC"
                spread: 0.5
                source: backRect2
                cached: true
            }
        }

    }
    indicator: Canvas {
        id: canvas
        x: dataList.width - width - dataList.rightPadding
        y: dataList.topPadding + (dataList.availableHeight - height) / 2
        width: 24 * m_ratio
        height: 12 * m_ratio
        contextType: "2d"
        opacity: 0.4
        Connections {
            target: dataList
            onPressedChanged: canvas.requestPaint()
        }
        onPaint: {
            context.save()
            context.reset()
            context.lineWidth = 2 * m_ratio
            context.beginPath()
            context.moveTo(0, 0)
            context.lineTo(width / 2, height)
            context.lineTo(width, 0)
            context.fillStyle = Qt.rgba(200, 155, 255,0)/*dataList.pressed ? color_vice : */
            context.stroke()
            context.restore()
        }
    }

}//ComboBox
