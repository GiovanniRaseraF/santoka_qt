import QtQuick 2.15
import QtQuick.Controls 2.12
Item{
Rectangle {
    id: hello
    width: 6000; height: 6000

    signal qmlSignal(string sentMsg)
    function qmlSlot(receivedMsg) {
        console.log("QML received: " + receivedMsg)
    }

    objectName: "hello"

    Button{
        id: button1
        onClicked: qmlSignal("Hello from QML!")
    }
}
}
