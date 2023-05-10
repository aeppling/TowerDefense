#include "NetworkController.hpp"
#include <iostream>
NetworkController::NetworkController(bool isServer){
    this->isServer = isServer;
    this->port = 53000;

    if(this->isServer){
        std::cout << "serveur" << std::endl;
        std::cout << "Local IP : " << sf::IpAddress::getLocalAddress() << std::endl;
        this->waitForConnection();
        
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
    // Create a TCP connection socket
    this->serverSocket = new sf::TcpSocket;

    std::cout << "Connecting to server..." << std::endl;
    if (this->serverSocket->connect(serverAddress, this->port) != sf::Socket::Done)
    {
        delete this->serverSocket;
        return false;
    }
    return true;
}


void NetworkController::waitForConnection()
{    
    std::cout << "Server is listening to port " << this->port << ", waiting for connections... " << std::endl;

    // Attend la connexion d'un client
    sf::TcpListener listener;

    // lie l'écouteur à un port
    if (listener.listen(this->port) != sf::Socket::Done)
    {
        std::cout << "Failed to bind listener to port " << this->port << std::endl;
    }
    auto client = std::make_unique<sf::TcpSocket>();
    if (listener.accept(*client) != sf::Socket::Done)
    {
        std::cout << "Failed to accept client's connection" << std::endl;
        return;
    }
    std::cout << "Client connected: " << client->getRemoteAddress() << std::endl;

    // Ajoute le client à la liste
    this->clients.push_back(std::move(client));
}


void NetworkController::sendMessageToAllClients(const std::string& message)
{
    for (auto& client : this->clients)
    {
        std::cout << "Sending message to client " << client->getRemoteAddress() << std::endl;
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
    std::cout << "Message sent to server" << std::endl;
}

std::string NetworkController::receiveMessage(sf::TcpSocket* clientSocket)
{
    char buffer[1024];
    std::size_t received;
    sf::Socket::Status status = clientSocket->receive(buffer, sizeof(buffer), received);
    if (status == sf::Socket::Done) {
        return std::string(buffer, received);
    }
    std::cout << "Failed to receive message from client" << std::endl;
    return "";
}



void NetworkController::sendMessageToClient(const sf::IpAddress& clientIpAddress, const std::string& message)
{   
    for (const auto& client : clients) {
        std::cout << "Client IP address: " << client->getRemoteAddress() << std::endl;
    }
    std::cout << "Sending message to client " << clientIpAddress << std::endl;
    auto client = std::find_if(clients.begin(), clients.end(), [&](const std::unique_ptr<sf::TcpSocket>& c) { return c->getRemoteAddress() == clientIpAddress; });

    if (client != clients.end())
    {
        if ((*client)->send(message.c_str(), message.size()) != sf::Socket::Done)
        {
            std::cout << "Failed to send message to client" << std::endl;
        }
        std::cout << "Message sent to client " << clientIpAddress << std::endl;
    }else{
        std::cout << "Client not found" << std::endl;
    }
}

std::vector<sf::TcpSocket*> NetworkController::getClients() {
    std::vector<sf::TcpSocket*> result;
    for (auto& client : this->clients) {
        result.push_back(client.get());
    }
    return result;
}

NetworkController::~NetworkController() {
    delete this->serverSocket;
}

