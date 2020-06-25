import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Rectangle{
    id : navigationrect
    x: 0 ; y:0;
    //width: 400 ;
    height: 64;
    color: "#052641"
    border.color: "#00498C"

    function setDefeat()
    {
        p1.noclicked();
        p2.noclicked();
        p3.noclicked();
        p4.noclicked();
    }

    function commomSetttingFunc(id, index)
    {
        navigationrect.index = index
        setDefeat();
        id.onSelected();
        buttonclicked(index);
        buttonclickedStr(id.mtextstr);
    }

    property int pbwidth: navigationrect.width / 4
    property int pbheight: height-6
    property int index: 0

    signal buttonclicked(int index);
    signal buttonclickedStr(string textstr);

    BaseButton{
        id:p1;
        mtextstr: "加车设置"
        MouseArea
        {
            anchors.fill: parent;
            onClicked: {
                commomSetttingFunc(p1, 0);
            }
        }
    }
    BaseButton{
        id:p2
        x: pbwidth
        mtextstr: "付款信息"
        MouseArea
        {
            anchors.fill: parent;
            onClicked: {
                commomSetttingFunc(p2, 1);
            }
        }
    }
    BaseButton{
        id:p3
        x: pbwidth*2
        mtextstr: "代理池"
        MouseArea
        {
            anchors.fill: parent;
            onClicked: {
                commomSetttingFunc(p3, 2);
            }
        }
    }

    BaseButton{
        id:p4
        x: pbwidth*3
        mtextstr: "商品监控"
        MouseArea
        {
            anchors.fill: parent;
            onClicked: {
                commomSetttingFunc(p4, 3);
            }
        }
    }

    Rectangle
    {
        id : bottomrect
        color: "yellow";
        width: pbwidth-1; height: 2
        y:pbheight+2;
        x:index*pbwidth
        Behavior on x{
            PropertyAnimation{duration: navigationrect.width}
        }
    }
}
