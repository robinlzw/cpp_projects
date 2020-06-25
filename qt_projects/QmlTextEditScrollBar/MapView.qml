import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.4
import LocalMap 1.0
import LmapEdit 1.0


Rectangle {
    id: mapViewer
    visible: true
    color: "#F0FFFF"
    width: rootWidth*0.925
    height: rootHeight*0.925

    property bool isLoadedEditMap: false

	
    Image{
        anchors.horizontalCenter:mapViewer.horizontalCenter
        anchors.verticalCenter:mapViewer.verticalCenter
        anchors.fill: parent
        source:"qrc:/Resources/mapViewBackGround.png"
    }

    function hideRightSpace() {
        mapFileList.visible = false;        
        tableViewselectedRowBgBox.visible = false;
        navigationPointsTableL.visible = false;
        dirShowButtonBckImage.source = "qrc:/Resources/notClick.png";
        naviTableShowButtonBckImage.source = "qrc:/Resources/notClick.png";
    }

    function openMapList() {
       hideRightSpace();
       mapFileList.visible = true
       localmap.refresh();
       maplist.clearListModel();
       var data = JSON.parse(localmap.text);
       for(var i =0;i<data.length;i++){
           console.log("fileName = " + data[i].fileName + ", and fileType = " + data[i].fileType);
           maplist.setListModel(data[i].fileName, data[i].fileType);
       }
       dirShowButtonBckImage.source = "qrc:/Resources/Clicked.png"
       shrinkButton.shrinkMapItemArea(2)
    }

    function openNaviPointTable() {
        hideRightSpace();
        if(mapViewer.isLoadedEditMap == true) {
            navigationPointsTableL.visible = true;
            var naviPointsJson=painter.getNavigationPointJson();
            navigationPointsTableL.naviPointsJson=naviPointsJson;
            var data = JSON.parse(navigationPointsTableL.naviPointsJson);
            naviPointTableL.clearNaviPointsListModel();
            for(var i =0;i<data.length;i++){
                //console.log("navipointsName = " + data[i].navipointsName + ", and x = " + data[i].x);
                naviPointTableL.setNaviPointsListModel(data[i].navipointsName, String(data[i].x), String(data[i].y));
            }
        }
        naviTableShowButtonBckImage.source = "qrc:/Resources/Clicked.png"
        shrinkButton.shrinkMapItemArea(2)
    }

    Connections {
        target: LocalMapWorkThread    
        onTextChanged: {
            if("downloadRosCurrentMap done" == arg) {
                console.log('20191217: downloadRosCurrentMap done');
                openMapList();
            }
        }
        onUploadMapEvent: {
            console.log('20191225: onUploadEvent');
            uploadDifferentMapTipBox.localMapName = localMapName;
            uploadDifferentMapTipBox.visible = true;
            if(1 == operationType) {
                uploadDifferentMapTipBox.boxMessage = "上传的地图不是机器人当前的地图, 是否要切换机器人当前地图?"
                uploadDifferentMapTipBox.operationType = 1;
            } else if(2 == operationType) {
                uploadDifferentMapTipBox.boxMessage = "上传的地图不是机器人当前的地图, 是否要切换机器人当前地图?"
                uploadDifferentMapTipBox.operationType = 2;
            } else if(3 == operationType) {
                uploadDifferentMapTipBox.boxMessage = "机器人当前的地图不是所编辑的地图, 不能导航, 是否要切换机器人当前地图?"
                uploadDifferentMapTipBox.operationType = 3;
            }
        }
//        onNavigateEvent: {
//        }
        onDownloadMapEvent: {
            console.log('20191225: onDownloadMapEvent');
            uploadDifferentMapTipBox.localMapName = localMapName;
            uploadDifferentMapTipBox.visible = true;
            uploadDifferentMapTipBox.boxMessage = "是否下载此地图?"
            uploadDifferentMapTipBox.operationType = 4;
        }
    }

	LocalMap
    {
        id:localmap
        onTextChanged: {
            if("downloadRosCurrentMap done" == arg) {
                console.log('20191217: downloadRosCurrentMap done');
                openMapList();
            }
        }
        onNavigateEvent: {
            console.log('20191225: onNavigateEvent');
            uploadDifferentMapTipBox.visible = true;
            uploadDifferentMapTipBox.boxMessage = "机器人当前的地图不是所编辑的地图, 不能导航, 是否要切换机器人当前地图?"
            uploadDifferentMapTipBox.operationType = 3;
        }
    }

//    LMessageBox {
//        id: mapOperation
//        boxMessage: "下载地图?"
//        btnYesVisible: false
//        btnNoVisible: true
//        boxButtonRejectLabel: "确认下载"

//        onRejected: {
//            cProgress.onStart();
//        }
//    }

    /* 1.目录展示 */
    LMessageBox {
        id: uploadDifferentMapTipBox       
        boxMessage: ""

        btnYesVisible: true
        btnNoVisible: true
        boxButtonAcceptLabel: "是"
        boxButtonRejectLabel: "否"
        useCircularProgress: true

        property string remoteMapName: ""
        property string localMapName: ""
        property int operationType: 0

        onAccepted: {            
            if(uploadDifferentMapTipBox.operationType == 1) {
                localmap.uploadLocalMapData(uploadDifferentMapTipBox.localMapName);                
                uploadDifferentMapTipBox.circularProgressStart(1);
            } else if(uploadDifferentMapTipBox.operationType == 2) {
                localmap.uploadLocalMapDataAndEditData(uploadDifferentMapTipBox.localMapName);
                uploadDifferentMapTipBox.circularProgressStart(1);
            } else if(uploadDifferentMapTipBox.operationType == 3) {
                uploadDifferentMapTipBox.circularProgressStart(0);
                localmap.afterNavigate();
            } else if(uploadDifferentMapTipBox.operationType == 4) {
                uploadDifferentMapTipBox.circularProgressStart(1);
            }
        }
    }


    Button {
        id: dirShowButton
        //width: 2.5 * mapViewer.width / 16
        width: mapViewer.width*0.33 / 2 - 1
        height: 36

        anchors.right: mapViewer.right
        anchors.rightMargin: mapViewer.width*0.33 - dirShowButton.width
        anchors.top: mapViewer.top
        anchors.topMargin: 4

        contentItem: Text {
            text: "地图列表"
            font.family: "microsoft yahei"
            font.pixelSize: 23
            opacity: 1.0
            color: "#FFFFFF"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight           
        }

        background: Image{
            id: dirShowButtonBckImage
            anchors.horizontalCenter:parent.horizontalCenter
            anchors.verticalCenter:parent.verticalCenter
            anchors.fill: parent
            source:"qrc:/Resources/notClick.png"
        }
        onClicked: {
            openMapList();            
        }
    }


    /* 地图列表 */
    Rectangle
    {
        id: mapFileList
        width: mapViewer.width*0.33
        height: mapItem.height - 16

        anchors.top: mapViewer.top
        anchors.topMargin: 64
        anchors.right: mapViewer.right
        anchors.rightMargin: 0
        visible: false

        LocalMapList
        {
            id: maplist
        }

        Connections {
            target: maplist
            onCurrentMapName:
            {
                var NewMap = "Resources/map/"+fileName;
                console.log('20190907: NewMap = ' + NewMap);
                painter.addNewPicture(NewMap);
                mapViewer.isLoadedEditMap = true;
                currentChooseIndicator.currentChooseType = "移动地图";
            }
        }
    }



    /* 2.导航点表格展示 */
    Button {
       id: naviTableShowButton
       //width: 2.5 * mapViewer.width / 16
       width: mapViewer.width*0.33 / 2 - 1
       height: 36

       anchors.right: mapViewer.right
       anchors.rightMargin: 0
       anchors.top: mapViewer.top
       anchors.topMargin: 4

       contentItem: Text {
           text: "导航点表"
           font.family: "microsoft yahei"
           font.pixelSize: 23
           opacity: 1.0
           color: "#FFFFFF"
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideRight
       }

       background: Image{
           id: naviTableShowButtonBckImage
           anchors.horizontalCenter:parent.horizontalCenter
           anchors.verticalCenter:parent.verticalCenter
           anchors.fill: parent
           source:"qrc:/Resources/notClick.png"
       }
       onClicked: {
           openNaviPointTable();
       }
   }



    /* 导航点表格 */
	Rectangle{
        id: navigationPointsTableL
        width: mapViewer.width*0.3333
        height: mapItem.height - 56
		
		anchors.right: mapViewer.right
        anchors.rightMargin: 0
		anchors.top: mapViewer.top
        anchors.topMargin: 64 + 32 + 8
        visible: false

        property var naviPointsJson

		NaviPointTableV2 {
			id: naviPointTableL			
            anchors.fill: parent
            width: parent.width
            height: parent.height
		}

        Connections {
            target: naviPointTableL
            onSetNewNaviPoint: {
                var naviPointsJsonData = JSON.parse(navigationPointsTableL.naviPointsJson);
                var itemChanged = false;
                for(var pointId =0; pointId < naviPointsJsonData.length; pointId++){
                    if(origName == naviPointsJsonData[pointId].navipointsName) {
                        console.log('onSetNewNaviPoint111');
                        if(0 == Number(j)) {
                            if(naviPointsJsonData[pointId].x == x && naviPointsJsonData[pointId].y == y) {
                                naviPointsJsonData[pointId].navipointsName = itemContent;
                                itemChanged = true;
                                break;
                            }
                        }
                        if(1 == Number(j)) {
                            if(naviPointsJsonData[pointId].y == y) {
                                naviPointsJsonData[pointId].x = Number(itemContent);
                                itemChanged = true;
                                break;
                            }
                        }
                        if(2 == Number(j)) {
                            if(naviPointsJsonData[pointId].x == x) {
                                naviPointsJsonData[pointId].y = Number(itemContent);
                                itemChanged = true;
                                break;
                            }
                        }

                        if(itemContent == "delete_this_naviPoint") {
                            if(naviPointsJsonData[pointId].x == x && naviPointsJsonData[pointId].y == y) {
                                console.log('delete_this_naviPoint');
                                naviPointsJsonData.splice(pointId, 1);
                                itemChanged = true;
                                tableViewselectedRowBgBox.visible = false;  // added in 20191205
                                break;
                            }
                        }

                        if(itemContent == "navigation_to_this_position") {  // added in 20191209
                            if(naviPointsJsonData[pointId].x == x && naviPointsJsonData[pointId].y == y) {
                                console.log('navigation_to_this_position');
                                localmap.beforeNavigate(x, y);
                                break;
                            }
                        }
                    }
                }

                if(itemChanged == true) {
                    console.log('itemChanged, newitemContent = ' + itemContent + ', i = ' + i + ', j = ' + j + ', origName = ' + origName + ', x = ' + x + ', y = ' + y);
                    navigationPointsTableL.naviPointsJson = JSON.stringify(naviPointsJsonData);
                    painter.setNavigationPointJson(navigationPointsTableL.naviPointsJson);
                    naviPointTableL.clearNaviPointsListModel();
                    for(var pointId =0; pointId < naviPointsJsonData.length; pointId++){
                       naviPointTableL.setNaviPointsListModel(naviPointsJsonData[pointId].navipointsName, String(naviPointsJsonData[pointId].x), String(naviPointsJsonData[pointId].y));
                    }
                }
            }
            onHighLightNaviPoint: {
                var heighLightPos = "[" + x + ", " + y + "]";
                console.log("onHighLightNaviPoint, heighLightPos = " + heighLightPos);
                painter.highLightPosition(heighLightPos);
                tableViewselectedRowBgBox.y = 64 + 32 + 8 + 36 + rowId*32;  // added in 20191205
                tableViewselectedRowBgBox.visible = true;  // added in 20191205
            }
        }


    }

    Item {
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            console.log("move left");
            if (event.key == Qt.Key_Left) {
                console.log("move left");
                event.accepted = true;
            }
        }
    }

    /* 主操作逻辑 */   
    MenuBar{
        id: operationNavigationBar
        anchors.left: mapViewer.left
        anchors.leftMargin: 0
        anchors.top: mapViewer.top
        anchors.topMargin: 0

        width: 10 * mapViewer.width / 16 + shrinkButton.width
        height: 48
        property int selectButtonOp: 3

        Menu {
            title: qsTr("地图编辑")
            Action {
                text: qsTr("虚拟墙")
                onTriggered: {
                    descTextEdit.visible = false                    
                    painter.setShape(3);
                    painter.setDescriptionStr("Virtual Wall");
                    operationNavigationBar.selectButtonOp = 3
                    currentChooseIndicator.currentChooseType = "虚拟墙";
                }
            }
            Action {
                text: qsTr("导航线")
                onTriggered: {
                    descTextEdit.visible = false
                    painter.setShape(3);
                    painter.setDescriptionStr("Navigation Line");
                    operationNavigationBar.selectButtonOp = 3
                    currentChooseIndicator.currentChooseType = "导航线";
                }
            }
            Action {
                text: qsTr("导航点")
                onTriggered: {
                    descTextEdit.visible = false
                    painter.setShape(2);
                    operationNavigationBar.selectButtonOp = 2
                    currentChooseIndicator.currentChooseType = "导航点";
                    openNaviPointTable();  // added in 20191205
                }
            }
//            Action {
//                text: qsTr("轨迹生成")
//                onTriggered: {  // added in 20200102
//                    descTextEdit.visible = false
//                    painter.setShape(9);
//                    operationNavigationBar.selectButtonOp = 3
//                    currentChooseIndicator.currentChooseType = "轨迹生成";
//                }
//            }
            Action {
                text: qsTr("保存编辑")
                onTriggered: {
                    painter.sendMapEditData(0);
                    painter.saveMap();
                    currentChooseIndicator.currentChooseType = "保存地图";
                }
            }
            delegate: GreenMenuItem{}
            background: GreenMenuBarBg{}
        }

        Menu {
            title: qsTr("编辑操作")
            Action {
                text: qsTr("移动点")
                onTriggered: {
                    painter.setShape(6);
                    operationNavigationBar.selectButtonOp = 3
                    currentChooseIndicator.currentChooseType = "移动点";
                }
            }
            Action {
                text: qsTr("删除线")
                onTriggered: {
                    painter.setShape(7);
                    operationNavigationBar.selectButtonOp = 3
                    currentChooseIndicator.currentChooseType = "删除线";
                }
            }

            delegate: GreenMenuItem{}
            background: GreenMenuBarBg{}
        }
        Menu {
            title: qsTr("地图操作")
            Action {
                text: qsTr("移动地图")
                onTriggered: {
                    painter.setShape(1);
                    currentChooseIndicator.currentChooseType = "移动地图";
                }
            }
            Action {
                text: qsTr("复位地图")
                onTriggered: {
                    painter.resetImage();
                    currentChooseIndicator.currentChooseType = "复位地图";
                }
            }

            delegate: GreenMenuItem{}
            background: GreenMenuBarBg{}
        }
        delegate: GreenMenuBar{}
        background: GreenMenuBarBg {}
    }

    Button {
        id: shrinkButton
        width: 16
        height: mapItem.height

        anchors.left: mapItem.right
        anchors.leftMargin: 0
        anchors.top: mapItem.top
        anchors.topMargin: mapItem.height / 2 - shrinkButton.height / 2

        function shrinkMapItemArea(option) {
            if(option == 1) {
                if(shrinkButtonBckImage.source == "qrc:/Resources/shrinkUp.png") {
                    hideRightSpace();
                    mapItem.width = mapViewer.width - shrinkButton.width
                    shrinkButtonBckImage.source = "qrc:/Resources/shrinkDown.png"
                } else {
                    mapItem.width = 10 * mapViewer.width / 16
                    shrinkButtonBckImage.source = "qrc:/Resources/shrinkUp.png"
                }
            } else if(option == 2) {
                if(shrinkButtonBckImage.source == "qrc:/Resources/shrinkDown.png") {
                    //hideRightSpace();
                    mapItem.width = 10 * mapViewer.width / 16
                    shrinkButtonBckImage.source = "qrc:/Resources/shrinkUp.png"
                }
            } else {}
        }

        background: Image{
            id: shrinkButtonBckImage
            anchors.horizontalCenter:parent.horizontalCenter
            anchors.verticalCenter:parent.verticalCenter
            anchors.fill: parent
            source:"qrc:/Resources/shrinkUp.png"
        }
        onClicked: {
            shrinkButton.shrinkMapItemArea(1)
        }
    }

    onWidthChanged: {
        if(shrinkButtonBckImage.source == "qrc:/Resources/shrinkUp.png") {
            mapItem.width = 10 * mapViewer.width / 16
        } else {
            mapItem.width = mapViewer.width - shrinkButton.width
        }
    }

    Rectangle {
        id: currentChooseIndicator
        anchors.right: operationNavigationBar.right
        anchors.rightMargin: 0
        anchors.top: mapViewer.top
        anchors.topMargin: 0
        width: 3 * mapViewer.width / 16
        height: 46

        property string currentChooseType: " "

        Image {
            id: indicatorBgImage
            source: "qrc:/Resources/indicator.png"
            anchors.fill: parent
        }

		Text {
            id: leftText
            anchors.left: parent.left
            anchors.leftMargin: 2
            width: parent.width / 2
            height: parent.height
            font.family: "microsoft yahei"
            font.pixelSize: 14
            opacity: 0.66
            color: "white"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideLeft
            text: "当前操作类型: "
		}
        Text {
            id: rightText
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 2 + 4
            width: parent.width / 2 - 4
            height: parent.height
            font.family: "microsoft yahei"
            font.pixelSize: 21
            opacity: 1
            color: "#bcc5e8"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideLeft
            text: currentChooseIndicator.currentChooseType
        }
    }

    Rectangle {
        id: tableViewselectedRowBgBox
        anchors.right: mapViewer.right
        anchors.rightMargin: 0
        y: 64 + 32 + 8 + 36
        width: mapViewer.width*0.3333
        height: 32
        opacity: 0.40
        visible: false

        radius: 12  //设置矩形圆角弧度
        border.color: "#8a9ef9" //设置边框的颜色
        border.width: 4       //设置边框的大小
        smooth: true          //设置平滑度，默认是false

        BorderImage {
            source: "qrc: /Resources/lineEditBg.png"
            width: parent.width; height: parent.height
            border { left: 4; top: 4; right: 4; bottom: 4 }
        }
    }

    Rectangle {
        id: mapItem        
        anchors.left: mapViewer.left
        anchors.leftMargin: 0
        anchors.top: mapViewer.top
        anchors.topMargin: 8 + 40

        width: 10 * mapViewer.width / 16
        //height: 15 * mapViewer.height / 16
        height: mapViewer.height - 48
        color: "gray"

        Rectangle {  /* 地图编辑 */
            id: mapEdit
            width: mapItem.width
            height: mapItem.height
            color: "gray"

            LMessageBox {
                id: topologicalGraphNotUniqueErrTipBox
                boxMessage: "请删除导航线"
                btnNoVisible: true
                boxButtonRejectLabel: "好的"
            }
            LMessageBox {
                id: selectLineSuccessTipBox
                boxMessage: "确认删除此线?"
                btnYesVisible: true
                btnNoVisible: true
                boxButtonAcceptLabel: "是"
                boxButtonRejectLabel: "否"
                onAccepted: {
                    painter.deleteLine(1);
                }
                onRejected: {
                    painter.deleteLine(0);
                }
            }
//            FocusScope {
//                focus: true;
//                Keys.enabled: true;
//                Keys.onPressed: {
//                    console.log("Qt.ControlModifier")
//                    switch (event.key){
//                    case Qt.ControlModifier:
//                        break;
//                    default:
//                        return;
//                    }
//                }
//            }
            LmapEdit {
                id: painter;
                width: mapEdit.width
                height: mapEdit.height

                onWidthChanged: {
                    //painter.init()
                }
                onHeightChanged: {
                    //painter.init()
                }
                onSendCursorPos: {
                    if((0 == x && 0 == y) || (3 == operationNavigationBar.selectButtonOp)) {
                        descTextEdit.visible = false
                        setDescDefaultPromptText.visible = false
                    } else {
                        console.log('gridOp.selectButtonOp = ' + operationNavigationBar.selectButtonOp);
                        descTextEdit.visible = true
                        setDescDefaultPromptText.visible = true
                        descTextEdit.x = x + 4;
                        descTextEdit.y = y + 4;
                    }
                    if(-1 == x && -1 == y) {
                        descTextEdit.visible = false
                        setDescDefaultPromptText.visible = false
                        currentChooseIndicator.currentChooseType = "移动地图";  // added in 20191206
                        console.log('currentChooseIndicator.currentChooseType = ' + currentChooseIndicator.currentChooseType);
                    }
                }
                onSendTopologicalGraphNotUnique: {
                    topologicalGraphNotUniqueErrTipBox.visible = true;
                }
                onSendSelectLineSuccess: {
                    selectLineSuccessTipBox.visible = true;
                }
                onSendSelectPolymorphicWallSuccess: {
                    selectPolymorphicWallSuccessTipBox.visible = true;
                }
                onSendCurrentPointPos: {
                    changePosDialog.currentPointPos = "[" + String(x) + ", " + String(y) + "]";
                }
            }
        }


        Dialog {
            id: changePosDialog;
            x:(parent.width-width)/2;
            y:(parent.height-height)/2;
            implicitWidth: 500;
            implicitHeight: 300;
            title: "修改坐标";
            modal: true;
            focus: true;
            visible: false
            property string currentPointPos: "[, ]"
            standardButtons: Dialog.Ok | Dialog.Cancel


            Column {
                anchors.fill: parent
                Text {
                    text: "当前坐标为: " + changePosDialog.currentPointPos +";  请输入新坐标, eg: [50, 50]"
                    height: 40
                }
                TextField {
                    id: changePosDialogInput
                    width: parent.width * 0.75
                    focus: true
                    onFocusChanged: console.log("Focus changed " + focus)
                }
            }

            onAccepted: {
                console.log("Ok clicked, and changePosDialogInput.text = " + changePosDialogInput.text)
                var newPos = changePosDialogInput.text;
                painter.changePos(newPos);  //painter.highLightPosition(newPos);
            }
            onRejected: console.log("Cancel clicked")
        }

        Rectangle {
            id: descTextEdit
            height: 30
            width: 256
            x: 20
            y: 50
            property string defaultText : "请输入导航点名字, 按回车确认";
            visible: false

            radius: 9  //设置矩形圆角弧度
            border.color: "#bcc5e8" //设置边框的颜色
            border.width: 3       //设置边框的大小
            smooth: true          //设置平滑度，默认是false

            BorderImage {
                id: nameInputBox
                source: "qrc: /Resources/lineEditBg.png"
                width: parent.width; height: parent.height
                border { left: 4; top: 4; right: 4; bottom: 4 }
            }
            Text {
                id: setDescDefaultPromptText
                anchors.fill: parent
                text: descTextEdit.defaultText
                font.family: "microsoft yahei"
                font.pixelSize: 14
                opacity: 0.66
                color: "#bcc5e8"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            TextInput {
                id: textEdit
                text: ""
                font.family: "microsoft yahei"
                font.pixelSize: 16
                height: parent.height
                width: parent.width
                anchors.left: nameInputBox.left
                anchors.leftMargin: 12
                anchors.top: nameInputBox.top
                anchors.topMargin: 6
                color: "#00BFFF"
                focus: true

                Keys.onPressed: {
                    switch(event.key)
                    {
                        case Qt.Key_Enter:
                        case Qt.Key_Return:
                        {
                            console.log('textEdit.text = ' + textEdit.text);
                            var DescriptionStr = textEdit.text;
                            painter.setDescriptionStr(DescriptionStr);
                            setDescDefaultPromptText.visible = false;
                            descTextEdit.visible = false;
                            textEdit.remove(0, textEdit.length);
                            textEdit.forceActiveFocus();
                            openNaviPointTable();  // added in 20191205
                        }
                        default:
                            break;
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    setDescDefaultPromptText.visible = false
                    textEdit.forceActiveFocus();
                }
            }
        }
     }
}
