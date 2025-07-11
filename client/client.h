#ifndef CLIENT_H
#define CLIENT_H

#include "client/views/game_view.h"
#include "client/views/main_view.h"
#include "client/views/qtwindow.h"
#include "client/controllers/game_controller.h"
#include "client/controllers/menu_controller.h"
#include "client/controllers/messages/message_event.h"
#include "client/controllers/messages/leave_event.h"
#include "common/communication/protocol.h"
#include "client/receiver&sender/clientReceiverLoop.h"
#include "client/receiver&sender/clientSenderLoop.h"
#include "client/menuClient.h"
#include "client/gameClient.h"

#include <iostream>
#include <exception>
#include <vector>

#include <QApplication>
#include <QWidget>
#include <QTimer>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define NAME_SERVER "localhost"
#define PORT "12345"

using namespace SDL2pp;

#include <string>

class Client {
private:
    std::string clientName;
    bool partida_iniciada;
    Protocol protocol;
    Queue<Response> recv_queue;
    Queue<std::shared_ptr<MessageEvent>> send_queue;
    RecvLoop receiver;
    SendLoop sender;
    std::vector<std::string> players;

public:
    // Constructor
    Client(const std::string name, const char* host, const char* port);
    ~Client() {
        receiver.stop();
        sender.stop();
        try {
            // Esto es un hack, es para q el hilo sender salga del queue.pop() y tire error asi se cierra correctamente
            send_queue.try_push(std::make_shared<LeaveEvent>());
        } catch (...) {}
        
        kill();
        receiver.join();
        sender.join();
    };

    void setName(const std::string& name);
    void run(QApplication& app, MenuController& menuController);
    void kill() {
        try {
            protocol.close();
        } catch (...) {}
    };

    bool receiveConnectionResponse();
};

#endif