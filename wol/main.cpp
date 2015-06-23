/* ========================================================================
   File: wol.exe
   Date: 23.06.2015
   Revision: 1.0.0
   Creator: DimiG
   Copyright 2015 Dmitri G. <dimi615@pisem.net>
   ======================================================================== */


#include <QUdpSocket>
#include <QStringList>
#include <iostream>
#include <windows.h>

using namespace std;


void SetConsoleColour(WORD* Attributes, DWORD Color)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Color);
}

void ResetConsoleColour(WORD Attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

int main(int argc, char** argv)
{
    WORD Attributes = 0;
    SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN );

    cout << "\nwol 1.0.0 - CLI tool for WakeUP On LAN remote computer (Windows 7/8 platform)" << endl;
    cout << "Copyright (C) DimiG, 2015\n" << endl;

    ResetConsoleColour(Attributes);

    /*
     * Check if argument exist
     */

    if (argc < 2) {

        cout << "Usage: wol [macAddress...]\n" << endl;
        cout << "macAddress\tMAC address for computer interface you wanna WakeUP" << endl;

        return 1;
    }

    /*
     * Correct argument if wrong
     */

    const QString MacAddressPattern = "^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$";
    const int PacketSize = 102;

    for (int i = 1; i < argc; i++) {
        QString macAddressStr = argv[i];
        QRegExp rx(MacAddressPattern);
        if (rx.indexIn(macAddressStr) == -1) {
            cout << "Warning: invalid MAC address " << macAddressStr.toStdString() << endl;
            continue;
        }

        macAddressStr.replace('-', ':');
        QStringList macBytes = macAddressStr.split(':');

        /*
         * Create packet
         */

        unsigned char packet[PacketSize];
        unsigned char mac[6];

        for (int i = 0; i < 6; i++) {
            mac[i] = (quint8)macBytes[i].toUInt(0, 16);
            packet[i] = 0xFF;
        }

        for (int i = 1; i <= 16; i++) {
            memcpy(&packet[i * 6], &mac, 6 * sizeof(unsigned char));
        }

        /*
         * Send packet
         */

        QUdpSocket socket;
        socket.writeDatagram(reinterpret_cast<const char*>(packet), PacketSize, QHostAddress::Broadcast, 40000);
        socket.flush();

        cout << "Action COMPLETE!!!" << endl;
    }

    return 0;
}
