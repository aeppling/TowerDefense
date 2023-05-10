#include "NetworkController.hpp"
#include <iostream>
NetworkController::NetworkController(bool isServer){
    this->isServer = isServer;
    this->port = 53000;

    if(this->isServer){
        std::cout << "serveur" << std::endl;
        std::cout << "Local IP : " << sf::IpAddress::getLocalAddress() << std::endl;
        sf::IpAddress clientIp = this->waitForConnection();
        std::cout << "Client IP : " << clientIp << std::endl;
    }else{
        std::cout << "client" << std::endl;
        // Attend la réponse du serveur contenant son adresse IP
            std::string serverAddressString;
            std::cout << "Please enter the IP address of the server : ";
            std::cin >> serverAddressString;
            sf::IpAddress serverAddress(serverAddressString);

            // Connecte le client au serveur
            if (this->connectToServer(serverAddress))
            {
                std::cout << "Connected to server" << std::endl;
            }
            else
            {
                std::cout << "Failed to connect to server" << std::endl;
            }
    }  
}

bool NetworkController::connectToServer(const sf::IpAddress& serverAddress)
{
    // Crée une socket de connexion TCP
    this->serverSocket = new sf::TcpSocket;

    std::cout << "Connecting to server..." << std::endl;
    if (this->serverSocket->connect(serverAddress, this->port) != sf::Socket::Done)
    {
        delete this->serverSocket;
        return false;
    }

    std::cout << "Connected to server" << std::endl;

    
    return true;
}


sf::IpAddress NetworkController::waitForConnection()
{    
    std::cout << "Server is listening to port " << this->port << ", waiting for connections... " << std::endl;

    // Attend la connexion d'un client
    sf::TcpListener listener;

    // lie l'écouteur à un port
    if (listener.listen(this->port) != sf::Socket::Done)
    {
        std::cout << "Failed to bind listener to port " << this->port << std::endl;
    }
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "Failed to accept client's connection" << std::endl;
    }
    std::cout << "Client connected: " << client.getRemoteAddress() << std::endl;
    this->clients.push_back(&client);
    // Envoie l'adresse IP du serveur au client
    sf::Packet packet;
    packet << sf::IpAddress::getLocalAddress().toString();
    if (client.send(packet) != sf::Socket::Done)
    {
        std::cout << "Failed to send server IP" << std::endl;
        return sf::IpAddress::None;
    }
    std::cout << "Server IP sent to client" << std::endl;

    // Ferme la socket d'écoute

    // Retourne l'adresse IP du client
    return client.getRemoteAddress();
}

void NetworkController::sendMessageToAllClients(const std::string& message)
{
    for (auto& client : this->clients)
    {
        if (client->send(message.c_str(), message.size()) != sf::Socket::Done)
        {
            std::cout << "Failed to send message to client" << std::endl;
        }
    }
}

void NetworkController::sendMessageToServer(const std::string& message)
{
    if (this->serverSocket->send(message.c_str(), message.size()) != sf::Socket::Done)
    {
        std::cout << "Failed to send message to server" << std::endl;
    }
}

std::string NetworkController::receiveMessage(sf::TcpSocket* clientSocket)
{
    int message;
    std::size_t received;
    sf::Socket::Status status = clientSocket->receive(&message, sizeof(message), received);
    if (status == sf::Socket::Done && received == sizeof(message)) {
        return std::to_string(message);
    }
}


