import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
//import TestModel 1.0

Window {
    id:mainwindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Контроллер команд")
    signal s_row_change
    Button
    {
        id:but_add
        x:549
        y:37
        text:"Добавить"
        onClicked:
        {
            dataModel.add("Commnad", "Alias Command")
        }
    }
    Button
    {
        id:but_change
        x:549
        y:97
        text:"Изменить"
        onClicked:
        {
            dataModel.change(view.currentIndex, "new Command", "new Alias")
        }
    }
    Button
    {
        id:but_remove
        x: 555
        y: 157
        text: "Удалить"
        onClicked:
        {
            dataModel.removeRow(view.currentIndex, dataModel)
        }
    }
    Rectangle {
        id:rec_view
        width: parent.width/1.4
        height: parent.height/1.4
        ListView {
            id: view

            anchors.margins: 10
            anchors.fill: parent
            spacing: 10
            model: dataModel
            clip: true


            highlight: Rectangle {
                color: "skyblue"
            }
            highlightFollowsCurrentItem: true

            delegate: Item {
                id: listDelegate

                property var view: ListView.view
                property var isCurrent: ListView.isCurrentItem

                width: view.width
                height: 40

                Rectangle {
                    id:rec_view_componenet
                    anchors.margins: 5
                    anchors.fill: parent
                    radius: height / 2
                    color: "white"//model.color
                    border {
                        color: "black"
                        width: 1
                    }

                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text:model.CommandNameRole+" "+model.CommandAliasRole    //text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {view.currentIndex = model.index
                            txt_dop.text = model.DopRole
                        }
                    }
                }
            }
        }
    }

}
