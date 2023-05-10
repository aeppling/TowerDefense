#ifndef UNTITLED1_NETWORKCONTROLLER_HPP_
#define UNTITLED1_NETWORKCONTROLLER_HPP_

#include <SFML/Network.hpp>
#include <vector>
class NetworkController{

private:
    bool isServer;
    short unsigned int port;
    sf::TcpSocket *serverSocket;
    std::vector<sf::TcpSocket*> clients;


public:   
    
    NetworkController(bool isServer);
    void broadcastMessage( const std::string& message);
    sf::IpAddress receiveServerAddress();
    bool connectToServer(const sf::IpAddress& serverAddress);
    sf::IpAddress waitForConnection();
    void sendMessageToAllClients(const std::string& message);
    void sendMessageToServer(const std::string& message);
    std::string receiveMessage(sf::TcpSocket* clientSocket);
    bool getIsServer() { return this->isServer; };
    std::vector<sf::TcpSocket*> getClients() { return this->clients; };
    sf::TcpSocket *getServerSocket() { return this->serverSocket; };


};

#endif //UNTITLED1_NETWORKCONTROLLER_HPP_