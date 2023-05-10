#ifndef UNTITLED1_NETWORKCONTROLLER_HPP_
#define UNTITLED1_NETWORKCONTROLLER_HPP_

#include <SFML/Network.hpp>
#include <vector>

class NetworkController {
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
    sf::Socket* isMessageReceived();
    // TODO
    // disconnect client
    // disconnect from server
    // disconnect all clients


private:
    bool isServer;
    unsigned short port;
    sf::TcpSocket* serverSocket;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
};

#endif //UNTITLED1_NETWORKCONTROLLER_HPP_
