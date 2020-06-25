import QtQuick 2.12
import QtQuick.Controls 1.4
import SortFilterProxyModel 1.0

Rectangle {
    id: naviPointsPage
    anchors.fill: parent

    Image{
        id: tableBoundingBoxImage
        anchors.horizontalCenter:parent.horizontalCenter
        anchors.verticalCenter:parent.verticalCenter
        anchors.fill: parent
        source:"qrc:/Resources/backBoundingBox.png"
        opacity: 0.66
    }


	signal setNewNaviPoint(string itemContent, int i, int j, string origName, int x, int y)
	signal highLightNaviPoint(int rowId, string naviPointName, int x, int y)
	function setNaviPointsListModel(naviPointName, x, y) {
		sourceModel.insert(sourceModel.count, {"navipointsName": naviPointName, "x": x, "y": y});
	}
	function updateNaviPointsListModel(index, naviPointName, x, y) {
		sourceModel.remove(index);
		sourceModel.insert(index, {"navipointsName": naviPointName, "x": x, "y": y});
	}
	function clearNaviPointsListModel() {
		sourceModel.clear();		
		proxyModel.source = sourceModel;
	}


    Rectangle{
        property string defaultText : "请输入导航点名字查询";
        id: focusScope
        width: naviPointsPage.width/2; height: 32
        //anchors.right: naviPointsPage.right
		anchors.left: naviPointsPage.left
        anchors.top: naviPointsPage.top
        anchors.topMargin: -32
        
        radius: 12  //设置矩形圆角弧度
        border.color: "#00BFFF" //设置边框的颜色
        border.width: 2       //设置边框的大小
        smooth: true          //设置平滑度，默认是false
		visible: true

        BorderImage {
			source: "qrc: /Resources/lineEditBg.png"
            width: parent.width; height: parent.height
            border { left: 4; top: 4; right: 4; bottom: 4 }
        }
        Text {
            id: defaultInputText
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
			font.family: "microsoft yahei"
            font.pixelSize: 16
            text: focusScope.defaultText
            color: "gray"
            font.italic: true
        }
        TextInput {
            id: textInput
			font.family: "microsoft yahei"
            font.pixelSize: 16
			anchors { left: parent.left; right: parent.right; leftMargin:8; rightMargin: 4; verticalCenter: parent.verticalCenter }
            focus: true
        }		
        states:State {
            name: "hasText"
            when: textInput.text != ''
            PropertyChanges{ target: defaultInputText; opacity: 0 }
        }
        transitions: [
            Transition {
                from: ""
                to: "hasText"
                NumberAnimation { exclude: defaultInputText; properties: "opacity"}
            },
            Transition {
                from: "hasText"
                to: ""
                NumberAnimation {properties: "opacity"}
            }
        ]
    }

    TableView{
        id: tableView
		width: parent.width
        height: parent.height
        anchors.fill: parent
        backgroundVisible: false //隐藏表格默认背景色(白色)
        frameVisible: false //隐藏表格最外面的矩形框线


        itemDelegate: Rectangle{
            id: tableCell
            border.color: "gray";
            radius:3;

            TextField{
                id: textField
                height: 32
                width: tableView.width / 2
                text: styleData.value
                font.family: "microsoft yahei"
                font.pointSize: 12
                textColor: "black";
                selectByMouse: true                
                onEditingFinished: {
                    var itemContent = proxyModel.get(styleData.row);
                    var posX = itemContent["x"], posY = itemContent["y"];
                    console.log('styleData[' + styleData.row + ', ' + styleData.column + '].text = ' + text);
                    if(0 == styleData.column) {
                        naviPointsPage.setNewNaviPoint(text, styleData.row, styleData.column, styleData.value, posX, posY);
                    } else {
                        //console.log('itemContent[styleData.row].navipointsName = ' + itemContent["navipointsName"]);
                        naviPointsPage.setNewNaviPoint(text, styleData.row, styleData.column, itemContent["navipointsName"], posX, posY);
                    }
                }
            }

            MouseArea{
                anchors.fill: parent
                enabled: true
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    var itemContent = proxyModel.get(styleData.row);
                    var naviName = itemContent["navipointsName"], posX = itemContent["x"], posY = itemContent["y"];
                    naviPointsPage.highLightNaviPoint(styleData.row, naviName, posX, posY);                   
                }  // 点击时触发
                onDoubleClicked: {
                    textField.forceActiveFocus()
                }
            }
        }
        headerDelegate: headerDele;  //表头委托
        rowDelegate: rowDele;   //行委托


        //定义表头的委托
        Component{
            id:headerDele
            Rectangle{
                id: headerRect
                //color: "transparent"
				color: "#797a7b"
                border.width: 1
                radius: 3
                height: 36
                Text{
                    text: styleData.value
                    anchors.centerIn: parent
                    font.family: "微软雅黑";
                    font.pixelSize: 12;
                    color: "white";
                }
            }
        }

        //定义行的委托
        Component{
            id:rowDele
            Item{
                height: 32
            }
        }

        TableViewColumn {
            role: 'navipointsName'
            title: "导航点名字"
            width: tableView.width / 2
        }

        TableViewColumn {
            role: 'x'
            title: "x位置"
            width: (tableView.width / 4) - 32
        }

        TableViewColumn {
            role: 'y'
            title: "y位置"
            width: (tableView.width / 4) - 32
        }

        TableViewColumn {
            width: 32
            title: "导航"
            delegate: Button {
                Image{
					anchors.horizontalCenter: parent.horizontalCenter
					width: 32				
					height: 32
					source: "qrc:/Resources/naviPoint.png"
				}
                onClicked: {
                    var itemContent = proxyModel.get(styleData.row);
                    var posX = itemContent["x"], posY = itemContent["y"];
                    console.log('styleData[' + styleData.row + ', ' + styleData.column + '].text = ' + text);
                    naviPointsPage.setNewNaviPoint("navigation_to_this_position", styleData.row, styleData.column, itemContent["navipointsName"], posX, posY);
                }
            }
        }

        TableViewColumn {
            width: 32
            title: "删除"
            delegate: Button {
				Image{
					anchors.horizontalCenter: parent.horizontalCenter
					width: 32				
					height: 32
					source: "qrc:/Resources/delete.png"
                }
                onClicked: {
                    var itemContent = proxyModel.get(styleData.row);
                    var posX = itemContent["x"], posY = itemContent["y"];
                    console.log('styleData[' + styleData.row + ', ' + styleData.column + '].text = ' + text);
                    naviPointsPage.setNewNaviPoint("delete_this_naviPoint", styleData.row, styleData.column, itemContent["navipointsName"], posX, posY);
                }
            }
        }


        //更新表格标题列宽度和role
        function updateColumn2Table(arrayData){
            if(arrayData.length != 3){
                console.log("DataShowTable.qml updateColumn2Table arrayData.length !=3");
                return;
            }

            var arrayTitle = arrayData[0]; //标题数组
            var arrayWidth = arrayData[1]; //宽度数组
            var arrayRoles = arrayData[2]; //role数组
            if(arrayTitle.length != arrayWidth.length || arrayTitle.length > arrayRoles.length){
                console.log("arrayTitle argument error in DataShowTable.qml updateColumn2Table(arrayTitle,arrayWidth,arrayRoles)");
                return;
            }

            tableView.model.clear(); //先将model里面的数据清空避免在更新的列里面有相同的role直接显示
            var i,str,count = tableView.columnCount;
            var sum = new Number(0);
            //求出长度累加和以便于按比例分配列宽
            for(i =0;i<arrayWidth.length;i++){
                sum += arrayWidth[i];
            }
            var prefix = 'import QtQuick 2.7;import QtQuick.Controls 1.4;TableViewColumn {width: Math.round(tableView.width *'; //创建TableViewColumn的代码
           //前缀
            //将现在的每列全部删除
            for(i=0;i<count;i++){
                tableView.removeColumn(0);
            }
            //循环添加TableViewColumn
            for(i=0;i<arrayTitle.length;i++){
                str = prefix + arrayWidth[i]/sum +");role:\"" + arrayRoles[i] + "\";title:\"" + arrayTitle[i] + "\"}";
                tableView.addColumn(Qt.createQmlObject(str,tableView,"dynamicSnippet1"));
            }
        }


        model: SortFilterProxyModel {
            id: proxyModel
            source: sourceModel.count > 0 ? sourceModel : null
            sortOrder: tableView.sortIndicatorOrder
            sortCaseSensitivity: Qt.CaseInsensitive
            sortRole: sourceModel.count > 0 ? tableView.getColumn(tableView.sortIndicatorColumn).role : ""
            filterString: "*" + textInput.text + "*"
            filterSyntax: SortFilterProxyModel.Wildcard
            filterCaseSensitivity: Qt.CaseInsensitive
        }


        ListModel {  //使用ListModel，并加入测试数据
            id: sourceModel          
        }

        Component.onCompleted: {
             //table.updateColumn2Table(bankPaySearchTableArray);    //创建表
             console.log("000 updateColumn2Table sourceModel.count = " + sourceModel.count + ", proxyModel.sortRole = " + proxyModel.sortRole);
        }
    }
}

