/*!
 *@file QmlProgress.qml
 *@brief Qml进度条
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.2

ProgressBar {
	property color proColor: "#148014"
	property color proBackgroundColor: "#AAAAAA"
	property int proWidth: 2
	property real progress: 0
    property real proRadius: 4
	property alias interval: timer.interval
    property bool isRun: false
    property int backWidth: 200

	function isRunning(){
		return(timer.running)
	}

	function onStart(){
		lProgress.progress = 0;
		timer.running = true;
	}

	function onStop(){
		timer.running = false;
	}

	id: lProgress
	anchors.centerIn: parent
	value: (progress/100)
	padding: 2

	background: Rectangle {
        implicitWidth: backWidth
		implicitHeight: 16
		color: lProgress.proBackgroundColor
		radius: lProgress.proRadius
	}

	contentItem: Item {
        implicitWidth: backWidth
		implicitHeight: 10

		Rectangle {
            width: lProgress.visualPosition * parent.width
			height: parent.height
			radius: 2
			color: lProgress.proColor
		}
	}

	Timer{
		id: timer
        running: isRun
		repeat: true
        interval: 100
		onTriggered:{
			lProgress.progress++;
            if (lProgress.progress > 98){
				lProgress.onStop();
				return;
			}
		}
	}
}
