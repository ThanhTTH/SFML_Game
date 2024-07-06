#include "state_game.hpp"
#include <map>

std::map<sf::Keyboard::Key, Direction> map_direaction {
    {sf::Keyboard::Left, Direction::Left},
    {sf::Keyboard::Right, Direction::Right},
};

StateGame::StateGame(StateManager* l_stateManager) 
    : BaseState(l_stateManager), 
    m_prevTime(0.0f),
    m_moving_state(false),
    m_isStop(false),
    m_score(0) {

}
//
StateGame::~StateGame(){
    for(auto& enemy : m_enemies) {
        delete enemy;
    }
    //
    for(auto& rocket : m_rockets) {
        delete rocket;
    }
}
//
void StateGame::Oncreate() {
    SetTransparent(true);
    sf::RenderWindow* window = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    std::string working_directory = Utilitis::GetWorkingDirectory();
    std::string hero_assets_path = working_directory + "Assets/graphics/hero_left.png";
    sf::Vector2f l_hero_position = sf::Vector2f(window->getSize().x * 0.25f, window->getSize().y * 0.5f);
    float l_hero_speed = 200.0f;
    m_hero.Initialize(hero_assets_path);
    m_hero.setPosition(l_hero_position);
    m_hero.setSpeed(l_hero_speed);
    //
    std::string sky_assets_path = working_directory + "Assets/graphics/sky.png";
    m_sky.Initialize(sky_assets_path);
    //

    std::string bg_assets_path = working_directory + "Assets/graphics/bg.png";
    m_background.Initialize(bg_assets_path);
    //
    std::string font_path = working_directory + "Assets/fonts/arial.ttf";
    m_font.loadFromFile(font_path);
    m_text.setFont(m_font);
    m_text.setString("Score : 0");
    m_text.setCharacterSize(25);
    m_text.setFillColor(sf::Color::Red);
    sf::FloatRect score_bounder = m_text.getLocalBounds();
    m_text.setOrigin(score_bounder.width / 2, score_bounder.height / 2);
    m_text.setPosition(sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y * 0.10f));
    //
    EventManager* event_manager = m_stateManager->GetContext()->m_event_manager;
    event_manager->AddCallback(StateType::Game, "Key_Left_Press", &StateGame::KeyLeftPress, this);
    event_manager->AddCallback(StateType::Game, "Key_Right_Press", &StateGame::KeyRightPress, this);
    event_manager->AddCallback(StateType::Game, "Key_Left_Up", &StateGame::KeyLeftUp, this);
    event_manager->AddCallback(StateType::Game, "Key_Right_Up", &StateGame::KeyRightUp, this);
    event_manager->AddCallback(StateType::Game, "Key_Up_Press", &StateGame::KeyUpPress, this);
    event_manager->AddCallback(StateType::Game, "Mouse_Left", &StateGame::MouseClick, this);
    event_manager->AddCallback(StateType::Game, "Key_Escape", &StateGame::KeyEXIT, this);
}
//
void StateGame::RocketGender() {
    std::string rocket_assets_path = Utilitis::GetWorkingDirectory() + "Assets/graphics/rocket.png";
    Rocket* rocket = new Rocket();
    sf::Vector2f l_rocket_position = sf::Vector2f(m_hero.getSprite().getPosition().x + m_hero.getSprite().getTexture()->getSize().x/2, m_hero.getSprite().getPosition().y + 10);
    rocket->Initialize(rocket_assets_path);
    rocket->setPosition(l_rocket_position);
    float l_rocket_speed = 400.0f;
    rocket->setSpeed(l_rocket_speed);
    m_rockets.push_back(rocket);
}
//
void StateGame::OnDestroy() {
    EventManager* event_manager = m_stateManager->GetContext()->m_event_manager;
    event_manager->RemoveCallback(StateType::Game, "Key_Left_Press");
    event_manager->RemoveCallback(StateType::Game, "Key_Right_Press");
    event_manager->RemoveCallback(StateType::Game, "Key_Up_Press");
    event_manager->RemoveCallback(StateType::Game, "Key_Left_Up");
    event_manager->RemoveCallback(StateType::Game, "Key_Right_Up");
    event_manager->RemoveCallback(StateType::Game, "Mouse_Left");
    event_manager->RemoveCallback(StateType::Game, "Key_Escape");
}
//
void StateGame::Activate() {
    m_isStop = false;
}
//
void StateGame::Deactivate() {
    m_moving_state = false;
    m_isStop = true;
}
//
void StateGame::Update(const sf::Time& l_time) {
    
    float distance = l_time.asSeconds();
    sf::RenderWindow *window = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    m_currentTime += distance;
    //Spam enemy objects
    if ((m_currentTime >= (m_prevTime + 1.125f) && !m_isStop)) {
        EnemyGender();
        m_prevTime = m_currentTime;
    }
    //
    for (int i = 0; i < m_enemies.size(); i++) {
        Enemy *enemy = m_enemies[i];
        enemy->Update(distance);
        //If rocket object moved to the end of left size
        if (enemy->getSprite().getPosition().x < 0)
        {
            m_enemies.erase(m_enemies.begin() + i);
            delete (enemy);
        }
    }
    //Update moving state of rocket object
    for (int i = 0; i < m_rockets.size(); i++) {
        Rocket *rocket = m_rockets[i];
        rocket->Update(distance);
        if (rocket->getSprite().getPosition().x > window->getSize().x)
        {
            m_rockets.erase(m_rockets.begin() + i);
            delete (rocket);
        }
    }
    //
    for (int i = 0; i < m_enemies.size(); i++)
    {
        for (int j = 0; j < m_rockets.size(); j++)
        {
            Enemy *enemy = m_enemies[i];
            Rocket *rocket = m_rockets[j];
            //Checking collision
            if (CollisionChecking(rocket->getSprite(), enemy->getSprite()))
            {
                //Display scrore
                m_score++;
                std::string final_score = "Score : " + std::to_string(m_score);
                m_text.setString(final_score);
                sf::FloatRect score_bounder = m_text.getLocalBounds();
                m_text.setOrigin(score_bounder.width / 2, score_bounder.height / 2);
                m_text.setPosition(sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y * 0.10f));
                //Remove impacted objects
                m_enemies.erase(m_enemies.begin() + i);
                m_rockets.erase(m_rockets.begin() + j);
                delete (enemy);
                delete (rocket);
            }
        }
    }
    // Check there is object moving
    if (m_moving_state) {
        m_hero.Move(distance);
    }
    //Update state of hero characters
    m_hero.Update(distance);
}
//
void StateGame::Draw() {
    sf::RenderWindow* window = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_sky.getSprite());
    window->draw(m_background.getSprite());
    window->draw(m_hero.getSprite());
    //Draw enemy
    for(Enemy* enemy : m_enemies) {
        window->draw(enemy->getSprite());
    }
    //Draw rocket
    for(Rocket* rocket : m_rockets) {
        window->draw(rocket->getSprite());
    }
    window->draw(m_text);
}
//
void StateGame::MouseClick(EventDetails* l_event_details) {
    RocketGender();
}
//
void StateGame::KeyLeftPress(EventDetails* l_event_details) {
    m_hero.SetDirection(map_direaction.at(sf::Keyboard::Key(l_event_details->m_keyCode)));
    m_moving_state = true;
}
//
void StateGame::KeyRightPress(EventDetails* l_event_details) {
    m_hero.SetDirection(map_direaction.at(sf::Keyboard::Key(l_event_details->m_keyCode)));
    m_moving_state = true;
}
//
void StateGame::KeyUpPress(EventDetails* l_event_details) {
    m_hero.Jump(750.0f);
}
//
void StateGame::KeyLeftUp(EventDetails* l_event_details) {
    m_moving_state = false;
}
//
void StateGame::KeyRightUp(EventDetails* l_event_details) {
    m_moving_state = false;
}
//
void StateGame::EnemyGender() {
    int randLoc = rand() % 3;
    sf::Vector2f enemyPos;
    sf::RenderWindow* window = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    float speed;
    switch (randLoc)
    {
    case 0:
        enemyPos = sf::Vector2f(window->getSize().x, window->getSize().y * 0.75f);
        speed = -400.0f;
        break;
    case 1:
        enemyPos = sf::Vector2f(window->getSize().x, window->getSize().y * 0.60f);
        speed = -550.0f;
        break;
    case 2:
        enemyPos = sf::Vector2f(window->getSize().x, window->getSize().y * 0.40f);
        speed = -650.0f;
        break;
    default:
        std::cout << "Incorerect y value" << std::endl;
        break;
    }
    std::string enemy_assets_path = Utilitis::GetWorkingDirectory() + "Assets/graphics/enemy.png";
    Enemy *enemy = new Enemy();
    enemy->Initialize(enemy_assets_path);
    enemy->setPosition(enemyPos);
    enemy->setSpeed(speed);
    m_enemies.push_back(enemy);
}
//
bool StateGame::CollisionChecking(const sf::Sprite &object, const sf::Sprite &distance) {
    return object.getGlobalBounds().intersects(distance.getGlobalBounds());
}
//
void StateGame::KeyEXIT(EventDetails* l_event_details) {
    m_stateManager->SwitchTo(StateType::MainMenu);
}