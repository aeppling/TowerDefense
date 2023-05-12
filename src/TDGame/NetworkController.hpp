#ifndef UNTITLED1_NETWORKCONTROLLER_HPP_
#define UNTITLED1_NETWORKCONTROLLER_HPP_

#include <SFML/Network.hpp>
#include <vector>

class NetworkController {
private:
    bool isServer;
    bool isWaiting;
    unsigned short port;
    sf::TcpSocket* serverSocket;
    std::vector<std::unique_ptr<sf::TcpSocket>>* clients;
public:
    NetworkController(bool isServer);
    ~NetworkController();

    bool connectToServer(const sf::IpAddress& serverAddress);
    void waitForConnection();
    void sendMessageToAllClients(const std::string& message);
    void sendMessageToServer(const std::string& message);
    std::string receiveMessage(sf::TcpSocket* clientSocket);
    void sendMessageToClient(const sf::IpAddress& clientIpAddress, const std::string& message);
    bool getIsServer() { return this->isServer; };
    std::vector<sf::TcpSocket*> getClients();
    sf::TcpSocket* getServerSocket() { return this->serverSocket; };
    std::string detectMessageReceived();
    void handleMessage(std::string message);
    bool isWaitingScreen() { return(this->isWaiting);};
    // TODO
    // disconnect client
    // disconnect from server
    // disconnect all clients


};

#endif //UNTITLED1_NETWORKCONTROLLER_HPP_
