import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Extras 1.4
import QtQml.Models 2.12
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 2.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.1
//import QtQuick.Controls.Styles 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0


Item {
    id: productSetting
    anchors.fill: parent


    signal currentMapName(string fileName)
    property string currentLocalMap: ""
    property bool qmlProgressVisible: false

    function clearListModel()
    {
        listModel.clear();
    }

    function setListModel(fileName, fileType)
    {
        console.log("listModel.count = " + listModel.count + ", fileName" + fileName + ", fileType" + fileType);
        listModel.insert(listModel.count, {"fileName": fileName, "fileType": fileType});
    }

	Rectangle {
        id: listViewExL2
        visible: true
        width: parent.width
        height: parent.height

        anchors.bottom: parent.bottom
        anchors.bottomMargin: -parent.height / 2
//        anchors.right: parent.right
//        anchors.rightMargin: parent.width / 3


        ListViewEx {
            id: listView
            model: listModel
            delegate: listDelegate
            //rotation: -90

            onLoad: {
                console.log("on load")
                //listModel.insert(0, {"name": (Math.floor(Math.random() * 100)).toString(), "number": (Math.floor(Math.random() * 100)).toString()})
            }

            onLoadMore: {
                console.log("on load more")
                //listModel.insert(listModel.count, {"name": (Math.floor(Math.random() * 100)).toString(), "number": (Math.floor(Math.random() * 100)).toString()})
            }
        }

        Component{
            id: listDelegate
            BasicRadioButton{
                width: 80
                height: 80
                //rotation:90
                checked: true
                text: model.fileName
                textColor: "purple"
                font.pixelSize: 16
                radioTheme: "#FFFF00"
            }
        }


        ListModel {
            id: listModel
        }
    }
}

