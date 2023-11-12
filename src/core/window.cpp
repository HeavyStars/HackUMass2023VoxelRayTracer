#include "window.hpp"
Window::Window(int w, int h, std::string title){
    _window = new sf::RenderWindow(sf::VideoMode(w, h), title);
    _window->setFramerateLimit(120);
    ImGui::SFML::Init(*_window);
    _running = false;
    windowWidth = w;
    windowHeight = h;
}

Window::~Window(){
    delete _window;
    _window = NULL;
}

void Window::run(){

    _running = true;
    while(_running){

        deltaTime = deltaClock.restart();
        sf::Time updateStart = deltaClock.getElapsedTime();

        sf::Event event;
        while(_window->pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed: {
                    _running = false;
                    break;
                }
                case sf::Event::Resized: {
                    windowWidth = event.size.width;
                    windowHeight = event.size.height;
                    break;
                }
                default: {
                    break;
                }

            }
            ImGui::SFML::ProcessEvent(*_window, event);
        }
        ImGui::SFML::Update(*_window, deltaTime);


        sf::Time updateEnd = deltaClock.getElapsedTime();
        updateTime = updateEnd-updateStart;
        
        ImGui::SetNextWindowPos(ImVec2(-1, 0));
        ImGui::SetNextWindowSize(ImVec2(windowWidth+5, 20));
        bool active = true;
        std::string information = std::string("Delta time: " + std::to_string(deltaTime.asSeconds()) +
        " FPS: " + std::to_string(1.f/deltaTime.asSeconds()) +
        " Frame Time: " + std::to_string(frameTime.asSeconds()) +
        " Update Time: " + std::to_string(updateTime.asSeconds()) +
        " Render Time: " + std::to_string(renderTime.asSeconds())
        );
        ImGui::Begin("Information", &active, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::Text(information.c_str());
        ImGui::End();

        _window->clear(sf::Color(0, 0, 0));
        sf::Time renderStart = deltaClock.getElapsedTime();
        ImGui::SFML::Render(*_window);
        _window->display();
        
        sf::Time renderEnd = deltaClock.getElapsedTime();
        sf::Time targetTime = sf::seconds(1.f/60.f-0.0000021);
        sf::Time checkTime = deltaClock.getElapsedTime();
        frameTime = checkTime;
        while (checkTime < targetTime) {
            checkTime = deltaClock.getElapsedTime();
        }
    }
    _window->close();
}