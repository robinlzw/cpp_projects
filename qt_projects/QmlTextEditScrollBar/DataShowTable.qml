import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: dataShowTable
    anchors.fill: parent
    color: "#87CEFA"

    function createTable(arrayData) {
        myTable.updateColumn2Table(arrayData);
    }

    signal setNewNaviPoint(string naviPointName, int i, int j)

    TableView{
        id: myTable
        width: parent.width
        height: parent.height
        anchors.fill: parent
        backgroundVisible: false //隐藏表格默认背景色(白色)
        frameVisible: false //隐藏表格最外面的矩形框线

        itemDelegate: Rectangle{
            id: tableCell
            anchors.fill: parent;
            border.color: "white";
            radius:3;
            color: styleData.selected ? "#00FFFF" : "white";
           
            TextField{
                id: textField
                height: 25
                width: 300
                text: styleData.value
                selectByMouse: true
                onEditingFinished: {
                    console.log('styleData[' + styleData.row + ', ' + styleData.column + '].text = ' + text);                   
					naviPointsPage.setNewNaviPoint(text, styleData.row, styleData.column)
                }
                Component.onCompleted: console.log("Object item: styleData.value", styleData.value)
            }
        }
        headerDelegate: headerDele;  //表头委托
        rowDelegate: rowDele;   //行委托


        //定义表头的委托
        Component{
            id:headerDele
            Rectangle{
                id: headerRect
                color: "transparent"
                border.width: 1
                radius: 3
                height: 25
                Text{
                    text: styleData.value
                    anchors.centerIn: parent
                    font.family: "微软雅黑";
                    font.pixelSize: 12;
                    color: "black";
                }
            }
        }

        //定义行的委托
        Component{
            id:rowDele
            Item{
                height: 25
            }
        }

        //更新表格标题列宽度和role
        function updateColumn2Table(arrayData){
            if(arrayData.length != 3){
                console.log("DataShowTable.qml updateColumn2Table arrayData.length !=3");
                return;
            }

            console.log("updateColumn2Table");


            var arrayTitle = arrayData[0]; //标题数组
            var arrayWidth = arrayData[1]; //宽度数组
            var arrayRoles = arrayData[2]; //role数组
            if(arrayTitle.length != arrayWidth.length || arrayTitle.length > arrayRoles.length){
                console.log("arrayTitle argument error in DataShowTable.qml updateColumn2Table(arrayTitle,arrayWidth,arrayRoles)");
                return;
            }

            myTable.model.clear(); //先将model里面的数据清空避免在更新的列里面有相同的role直接显示
            var i,str,count = myTable.columnCount;
            var sum = new Number(0);
            //求出长度累加和以便于按比例分配列宽
            for(i =0;i<arrayWidth.length;i++){
                sum += arrayWidth[i];
            }
            var prefix = 'import QtQuick 2.7;import QtQuick.Controls 1.4;TableViewColumn {width: Math.round(myTable.width *'; //创建TableViewColumn的代码
           //前缀
            //将现在的每列全部删除
            for(i=0;i<count;i++){
                myTable.removeColumn(0);
            }
            //循环添加TableViewColumn
            for(i=0;i<arrayTitle.length;i++){
                str = prefix + arrayWidth[i]/sum +");role:\"" + arrayRoles[i] + "\";title:\"" + arrayTitle[i] + "\"}";
                myTable.addColumn(Qt.createQmlObject(str,myTable,"dynamicSnippet1"));
            }
        }

        model: ListModel {  //使用ListModel，并加入测试数据
            id: sourceModel
//            ListElement {
//                recordId: 1
//                accountId: 1
//                promptInfo: "test"
//                proxyInfo: "test"
//            }
//            ListElement {
//                recordId: 1
//                accountId: 1
//                promptInfo: "test"
//                proxyInfo: "test"
//            }
//            ListElement {
//                recordId: 1
//                accountId: 1
//                promptInfo: "test"
//                proxyInfo: "test"
//            }
        }

        Component.onCompleted: {            

        }
    }
}

