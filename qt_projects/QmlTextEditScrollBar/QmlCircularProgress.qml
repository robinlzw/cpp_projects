/*!
 *@file QmlCircularProgress.qml
 *@brief Qml圆形进度条
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.4

Canvas {
    property color arcColor: "#148014"
    property color arcBackgroundColor: "#AAAAAA"
    property int arcWidth: 2
    property real progress: 0
    property real radius: 16
    property bool anticlockwise: false
    //property alias interval: timer.interval
    property bool textVisible: false

    signal progressDone

    id: canvas
    width: 2*radius + arcWidth
    height: 2*radius + arcWidth

    Text{
        visible: textVisible
        anchors.centerIn: parent
        font.pointSize: 16
        text: Math.floor((parent.progress / 360) * 100 )+ "%"
    }

    QtObject {
        id:attrs;
        property int counter
        Component.onCompleted: {
           attrs.counter = 180;
       }
    }
    function currentDateTime(){
        return Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss.zzz ddd");
    }

    Timer{
        id: timer
        running: false
        repeat: true
        interval: 1000
        triggeredOnStart: true
        onTriggered:{
            parent.progress += 2;
//            var delayedTime = 0;
//            while(delayedTime < 36000000) {
//                delayedTime++;
//            }

            attrs.counter -= 1;
            if (attrs.counter < 0){
                timer.stop();
            }

            if (parent.progress > 360){
                onStop();
                parent.requestPaint();
                progressDone();
                return;
            }
            parent.requestPaint();
        }
    }

    function isRunning(){
        return(timer.running)
    }

    function onStart(){
        progress = 0;
        var ctx = getContext("2d");
        ctx.clearRect(0,0,width,height);
        //timer.running = true;
        timer.start()
    }

    function onStop(){
        progress = 0;
        var ctx = getContext("2d");
        ctx.clearRect(0,0,width,height);
        timer.running = false;        
    }

    onPaint: {
        var ctx = getContext("2d")
        ctx.clearRect(0,0,width,height)
        ctx.beginPath()
        ctx.strokeStyle = arcBackgroundColor
        ctx.lineWidth = arcWidth
        ctx.arc(width/2,height/2,radius,0,Math.PI*2,anticlockwise)
        ctx.stroke()

        var r = progress*Math.PI/180
        ctx.beginPath()
        ctx.strokeStyle = arcColor
        ctx.lineWidth = arcWidth

        ctx.arc(width/2,height/2,radius,0-90*Math.PI/180,r-90*Math.PI/180,anticlockwise)
        ctx.stroke()
    }
}
