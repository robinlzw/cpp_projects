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
import LocalMap 1.0


Item {
    id:mapListPage
    anchors.fill: parent
    width: parent.width
    height: parent.height

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


    /* 进度条 */
//    Rectangle {
//        width: mapListPage.width
//        visible: qmlProgressVisible
//        anchors.top: mapListPage.top
//        anchors.topMargin: -8
//        anchors.right: mapListPage.right
//        anchors.rightMargin: 0

//        QmlProgress {
//            id: qmlProgress

//            isRun: true
//            backWidth: mapListPage.width - 4
//        }
//    }

	Rectangle {
        id: listViewExL
        visible: true
        width: parent.width
        height: parent.height
		
        Image{
            id: spaceBoundingBoxImage
            anchors.horizontalCenter:parent.horizontalCenter
            anchors.verticalCenter:parent.verticalCenter
            anchors.fill: parent
            width: parent.width
            height: parent.height
            source:"qrc:/Resources/backBoundingBox.png"
			opacity: 0.66
        }

        ListViewEx {
            id: listView
            width: parent.width
            height: parent.height
            model: listModel
            delegate: listDelegate

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
            Rectangle{
                id: listItem
                width: parent.width
                height: 48
                color: "#797a7b"
                Text {
                    id: text
                    font.family: "microsoft yahei"
                    font.pixelSize: 12
                    //font.pointSize: 12
                    height: parent.height
                    width: parent.width - delBtn.width - operationButton.width
                    //text: "Name: " + model.name + "\n" + "Number: " + model.number
                    text: model.fileName
                    //color: "green"
                    color: "white"
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    verticalAlignment: Text.AlignVCenter

//                    PropertyAnimation on x {
//                        id:animation
//                        running: animationRunning
//                        from: listItem.width
//                        to:(0-text.text.length*text.font.pixelSize)+300;
//                        //duration: animationDuration/3
//                        duration: 15*1000
//                        loops:1
//                        onStopped:{
//                            animation.start()
//                        }
//                    }

                    MouseArea{
                        property point clickPos: Qt.point(0, 0)

                        anchors.fill: parent
                        onPressed: {
                            clickPos  = Qt.point(mouse.x,mouse.y);
                            mapListPage.currentMapName(model.fileName)
                            mapListPage.currentLocalMap = model.fileName
                            localmap.setCurrentLocalMap(model.fileName)
                        }
                        onReleased: {
                           var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)

                           if ((delta.x < 0) && (delBtnShowAnim.running === false) && (delBtn.width === 0))
                               delBtnShowAnim.start();
                           else if (delBtnHideAnim.running === false && (delBtn.width > 0))
                               delBtnHideAnim.start();

                        }
                   }
                }

                Image {
                    id: operationButton
                    sourceSize.width: 32
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 16
                    verticalAlignment: Image.AlignVCenter

                    visible: true
                    source: model.fileType == "remoteFile" ? "qrc:/Resources/download.png" : "qrc:/Resources/upload.png";

                    MouseArea{
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        onClicked: {
                            //if(model.fileType == "remoteFile") {
                                //mapListPage.qmlProgressVisible = true;
                                //qmlProgress.onStart();
                            //}
                            LocalMapWorkThread.setCurrentLocalMap(mapListPage.currentLocalMap);
                            LocalMapWorkThread.start(model.fileName, model.fileType);
                            //localmap.mapOperaton(model.fileName, model.fileType);
                        }
                    }
                }

                Rectangle{
                   color: "#AAAAAA"
                   height: 1
                   width: parent.width
                   anchors.bottom: parent.bottom
                }
                Rectangle{
                   id: delBtn
                   height: parent.height
                   width: 0
                   color: "#EE4040"
                   visible: false
                   anchors.right: parent.right
                   Text {
                       font.family: "microsoft yahei"
                       font.pointSize: 12
                       anchors.centerIn: parent
                       text: qsTr("删除")
                       color: "#797a7b"
                   }
                   MouseArea{
                       anchors.fill: parent
                       onClicked: {
                           //listView.model.remove(index);
                       }
                   }
                }
                PropertyAnimation{
                   id: delBtnShowAnim
                   target: delBtn
                   property: "width"
                   duration: 100
                   from: 0
                   to: 60
                }
                PropertyAnimation{
                   id: delBtnHideAnim
                   target: delBtn
                   property: "width"
                   duration: 100
                   from: 60
                   to: 0
                }
            }
        }


        ListModel {
            id: listModel
        }
    }
}

