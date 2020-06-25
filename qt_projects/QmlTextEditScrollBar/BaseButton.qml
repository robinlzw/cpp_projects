import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Rectangle{
    id : navigrect;
    property string mtextstr: "..."
    function noclicked()
    {
        p1text.color = "#00CCFF";
        p1text.font.bold = false;
        navigrect.color = "#00498C";
        //navigrect.color
    }
    function onSelected()
    {
        p1text.color = "white";
        p1text.font.bold = true;
        navigrect.color = "#1B96D1";

    }

    x:1;
    anchors.verticalCenter : parent.verticalCenter
    width: parent.pbwidth;height: parent.pbheight
    radius: 8
    color: "#00498C"
    border.color: "#06E4F3"
    Text {
        id : p1text
        anchors.centerIn : parent
        color: "#00CCFF"
        text: mtextstr

    }
    Behavior on color{
            PropertyAnimation{duration: 1000}
        }

    // color:curindex==3?GColor.浅绿色["500"]:GColor.浅蓝色["500"]
}
