import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Extras 1.4
import QtQml.Models 2.12
import WifiControl 1.0
import WifiData 1.0
import SocketHandler 1.0
//import Manager 1.0
Rectangle {
	id:mainWifiView
    width: rootWidth*0.925
    height: rootHeight*0.925
	//anchors.leftMargin: 50
	//anchors.rightMargin: 50
	property int currentIndex
	property int connectRet:-1
	property int connectedIndex:-1
	property int current:0

	signal sendIndex(int oldindex)
	
	Image{
		anchors.horizontalCenter:mainWifiView.horizontalCenter
		anchors.verticalCenter:mainWifiView.verticalCenter
		anchors.fill: parent
		source:"qrc:/Resources/wifibackground.png"
	}

    function getImageSource(type){
        if(type=== 0)
        {
            return "qrc:/Resources/angle.png"
        }
        else{
            return ""
        }
    }

	function isConnected(index){
        if(index===connectedIndex){
            return "qrc:/Resources/connectedangle.png"
		}
		else
		{
            return "qrc:/Resources/angle.png"
            //return ""
		}
	}

	function getnamewidth(connectRet){
		//console.log("connectRet:",connectRet)
//        if(connectedIndex ===connectRet && connectRet!==-1){
//			return 100
//		}else
//		{
//			return rootWidth*5.5/8
//		}
        return rootWidth*5.5/8
	}

	function getconnectwidth(index){
		if(connectedIndex==-1){
			return rootWidth*7/8-300
        }else if(index===connectedIndex)
		{
			return rootWidth*7/8-400
		}
		
	}


	function getIntensitySource(intensity){

        if(intensity>= 60)
        {
            return "qrc:/Resources/wifi100.png"
        }
        else if(intensity>= 30)
		{
            return "qrc:/Resources/wifi60.png"
        }else
		{
			return "qrc:/Resources/wifi30.png"
		}

    }


    Component {

        id: contactDelegate
        //MouseArea {
		Item{
			id:delegateitem
            width: parent.width; height: 50
			//border.color:"gray"
			//border.width:1
			//pressed:true
            
            x:0
            y:mainWifiView.height*0.075

            Row {

				//这个是列间距
                spacing: 40
                leftPadding : 5
                topPadding : 10
                bottomPadding : 5
				//bottomPadding:true

				Item{
					width: 25
					height: 25
					//anchors.fill: parent
					//color: "#333"
                    //border.color: Qt.lighter(color, 1.2)

				}

				Image {  // 头像
                    //source:getImageSource(robottype)
                    source:isConnected(index)
                    sourceSize.width: 25
                    sourceSize.height: 35
					anchors.leftMargin: 25
					//width:100
                }
                Text {  // 名字
                    text: name
                    height: 35
					//anchors.leftMargin: 100
					//width:100
                    color: "white"
                    font.pointSize: 16
					width:getnamewidth(index)
                    //horizontalAlignment : Text.AlignHCenter
                    verticalAlignment : Text.AlignVCenter
                }

//				Image {  // 连接状态
//					source:isConnected(index)
//					width:getconnectwidth(index)
//					fillMode:Image.Pad
//					horizontalAlignment: Image.AlignLeft
//					verticalAlignment : Image.AlignVCenter
//					//anchors.leftMargin:getconnectwidth(connectRet)
//					anchors.leftMargin:25
//                    sourceSize.width: 25
//                    sourceSize.height: 35
//					//anchors.leftMargin: 25
//					//visible:false
//					//width:100
//                }
				
				Image {  // 强度
                    source:getIntensitySource(intensity)
                    sourceSize.width: 25
                    sourceSize.height: 25

                    fillMode:Image.PreserveAspectFit
                    //anchors.horizontalCenter:parent.horizontalCenter
                    //anchors.leftMargin: 25
					//width:100
                }

                
            }

			MouseArea{
				anchors.fill: parent
				onClicked:{
                    console.log("wifi clicked index:",index)
					delegateitem.ListView.view.currentIndex = index
					currentIndex=index
					//index.highlight=Rectangle { color: "lightsteelblue"; radius: 5 }
					}
			}
			//这项没用
			//states: State {
              //   name: "Current"
              //   when: delegateitem.ListView.isCurrentItem
                 //PropertyChanges { target: highlight; Rectangle { color: "lightsteelblue"; radius: 5 }}
             //}

			 Connections {
                        target: mainWifiView
						onSendIndex:{
								delegateitem.ListView.view.currentIndex = oldindex
							}
					}
        }
    }

    ListView {
        id: view
		y : -vbar.position*height

        boundsBehavior: Flickable.StopAtBounds
        //anchors.rightMargin: -363
        anchors.fill: parent
        anchors.topMargin:mainWifiView.height*0.075
		anchors.bottomMargin:100
		//anchors.leftMargin: 25
		//anchors.rightMargin: 25
        model: wificontrol.wifiDatas
        delegate: contactDelegate
		spacing:20
        highlight: Rectangle { 
                color: "#979595";
                radius: 5 ;opacity:0.5
				
				//y: view.currentItem.y
				Behavior on y {
				SpringAnimation {
                     spring: 5
                     damping: 1.0
				 }
          }
			}
        focus: false

		highlightFollowsCurrentItem: true
		//currentIndex:mainWifiView.current
		//onCurrentIndexChanged:mainWifiView.current=currentIndex
		ScrollBar.vertical: ScrollBar {
		 parent:view.parent
		 id: vbar
         hoverEnabled: true
         active: hovered || pressed
         orientation: Qt.Vertical
         //size: (parent.height-100)/50*wificontrol.wifiDatas.length
		 //size: 50*wificontrol.wifiDatas.length/(parent.height-100)
		 size:0.65
         anchors.top: parent.top
         anchors.right: parent.right
         anchors.bottom: parent.bottom
		 anchors.bottomMargin:100
         policy: ScrollBar.AlwaysOn
		 
		}

		 Connections {
            target: connectWifiButton
			onClicked:{
				//console.log("connectRet:",connectRet)
				//delegateitem.ListView.view.currentItem.visible = true
				}
			}

        
    }

	ButtonGroup {
      //buttons: buttongroup.children
	  id:buttongroup

	}

		Button {
            id: connectWifiButton
            anchors.right: updateWifiButton.left
            anchors.rightMargin: 75
			anchors.top: view.bottom
			anchors.topMargin: 10
            //width: 73
            //height: 38
            Text {
                text: qsTr("连接")
                font.family: "微软雅黑";
                color :"white"
                font.pixelSize:16
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.verticalCenter:parent.verticalCenter
            }
			background:Image{
                anchors.fill: parent
				source:"qrc:/Resources/connect.png"
			}
			ButtonGroup.group:buttongroup
            //text: qsTr("连接")
			 onClicked:{
				//wificontrol.wifiDatas.remove(delegateitem.ListView.view.currentIndex)
				connectedIndex=currentIndex
				connectRet=wificontrol.connectWifi(currentIndex)
				view.model=wificontrol.wifiDatas;
				console.log("connectRet:",connectRet)
				//指向连接的index
				sendIndex(currentIndex)
				//contactDelegate.delegateitem.view.currentIndex=connectedIndex

			 }
        }

        Button {
            id: updateWifiButton
			anchors.horizontalCenter:view.horizontalCenter
			anchors.top: view.bottom
			anchors.topMargin: 10
            //width: 50
            //height: 40
            //text: qsTr("刷新")
            Text {
                text: qsTr("刷新")
                font.family: "微软雅黑";
                color :"white"
                font.pixelSize:16
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.verticalCenter:parent.verticalCenter
            }
			background:Image{

				source:"qrc:/Resources/update.png"
			}
			
			ButtonGroup.group:buttongroup
            onClicked:{
                wificontrol.intWifiList()
				view.model=wificontrol.wifiDatas;
            }
        }

        Button {
            id: disconnectWifiButton
			anchors.left: updateWifiButton.right
            anchors.leftMargin: 75
			anchors.top: view.bottom
			anchors.topMargin: 10
            //width: 50
            //height: 40
			//text: qsTr("断开")
            Text {
                text: qsTr("断开")
                font.family: "微软雅黑";
                color :"white"
                font.pixelSize:16
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.verticalCenter:parent.verticalCenter
            }
			background:Image{
				source:"qrc:/Resources/disconnect.png"
			}

			ButtonGroup.group:buttongroup
            
			onClicked:{
				//wificontrol.wifiDatas.remove(delegateitem.ListView.view.currentIndex)
				
				wificontrol.disConnectWifi(connectedIndex)
				//wificontrol.intWifiList()
				connectedIndex=-1
				view.model=wificontrol.wifiDatas;
			 }
        }

    WifiControl {
        id: wificontrol
    }


}


