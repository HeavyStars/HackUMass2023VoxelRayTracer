#include "window.hpp"
Window::Window(int w, int h, std::string title) :
renderImage(1920, 1080) {
    _window = new sf::RenderWindow(sf::VideoMode(w, h), title);
    _window->setFramerateLimit(288);
    ImGui::SFML::Init(*_window);
    _running = false;
    windowWidth = w;
    windowHeight = h;

    _renderView.reset(sf::FloatRect(0, 0, 1920, 1080));
    float yPos = std::max((1-(((1080.f/1920.f)*(float)windowWidth)/(float)windowHeight))/2.f, 0.f);
    float viewHeight = (yPos > 0) ? ((1080.f/1920.f)*(float)windowWidth)/(float)windowHeight : 1.f;
    _renderView.setViewport(sf::FloatRect(0.f, yPos, 1.f, viewHeight));
}

Window::~Window(){
    delete _window;
    _window = NULL;
}

void Window::run(){

    _running = true;
    while(_running){

        deltaTime = deltaClock.restart();

        //UPDATE WINDOW-------------------------------------------------------------------------------------------
        sf::Time updateStart = deltaClock.getElapsedTime();

        sf::Event event;
        while(_window->pollEvent(event)) {
            switch(event.type){
                case sf::Event::Closed: {
                    _running = false;
                    break;
                }
                case sf::Event::Resized: {
                    windowWidth = event.size.width;
                    windowHeight = event.size.height;
                    float yPos = std::max((1-(((1080.f/1920.f)*(float)windowWidth)/(float)windowHeight))/2.f, 0.f);
                    float viewHeight = (yPos > 0) ? ((1080.f/1920.f)*(float)windowWidth)/(float)windowHeight : 1.f;
                    _renderView.setViewport(sf::FloatRect(0.f, yPos, 1.f, viewHeight));
                    break;
                }
                default: {
                    break;
                }

            }
            ImGui::SFML::ProcessEvent(*_window, event);
        }
        ImGui::SFML::Update(*_window, deltaTime);

        //IMGUI UPDATES
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
        //END IMGUI UPDATES

        renderImage.update(deltaTime);
        sf::Time updateEnd = deltaClock.getElapsedTime();
        updateTime = updateEnd-updateStart;
        //END UPDATE WINDOW---------------------------------------------------------------------------------------

        //START RENDERING-----------------------------------------------------------------------------------------
        sf::Time renderStart = deltaClock.getElapsedTime();
        _window->clear(sf::Color(0, 0, 0));

        const sf::Texture & scene = renderImage.render();
        sf::Sprite drawScene(scene);
        _window->setView(_renderView);
        _window->draw(drawScene);
        _window->setView(_window->getDefaultView());

        ImGui::SFML::Render(*_window);
        _window->display();
        
        sf::Time renderEnd = deltaClock.getElapsedTime();
        renderTime = renderEnd-renderStart;
        //END RENDER TO WINDOW------------------------------------------------------------------------------------


        //FPS ENFORCE STRICT TIME TO 60FPS
        sf::Time targetTime = sf::seconds(1.f/144.f-0.0000021);
        sf::Time checkTime = deltaClock.getElapsedTime();
        frameTime = checkTime;
        while (checkTime < targetTime) {
            checkTime = deltaClock.getElapsedTime();
        }
        
    }
    _window->close();
}