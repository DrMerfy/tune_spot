/*
 * File:    Configurator.hpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#ifndef Configurator_HPP
#define Configurator_HPP

#include <QObject>
#include <QUrl>
#include <memory>
#include <AubioWrapper.hpp>
#include <NotesController.hpp>
#include <PitchBuffer.hpp>

class Configurator : public QObject {

    Q_OBJECT
    Q_PROPERTY(bool active MEMBER activeTuner WRITE setActive NOTIFY activeChanged())
    Q_PROPERTY(QString note MEMBER closestNote READ getClosestNote() NOTIFY samplesAnalyzed())
    Q_PROPERTY(qreal percentage MEMBER percentageOfDistanceFromTheClosestNote READ getPercentageOfDistanceFromTheClosestNote() NOTIFY samplesAnalyzed())
    Q_PROPERTY(qreal frequency MEMBER confidentFrequency READ getFrequency() NOTIFY samplesAnalyzed())
    Q_PROPERTY(quint16 baseFreq READ getBaseFrequency() WRITE setBaseFrequency NOTIFY baseFrequencyChanged())
    Q_PROPERTY(QString setterName MEMBER organSetter READ getOrganSetter() WRITE setOrganSetter NOTIFY organSetterChanged())

public:
    explicit Configurator(QObject *parent = nullptr);

    /**
     * @brief setActive this function activates and deactivates the microphone of the tuner
     * @param active is a variable which indicates if the tuner is gonna be active or not
     */
    void setActive(bool active);

    /**
     * @brief setOrganSetter is a function that sets the organ setter that is gonna be used
     * @param setter is the setter that defines the organSetter
     * freeMode
     * celloX where x {1-4} check Notes Controller what every number means e.g. cello1
     * guitarX where x {1-6] check Notes Controller what every number means e.g. guitar6
     */
    void setOrganSetter(QString setter);

    /**
     * @brief getOrganSetter is a function that returns the organ setter
     * @return the organ setter
     */
    QString getOrganSetter();

    /**
     * @brief getBaseFrequency is a function that returns the base frequency
     * @return the base frequency
     */
    quint16 getBaseFrequency();

    /**
     * @brief setBaseFrequency is a function that changes the base frequency
     * @param frequency is the base frequency value that we want to set
     */
    void setBaseFrequency(quint16 frequency);

    /**
     * @brief getClosestNote is a function that returns the closest note
     * @return the closest note
     */
    QString getClosestNote();

    /**
     * @brief getPercentageOfDistanceFromTheClosestNote is a function that returns the percentage of distance from the closest note
     * @return the percentage of distance from the closest note
     */
    qreal getPercentageOfDistanceFromTheClosestNote();

    /**
     * @brief getFrequency this function returns the frequency
     * @return the frequency
     */
    qreal getFrequency();

signals:
	void samplesAnalyzed();

    void activeChanged();

    void baseFrequencyChanged();

    void organSetterChanged();

private:
    /**
     * @brief applyFormat is a functions that sets the format settings of the audioinput
     */
    void applyFormat();

    //  the audioinput device
    std::unique_ptr<QAudioInput> recorder;

    //  the format settings of the qiodevice
    QAudioFormat formatSettings;

    //  the buffer that includes the audio input
    PitchBuffer pitchBuffer;

    //  we use this notes' controller to handle the notes as name and frequencies and their base frequency
    NotesController notesController;

    //  the aubio object
    AubioWrapper aubio;

    //  this variable indicates if the tuner's microphone is active or not
    bool activeTuner;

    //  this varibles is the setter id
    QString organSetter;

    //  this variable is used for graphical reasons and it's range is -100 to 100
    qreal percentageOfDistanceFromTheClosestNote;

    //  this variable is used for graphical reasons
    QString closestNote;

    //  this variable stores the last confident current frequency that has recognized
    qreal confidentFrequency;

    //  this variable stores the threads hold of the confidence
    float confidenceThresHold = .90;

private slots:
	void analyzeSamples();
};

#endif // Configurator_HPP
