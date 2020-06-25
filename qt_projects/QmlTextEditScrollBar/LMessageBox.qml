import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: window
    Material.theme: Material.Dark
    Material.accent: Material.color(Material.Purple)
    visible: false
    flags: Qt.FramelessWindowHint|Qt.Window
    modality: Qt.ApplicationModal

    signal accepted
    signal rejected

    property bool btnYesVisible: false
    property bool btnNoVisible: false
    property bool useCircularProgress: false

    property string boxMessage: ""                            // msgBox Message
    property string boxTitle: ""                              // msgBox Title

    property string boxButtonAcceptLabel: "YES"                // msgBox 'Accept' Button Text
    property string boxButtonRejectLabel: "NO"                // msgBox 'Reject' Button Text

    property bool boxButtonAcceptHighlighted: true            // msgBox 'Accept' Button Highlighted

    property int boxWidth: 320                                // msgBox Width
    property int boxHeight: 160                               // msgBox Height

    property real boxButtonAcceptColor: Material.Blue         // msgBox 'Accept' Button Color (Material enum); automatic color fix

    minimumWidth: boxWidth
    maximumWidth: boxWidth
    minimumHeight: boxHeight
    maximumHeight: boxHeight

    title: boxTitle

    function circularProgressStart(displayCircularProgress){
        if(displayCircularProgress == 1) {
            cProgress.textVisible = true;
            cProgress.radius = 24;
        }
        cProgress.onStart();
    }

    function circularProgressStop(){
        cProgress.onStop();
    }

    background: BorderImage {
        source:"qrc:/Resources/popBox.png"
        border { left: -256; top: -256; right: -256; bottom: -256 }
    }

    QmlCircularProgress{
        id: cProgress
        anchors.centerIn: parent
        arcWidth: 3
        radius: 0
        //interval: 16
        arcColor: "#148014"
        textVisible: false

        onProgressDone: {
            cProgress.textVisible = false;
            cProgress.radius = 0;
            window.close()
        }
    }


    Button {
        id: btnYes
        text: boxButtonAcceptLabel
        font.family: "microsoft yahei"
        font.pixelSize: 16
        visible: btnYesVisible

        x: 64
        y: (ApplicationWindow.height - 16) - btnYes.height
        width: 72
        height: 36

        background: Image{
            anchors.horizontalCenter:parent.horizontalCenter
            anchors.verticalCenter:parent.verticalCenter
            anchors.fill: parent
            source:"qrc:/Resources/isOk.png"
        }
        highlighted: boxButtonAcceptHighlighted
        Material.accent: Material.color(boxButtonAcceptColor)
        onClicked: {
            accepted()
            if(useCircularProgress == false) {
                window.close()
            }
        }
    }

    Button {
        id: btnNo
        text: boxButtonRejectLabel
        font.family: "microsoft yahei"
        font.pixelSize: 16
        visible: btnNoVisible

        x: (ApplicationWindow.width - 64) - btnNo.width
        y: (ApplicationWindow.height - 16) - btnNo.height
        width: 72
        height: 36

        background: Image{
            anchors.horizontalCenter:parent.horizontalCenter
            anchors.verticalCenter:parent.verticalCenter
            anchors.fill: parent
            source:"qrc:/Resources/isCancel.png"
        }
        highlighted: boxButtonAcceptHighlighted
        Material.accent: Material.color(boxButtonAcceptColor)
        onClicked: {
            rejected()
            window.close()
        }
    }

    Label {
        id: lblMsg
        width: ApplicationWindow.width - 20
        text: boxMessage
        font.family: "microsoft yahei"
        font.pixelSize: 14
        color: "white"
        x: 20
        y: 20
        wrapMode: Label.WordWrap
    }
}
