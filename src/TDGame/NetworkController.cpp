#include "NetworkController.hpp"
#include <iostream>
NetworkController::NetworkController(bool isServer){
    this->isServer = isServer;
    this->port = 53000;

    if(this->isServer){
        std::cout << "serveur" << std::endl;
        sf::IpAddress clientIp = this->waitForConnection();
        std::cout << "Client IP : " << clientIp << std::endl;
    }else{
        std::cout << "client" << std::endl;
        // Envoie un message de broadcast pour demander l'adresse IP du serveur
        this->broadcastMessage("Hello Supinfo !");
        // Attend la réponse du serveur contenant son adresse IP
        sf::IpAddress serverAddress = this->receiveServerAddress();
        if (serverAddress != sf::IpAddress::None)
        {
            std::cout << "Server address : " << serverAddress << std::endl;

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
        else
        {
            std::cout << "Failed to receive server address" << std::endl;
        }
    }  
}

void NetworkController::broadcastMessage( const std::string& message)
{
    // Crée une socket d'envoi de diffusion
    sf::UdpSocket socket;
    socket.setBlocking(false);

    // Envoie le message en diffusion sur le port spécifié
    sf::IpAddress broadcast = sf::IpAddress::Broadcast;
    if (socket.send(message.c_str(), message.size(), broadcast, this->port) != sf::Socket::Done)
    {
        std::cout << "Failed to broadcast message" << std::endl;
        return;
    }

    // Ferme la socket
    socket.unbind();
}

sf::IpAddress NetworkController::receiveServerAddress()
{
    // Crée une socket d'écoute sur le port spécifié
    sf::UdpSocket socket;
    if (socket.bind(this->port) != sf::Socket::Done)
    {
        std::cout << "Failed to bind socket" << std::endl;
        return sf::IpAddress::None;
    }

    // Attend la réception de la réponse du serveur
    char data[1024];
    std::size_t received;
    sf::IpAddress serverAddress;
    if (socket.receive(data, sizeof(data), received, serverAddress, this->port) != sf::Socket::Done)
    {
        std::cout << "Failed to receive message" << std::endl;
        return sf::IpAddress::None;
    } 
    std::cout << "Received " << received << " bytes from " << serverAddress << " : " << data << std::endl;
    // Ferme la socket
    socket.unbind();

    // Retourne l'adresse IP du serveur
    return serverAddress;
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
    // Crée une socket d'écoute sur le port spécifié
    std::cout << "Waiting for connection..." << std::endl;
    sf::TcpListener listener;
    if (listener.listen(this->port) != sf::Socket::Done)
    {
        std::cout << "Failed to listen on port " << this->port << std::endl;
        return sf::IpAddress::None;
    }
    std::cout << "Server is listening to port " << this->port << ", waiting for connections... " << std::endl;

    // Attend la connexion d'un client
    sf::TcpSocket client;
    std::cout << "Waiting for client to connect..." << std::endl;
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "Failed to accept client" << std::endl;
        return sf::IpAddress::None;
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
    listener.close();

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


