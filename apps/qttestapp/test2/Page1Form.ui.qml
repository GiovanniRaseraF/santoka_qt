import QtQuick 2.7
import QtQuick.Controls 2.0
import QtWebSockets 1.1
import QtWebEngine 1.4

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }
}
