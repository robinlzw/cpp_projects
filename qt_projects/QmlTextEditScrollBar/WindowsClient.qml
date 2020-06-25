import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

//Rectangle {
//Item {
Window{
    id: root
    objectName: "window"
    visible: true
    color: "#161616"
    title: "云绅大天使客户端"
    width: 1600
    height: 900
    //width: Screen.desktopAvailableWidth
    //height: Screen.desktopAvailableHeight
    //visibility:FullScreen


    property alias rootWidth: root.width
    property alias rootHeight: root.height
	property int whichOneClicked:0

    signal clickedWhichOne(int index)

	function getSideResource(index){
        //console.log("getSideResource:",index)
        if(whichOneClicked===0)
        {
            if(index===0)
               return "qrc:/Resources/pagedown1.png"
            else if(index===1)
                return "qrc:/Resources/page2.png"
            else if(index===2)
                return "qrc:/Resources/page3.png"
            else if(index===3)
                return "qrc:/Resources/page4.png"
            else
                return ""
        }else
        {
            if(index===0)
               return "qrc:/Resources/pageblack1.png"
            else if(index===1&&whichOneClicked!=1)
                return "qrc:/Resources/pageblack2.png"
            else if(index===1&&whichOneClicked==1)
                return "qrc:/Resources/pagedown2.png"
            else if(index===2&&whichOneClicked!=2)
                return "qrc:/Resources/pageblack3.png"
            else if(index===2&&whichOneClicked==2)
                return "qrc:/Resources/pagedown3.png"
            else if(index===3&&whichOneClicked!=3)
                return "qrc:/Resources/pageblack4.png"
            else if(index===3&&whichOneClicked==3)
                return "qrc:/Resources/pagedown4.png"
            else
                return ""
        }
	}

	function clickWhichOne(index){
        //console.log("clickWhichOne:",index)
        if(index===0)
        {
            part1.source="qrc:/Resources/page0.png"
            part2.source="qrc:/Resources/page5.png"
            part3.source ="qrc:/Resources/mainpage2.png"
            //return "qrc:/Resources/pagedown1.png"
        }
        else if(index===1)
        {
            part1.source="qrc:/Resources/page0black.png"
            part2.source="qrc:/Resources/page5black.png"
            part3.source ="qrc:/Resources/main2black.png"
            //return "qrc:/Resources/pagedown2.png"
        }
        else if(index===2)
        {
            part1.source="qrc:/Resources/page0black.png"
            part2.source="qrc:/Resources/page5black.png"
            part3.source ="qrc:/Resources/main2black.png"
            //return "qrc:/Resources/page3.png"
        }
        else if(index===3)
        {
            part1.source="qrc:/Resources/page0black.png"
            part2.source="qrc:/Resources/page5black.png"
            part3.source ="qrc:/Resources/main2black.png"
            //return "qrc:/Resources/page4.png"
        }
        //else return ""
	}

    property bool isScreenPortrait:true
    property color darkFontColor: "#e7e7e7"
    readonly property color lightBackgroundColor: "#cccccc"
    readonly property color darkBackgroundColor: "#161616"
    //property Component circularGauge: CircularGaugeView {}

    //FontLoader { id: openSans; source: "qrc:/fonts/OpenSans-Regular.ttf" }

    Text {

        font.pointSize: 13
        font.bold: true
        id: textSingleton
    }


    StackLayout {
        id: layout
        anchors.bottomMargin: 0
        anchors.top: root.top
        anchors.topMargin: rootHeight*0.075

        anchors.rightMargin: 0
        anchors.left: stackView.left
        anchors.leftMargin: rootWidth*0.075
        anchors.fill: parent
        currentIndex: 0

		
		
        Connections {
                        target: root
                        //onClickedWhichOne: listmodelOne.setProperty(0,visible,false)
                        onClickedWhichOne: {
                            console.log("idnex:"+index)
                            //listmodelOne.setProperty(1,"colorCode","red")
                            //spipeView.setProperty(index,"colorCode","red")

                            //swipeView.visible=false
                            layout.currentIndex=index
							//console.log("focus"+Window.activeFocusItem)
							if(index==2){
								dirctionControl.focus=true
							}
							if(index==3){
								mapEditPage.openMapList()
							}
                            //swipeView.currentItem.visible=true
                            //swipeView.currentItem.visible=true
                            //if(index==swipeView.currentIndex){swipeView.currentItem.visible=true}
                        }
                    }

	  MainPage{

	  }

      WifiView{
		
	  }

	  
	  
	   FocusScope {
          id: dirctionControl
          //focus: true
			Scan{

			}	      		
			
		  }
	 

     MapView{
		id: mapEditPage
	 }
      
    }
    //property Component wifi: WifiView {}

    /*
    property Component delayButton: ControlView {
           darkBackground: false

           control: DelayButton {
               text: "Alarm"
               anchors.centerIn: parent
           }
       }
     */

    property var componentMap: {
		 "\u9996\u9875":0,
         "\u8fde\u63a5": 1,
        "\u4efb\u52a1\u6267\u884c": 2,
		"\u5730\u56fe": 3


        //"\u8fde\u63a5": wifi,
        //"\u5730\u56fe": delayButton,
        //"4": gauge,

    }

    Image {
        width: rootWidth*0.075
        height:  rootHeight*0.2
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin:0
        anchors.rightMargin: rootWidth*0.925

        id: part1
        source: "qrc:/Resources/page0.png"

    }

    Image {
        y:rootHeight*0.6

        width: rootWidth*0.075
        height:  rootHeight*0.4
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin:0
        anchors.rightMargin: rootWidth*0.925

        id: part2
        source: "qrc:/Resources/page5.png"

    }

    Image {
        x:rootWidth*0.075
        y:0

        width: rootWidth*0.925
        height:  rootHeight*0.075
        anchors.bottomMargin: 0
        //anchors.leftMargin: 0
        //anchors.topMargin:0
        //anchors.rightMargin: rootWidth*7/8

        id: part3
        source: "qrc:/Resources/mainpage2.png"

    }

    Image {
        x:rootWidth*0.075
        y:rootHeight*0.075
        z:-1
        width: rootWidth*0.925
        height:  rootHeight*0.925
        anchors.bottomMargin: 0
        //anchors.leftMargin: 0
        //anchors.topMargin:0
        //anchors.rightMargin: rootWidth*7/8

        id: part4
        source: "qrc:/Resources/mainpage.png"

    }


    StackView {
    //Item{
        id: stackView
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: rootHeight*0.2
        //anchors.top:parent.top-50
        anchors.rightMargin: rootWidth*0.925
        anchors.fill:parent

		opacity:1.0

        //index: spipeView.index
        //anchors.right: root.right
        //anchors.leftMargin: 5

        initialItem: ListView {
            id:sideColumn
            width: rootWidth*0.1
            //color:"#2b2b2b"
            boundsBehavior: Flickable.StopAtBounds
            model: ListModel {
                id:innerModel
				 ListElement {
                    //title: "\u9996\u9875"
                     title:"" 
                }
                ListElement {
                    //title: qsTr("wifi")
                    //title: "\u8fde\u63a5"

                }
				ListElement {
                    //title: "\u4efb\u52a1\u6267\u884c"                  
                }
                ListElement {
                    //title: "\u5730\u56fe"                   
                }
                
            }

            delegate: Button {
           //delegate: ToolButton{
                id:sideButton
                width: rootWidth*0.075
                height: rootHeight*0.1
                text: title
                //fontColor:root.darkFontColor
                //flat:true
                //highlighted:true
                //icon.name: title
                //icon.source:"qrc:/Resources/images/icon-go.png"
                //
                //icon.color:"transparent"


                //icon.source:getSideResource(index)

                //display:AbstractButton.TextUnderIcon

                background:Image {
                    //id: name
                    source: getSideResource(index)
                    Connections {
                                    target: root
                                    //onClickedWhichOne: listmodelOne.setProperty(0,visible,false)
                                    onClickedWhichOne: {
                                        //console.log("item:"+innerModel.currentItem)
										console.log("item source:"+sideButton.background.source)
                                    }
                                 }
                }
				/*
                background: Rectangle {

                          implicitWidth: sideButton.width
                          implicitHeight: sideButton.height
                          border.color: "#26282a"
                          border.width: 0.5
                          //opacity: enabled ? 1 : 0.3
                          //color: "#161616"
                      }*/
//				 background:Rectangle {
//						implicitWidth: sideButton.width
//                        implicitHeight: sideButton.height
//						color: "white"

//						 CustomBorder {
						  
//                          //implicitWidth: sideButton.width
//                          //implicitHeight: sideButton.height
//							commonBorder: false
//							lBorderwidth: 0
//							rBorderwidth: 0
//							tBorderwidth: 2
//							bBorderwidth: 2
//							borderColor: "red"
//						  //borderColor: "red"
//						  }

//				 }
				 
				 
				
                          //opacity: enabled ? 1 : 0.3
                          //color: "#161616"

				
                /*
                onClicked: {
                    if (stackView.depth == 1) {

                        //click works 点击
                        //stackView.push({item: componentMap[title]});
                        stackView.push({item: componentMap[title]});
                        stackView.currentItem.forceActiveFocus();
                    }
                }*/

                onClicked: {
                    if (stackView.depth == 1) {
                        // Only push the control view if we haven't already pushed it...
                        //root.clickedWhichOne(stackView.currentIndex);

						//stackView.currentItem.forceActiveFocus();
                        //root.clickedWhichOne(componentMap[title]);
						whichOneClicked=index
                        root.clickedWhichOne(index);
						clickWhichOne(index)
						
                        console.log("emit clickedWhichOne:"+index)
                    }
                }

            }


        }



    }

//    Rectangle {
//        id: rectangle

//        anchors.bottomMargin: 0
//        anchors.left: stackView.left
//        anchors.leftMargin: rootWidth*0.085
//        anchors.topMargin: 0
//        //anchors.top:parent.top-50
//        anchors.rightMargin: 0

//        width: rootWidth*0.915
//        height: rootHeight/9
//        color: "#ababab"
//    }

    /*

    SwipeView {
        id: swipeView
        x: 288
        y: 182
        width: 600
        height: 653
        orientation:Qt.Vertical
        //currentIndex: stackView.index
        Connections {
                        target: root
                        //onClickedWhichOne: listmodelOne.setProperty(0,visible,false)
                        onClickedWhichOne: {
                            console.log("idnex:"+index)
                            //listmodelOne.setProperty(1,"colorCode","red")
                            //spipeView.setProperty(index,"colorCode","red")

                            //swipeView.visible=false
                            swipeView.setCurrentIndex(index)
                            //swipeView.currentItem.visible=true
                            //swipeView.currentItem.visible=true
                            //if(index==swipeView.currentIndex){swipeView.currentItem.visible=true}
                        }
                    }

        Repeater {
            model: 3
            Pane{
                x: 200
                y: 0
                //contentWidth:600
                width: swipeView.width
                //height: spipeView.height

                Column{
                    //x: 200
                    //y: 0
                    width: swipeView.width
                    height: swipeView.height
                    Text{
                        text: index
                        color: "red"
                        width: 100
                        height: 100
                        //height: spipeView.height
                    }
                }
            }
        }

    }
    */

}
