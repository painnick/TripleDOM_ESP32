#pragma once

#include <Arduino.h>
#include <esp_log.h>

#include "common.h"
#include "DFMiniMp3.h"

#define MP3_TAG "DFPLAYER"

#ifdef DEBUG
#define DEFAULT_VOLUME 10
#else
#define DEFAULT_VOLUME 15
#endif

int BACKGROUND_TRACK = -1;

#define MAIN_THEME_TRACK 1

#define BEAM_RIFLE_TRACK 1
#define HEAD_VULCAN_TRACK 2

void playBackground();

class Mp3Notify;

typedef DFMiniMp3<HardwareSerial, Mp3Notify> DfMp3;

class Mp3Notify {
public:
    static void PrintlnSourceAction(DfMp3_PlaySources source,
                                    const char *action) {
        if (source & DfMp3_PlaySources_Sd) {
#ifdef DEBUG
            ESP_LOGD(MP3_TAG, "SD Card, %s", action);
#endif
        }
        if (source & DfMp3_PlaySources_Usb) {
#ifdef DEBUG
            ESP_LOGD(MP3_TAG, "USB Disk, %s", action);
#endif
        }
        if (source & DfMp3_PlaySources_Flash) {
#ifdef DEBUG
            ESP_LOGD(MP3_TAG, "Flash, %s", action);
#endif
        }
    }

    static void OnError(DfMp3 &mp3, uint16_t errorCode) {
        // see DfMp3_Error for code meaning
        switch (errorCode) {
            case DfMp3_Error_Busy:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - Busy");
#endif
                break;
            case DfMp3_Error_Sleeping:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - Sleeping");
#endif
                break;
            case DfMp3_Error_SerialWrongStack:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - Serial Wrong Stack");
#endif
                break;

            case DfMp3_Error_RxTimeout:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - Rx Timeout!!!");
#endif
                break;
            case DfMp3_Error_PacketSize:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - Wrong Packet Size!!!");
#endif
                break;
            case DfMp3_Error_PacketHeader:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - Wrong Packet Header!!!");
#endif
                break;
            case DfMp3_Error_PacketChecksum:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - Wrong Packet Checksum!!!");
#endif
                break;

            default:
#ifdef DEBUG
                ESP_LOGE(MP3_TAG, "Com Error - %d", errorCode);
#endif
                break;
        }
    }

    static void OnPlayFinished(DfMp3 &mp3, DfMp3_PlaySources source,
                               const uint16_t track) {
#ifdef DEBUG
        ESP_LOGD(MP3_TAG, "Play finished for #%d", track);
#endif
        if (track == BACKGROUND_TRACK) {
            playBackground();
        }
    }

    static void OnPlaySourceOnline(DfMp3 &mp3, DfMp3_PlaySources source) {
        PrintlnSourceAction(source, "online");
    }

    static void OnPlaySourceInserted(DfMp3 &mp3, DfMp3_PlaySources source) {
        PrintlnSourceAction(source, "inserted");
    }

    static void OnPlaySourceRemoved(DfMp3 &mp3, DfMp3_PlaySources source) {
        PrintlnSourceAction(source, "removed");
    }
};

DfMp3 dfmp3(Serial1, PIN_MP3_RX, PIN_MP3_TX);

inline void setDefaultVolume() {
    ESP_LOGD(MP3_TAG, "Set Volume");
    dfmp3.setVolume(DEFAULT_VOLUME);
    dfmp3.loop();
}

inline void setupSound() {
    ESP_LOGI(MP3_TAG, "Setup DFPlayer");
    dfmp3.begin(9600, 1000);
}

void playBackground() {
    ESP_LOGD(MP3_TAG, "Play BGM");
    BACKGROUND_TRACK = MAIN_THEME_TRACK;
    dfmp3.playMp3FolderTrack(MAIN_THEME_TRACK);
    dfmp3.loop();
}

void playBeamRifle() {
    dfmp3.playAdvertisement(BEAM_RIFLE_TRACK);
}

void playHeadVulcan() {
    dfmp3.playAdvertisement(HEAD_VULCAN_TRACK);
}

void stopAdvert() {
    dfmp3.stopAdvertisement();
}