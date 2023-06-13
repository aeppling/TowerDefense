#include "NetworkController.hpp"
#include <iostream>
NetworkController::NetworkController(bool isServer){
    // Crée un objet NetworkController client ou serveur
    this->isServer = isServer;
    this->isWaiting = false;
    this->port = 53000;
    this->clients = new std::vector<std::unique_ptr<sf::TcpSocket>>();

}

bool NetworkController::connectToServer(const sf::IpAddress& serverAddress)
{
    // Connexion au serveur en fonction de son adresse Ip
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
{   // Attend la connexion d'un client
    std::cout << "Server is listening to port " << this->port << ", waiting for connections... " << std::endl;
    this->isWaiting = true;
    
    sf::TcpListener listener;

    // lie l'écouteur à un port
    if (listener.listen(this->port) != sf::Socket::Done)
    {
        std::cout << "Failed to bind listener to port " << this->port << std::endl;
        this->isWaiting = false;
        return;
    }

    int numClients = 0;
    while (numClients < 1) {
        auto client = std::make_unique<sf::TcpSocket>();
        if (listener.accept(*client) != sf::Socket::Done)
        {
            std::cout << "Failed to accept client's connection" << std::endl;
            continue;
        }
        std::cout << "Client connected: " << client->getRemoteAddress() << std::endl;

        // Ajoute le client à la liste
        this->clients->push_back(std::move(client));
        std::cout << "Client added to list" << std::endl;
        numClients++;
        std::cout << "Number of clients: " << numClients << std::endl;
    }
    this->isWaiting = false;
}




void NetworkController::sendMessageToAllClients(const std::string& message)
{
    // Envoie un message à tous les clients
    for (const auto& client : *this->clients)
    {
        std::cout << "Sending message to client " << client->getRemoteAddress() << std::endl;
        if (client->send(message.c_str(), message.size()) != sf::Socket::Done)
        {
            std::cout << "Failed to send message to client " << client->getRemoteAddress() << std::endl;
        }
    }
}




void NetworkController::sendMessageToServer(const std::string& message)
{
    // Envoie un message au serveur
    if (this->serverSocket->send(message.c_str(), message.size()) != sf::Socket::Done)
    {
        std::cout << "Failed to send message to server" << std::endl;
    }
    std::cout << "Message sent to server" << std::endl;
}

std::string NetworkController::receiveMessage(sf::TcpSocket* clientSocket)
{   
    // Lis le message en attente
    std::cout << "Receiving message from client" << std::endl;
    char buffer[1024];
    std::size_t received;
    sf::Socket::Status status = clientSocket->receive(buffer, sizeof(buffer), received);
    if (status == sf::Socket::Done) {
        return std::string(buffer, received);
    }
    std::cout << "Failed to receive message from client test" << std::endl;
    return "";
}



void NetworkController::sendMessageToClient(const sf::IpAddress& clientIpAddress, const std::string& message)
{
    // Envoie un message à un client
    for (const auto& client : *clients)
    {
        std::cout << "Client IP address: " << client->getRemoteAddress() << std::endl;
    }
    
    std::cout << "Sending message to client " << clientIpAddress << std::endl;
    
    auto client = std::find_if(clients->begin(), clients->end(), [&](const std::unique_ptr<sf::TcpSocket>& c) {
        return c->getRemoteAddress() == clientIpAddress;
    });
    
    if (client != clients->end())
    {
        if ((*client)->send(message.c_str(), message.size()) != sf::Socket::Done)
        {
            std::cout << "Failed to send message to client" << std::endl;
        }
        else
        {
            std::cout << "Message sent to client " << clientIpAddress << std::endl;
        }
    }
    else
    {
        std::cout << "Client not found" << std::endl;
    }
}


std::vector<sf::TcpSocket*> NetworkController::getClients() {
    // Retourne la socket entre la liste des sockets des clients
    std::vector<sf::TcpSocket*> result;
    for (const auto& client : *(this->clients)) {
        result.push_back(client.get());
    }
    return result;
}


NetworkController::~NetworkController() {
    delete this->serverSocket;
    delete this->clients;
}

std::string NetworkController::detectMessageReceived()
{
    // Detecte si un message a été reçu
    bool messageReceived = false;
    // Si on est un serveur, on vérifie si un message a été reçu sur chacun des clients
   
    if (isServer)
    {
        for (const auto& client : *clients)
        {
            char buffer[1024];
            std::size_t received;
            client->setBlocking(false);
            sf::Socket::Status status = client->receive(buffer, sizeof(buffer), received);

            if (status == sf::Socket::Done)
            {
                std::cout << "Received message \"" << buffer << "\" from client " << client->getRemoteAddress() << std::endl;
                messageReceived = true;
                return std::string(buffer, received);
            }
            else if (status == sf::Socket::Disconnected)
            {
                std::cout << "Client " << client->getRemoteAddress() << " disconnected" << std::endl;
            }
            else if (status == sf::Socket::Error)
            {
                std::cout << "An error occurred while receiving data from client " << client->getRemoteAddress() << std::endl;
            }
            client->setBlocking(false);
        }
    }
    // Si on est un client, on vérifie si un message a été reçu sur la socket du serveur
    else
    {
        char buffer[1024];
        this->serverSocket->setBlocking(false);
        std::size_t received;
        sf::Socket::Status status = this->serverSocket->receive(buffer, sizeof(buffer), received);
        if (status == sf::Socket::Done)
        {
            std::cout << "Received message \"" << buffer << "\" from server" << std::endl;
            messageReceived = true;
            return std::string(buffer, received);
        }
        else if (status == sf::Socket::Disconnected)
        {
            std::cout << "Disconnected from server" << std::endl;
        }
        else if (status == sf::Socket::Error)
        {
            std::cout << "An error occurred while receiving data from server" << std::endl;
        }
        this->serverSocket->setBlocking(true);
    }

    return "";
}

void NetworkController::handleMessage(std::string message){
    // Si on est un client on envoie le message au serveur
    // Si on est un serveur on envoie le message à tous les clients
    if (this->isServer == false) {
        this->sendMessageToServer(message);
    } else {
        this->sendMessageToAllClients(message);
    }
}
