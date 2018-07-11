import QtQuick 2.0
import QtQuick.Layouts 1.3
import Configurator 1.0

import "../scripts/TunerContext.js" as Context

Item {
    signal percentage_changed(string note_name, string percentage)

    onPercentage_changed: Context.tune(note_name, percentage)


    FontLoader {
        id: localFont
        source: "../data/fonts/OpenSans-Light.ttf"
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: tuner_holder.bottom
        anchors.topMargin: -40
        color: "#FFFFFF"
        font.family: localFont.name
        font.weight: Font.Light
        font.pixelSize: Qt.application.font.pixelSize * 5
        text: "A"
        id: notes_holder
    }

    Item {
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.centerIn: parent
        height: lines_container.height; width: lines_container.width
        id: tuner_holder

        RowLayout {
            anchors.centerIn: parent
            id: lines_container
            spacing: 15.5
        }

        Item {
            anchors.centerIn: parent
            width: lines_container.width
            id: tuning_circle_holder
        }
    }

    RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: notes_holder.bottom
            id: string_holder
            spacing: 12
    }

    Component.onCompleted: {
        Context.onCreate(notes_holder, string_holder, lines_container, tuning_circle_holder, configurator);
    }
}
