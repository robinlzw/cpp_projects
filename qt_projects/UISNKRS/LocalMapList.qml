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
    id:mapListPage
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
        id: listViewExL
        visible: true       
//        width: parent.height - 128 - 32
//        height: parent.height
        width: 0
        height: parent.height

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 2
//        width: 32
//        height: 380
        //color: "#6E6E6E"
        color: "green"

        ListViewEx {
            id: listView
//            width: parent.width
//            height: 32
//            width: 320
//            height: 1080

            model: listModel
            delegate: listDelegate
            rotation: -90

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
//            Rectangle{
                BasicRadioButton{
//                    width: 360
//                    height: 124
                    width: 80
                    height: 80

                    rotation:90
                    checked: true
                    text: model.fileName
                    //text: "40"
                    textColor: "purple"
                    radioTheme: "red"
                }
           // }
        }


        ListModel {
            id: listModel
        }
    }
}

