/*
  date:20181221
  author:狐狸家的鱼
*/
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
ColumnLayout{
    Frame{
        Layout.fillWidth: true

        ListView{
            id: m_listView
            implicitWidth: parent.width
            implicitHeight: 320
            clip: true
            property int currentIndex: 0

            model: ListModel{
                id:model
//                ListElement{
//                    done:true
//                    description:"water the flowers"
//                }
            }

            delegate: RowLayout{
                width: parent.width
                height: 42
//                Text{
//                    text: "款式" + "" + (index+1);
//                }

                CheckBox{
                    text: qsTr("款式" + (index+1))
                    Layout.alignment: Qt.AlignLeft
                    checked: model.done
                    onClicked: {
                        model.done = checked
                        m_listView.currentIndex = index
                    }
                }
//                TextField{
//                    text: model.description
//                    onEditingFinished: model.description = text
//                    Layout.fillWidth: true
//                }
                Text{
                   text: "尺码: ";
                   width: 32
                }
                Rectangle {
                    width: parent.width - 64; height: parent.height;
                    color: "#87CEFA"; Layout.alignment: Qt.AlignLeft
                    Layout.fillWidth: true

                    Row {
                        spacing: 0
                        CheckBox{
                            text: qsTr("35")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("36")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("37")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("38")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("39")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("40")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("41")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("42")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("43")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("44")
                            checked: model.done
                            onClicked: {
                            }
                        }
                        CheckBox{
                            text: qsTr("45")
                            checked: model.done
                            onClicked: {
                            }
                        }
                    }
                }
            }
        }

    }
    RowLayout{
        Button{
            Layout.fillWidth: true
            text: '添加款式'
            onClicked: model.append({done:false,description:""})
        }
        Button{
            Layout.fillWidth: true
            text: '删除款式'
            onClicked: {
                model.remove(m_listView.currentIndex)
            }
        }
    }
}
