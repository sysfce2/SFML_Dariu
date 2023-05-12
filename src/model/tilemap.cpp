#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    jetpack.init(4, 0.5f, "./src/asset/image/Jetpack.png", sf::IntRect(0, 0, 32, 32), true);
    banana.init(17, 0.5f, "./src/asset/image/Items/Fruits/Bananas.png", sf::IntRect(0, 0, 32, 32), true);
    portalP.init(0, 0.f, "./src/asset/image/PortalP.png", sf::IntRect(0, 0, 32, 32), true);
    portalQ.init(0, 0.f, "./src/asset/image/PortalQ.png", sf::IntRect(0, 0, 32, 32), true);
    trophy.init(8, 0.2f, "./src/asset/image/Items/Checkpoints/End/End (Pressed) (64x64).png", sf::IntRect(0, 0, 64, 64), false);
}

std::string Tilemap::map[H] = {};

void Tilemap::load_from_file(int phase) {
    this->load_map_from_file(phase);
    this->load_texture_from_file(phase);
}
void Tilemap::load_map_from_file(int phase) {
    this->mapfile = "./src/resource/map_" + to_string(phase) + ".dtm";
    std::string lines = Tools::get_lines_from_dtm(this->mapfile, "", "\n");
    std::stringstream ss(lines);
    std::string line;
    int i = 0;

    while (getline(ss, line, '\n')) {
        this->W = line.length();
        this->map[i] = line;
        i++;
    }
}
void Tilemap::load_texture_from_file(int phase) {
    std::string terrain = Tools::get_lines_from_dtm("./src/resource/map_" + to_string(phase) + ".dtm", "[TERRAIN]", "");
    if (terrain.empty()) terrain = "Terrain";

    terrain_tex.loadFromFile("./src/asset/image/" + terrain + "/Terrain (16x16).png");
    terrain2_tex.loadFromFile("./src/asset/image/" + terrain + "/Terrain (32x32).png");
    door_tex.loadFromFile("./src/asset/image/door.png");

    ground.setTexture(terrain_tex);
    ground.setTextureRect(sf::IntRect(96, 0, 32, 32));

    ground_ora.setTexture(terrain_tex);
    ground_ora.setTextureRect(sf::IntRect(272, 64, 32, 32));

    ground_door_closed.setTexture(door_tex);
    ground_door_closed.setTextureRect(sf::IntRect(0, 0, 32, 32));

    ground_door_opened.setTexture(door_tex);
    ground_door_opened.setTextureRect(sf::IntRect(32, 0, 32, 32));

    ground_left.setTexture(terrain2_tex);
    ground_left.setTextureRect(sf::IntRect(0, 0, 32, 32));
    ground_mid.setTexture(terrain2_tex);
    ground_mid.setTextureRect(sf::IntRect(32, 0, 32, 32));
    ground_right.setTexture(terrain2_tex);
    ground_right.setTextureRect(sf::IntRect(64, 0, 32, 32));

    ground_left2.setTexture(terrain2_tex);
    ground_left2.setTextureRect(sf::IntRect(0, 32, 32, 32));
    ground_mid2.setTexture(terrain2_tex);
    ground_mid2.setTextureRect(sf::IntRect(32, 32, 32, 32));
    ground_right2.setTexture(terrain2_tex);
    ground_right2.setTextureRect(sf::IntRect(64, 32, 32, 32));

    start_tex.loadFromFile("./src/asset/image/Start.png");
    start.setTexture(start_tex);
    start.setTextureRect(sf::IntRect(0, 0, 32, 32));

    fire_tex.loadFromFile("./src/asset/image/fire1.png");
    fire.setTexture(fire_tex);
    fire.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

bool Tilemap::isPortal(int i, int j) {
    return map[i][j] == 'P' || map[i][j] == 'Q';
};
int Tilemap::getPortalNumber(int i, int j) {
    char charNum = map[i][j + 1];
    int intNum = (int)charNum;
    return intNum;
};

point Tilemap::getMapOppositPortal(int i, int j) {
    char currentLetter = map[i][j];
    int currentNumber = this->getPortalNumber(i, j);

    point op;

    // Search opossit side
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            if (this->map[i][j] != currentLetter) {
                if (currentNumber == this->getPortalNumber(i, j)) {
                    op.i = i;
                    op.j = j;
                    op.l = this->map[i][j];
                    op.found = true;
                }
            }
        }
    }
    return op;
};

void Tilemap::update() {
    std::string e;
    for (auto& plataform : plataforms) {
        e = map[(int)plataform->pos.top / 32][(int)plataform->pos.left / 32];
        if (e == "<") {
            plataform->velocity.x = -plataform->vel_step;
            plataform->velocity.y = 0.0f;
        } else if (e == ">") {
            plataform->velocity.x = plataform->vel_step;
            plataform->velocity.y = 0.0f;
        } else if (e == "^") {
            plataform->velocity.x = 0.0f;
            plataform->velocity.y = -plataform->vel_step;
        } else if (e == "V") {
            plataform->velocity.x = 0.0f;
            plataform->velocity.y = plataform->vel_step;
        }
        plataform->update();
    }
}

void Tilemap::draw(sf::RenderWindow* w) {
    for (int i{}; i < H; ++i) {
        for (int j{}; j < W; ++j) {
            if (map[i][j] == ' ') {
                continue;
            } else if (map[i][j] == '@') {
                start.setPosition(j * 32, i * 32);
                w->draw(start);
            } else if (map[i][j] == '.') {
                banana.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'J') {
                jetpack.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'T') {
                trophy.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'A') {
                ground_left.setPosition(j * 32, i * 32);
                w->draw(ground_left);
            } else if (map[i][j] == 'B') {
                ground_mid.setPosition(j * 32, i * 32);
                w->draw(ground_mid);
            } else if (map[i][j] == 'C') {
                ground_right.setPosition(j * 32, i * 32);
                w->draw(ground_right);
            } else if (map[i][j] == 'D') {
                ground_left2.setPosition(j * 32, i * 32);
                w->draw(ground_left2);
            } else if (map[i][j] == 'E') {
                ground_mid2.setPosition(j * 32, i * 32);
                w->draw(ground_mid2);
            } else if (map[i][j] == 'F') {
                ground_right2.setPosition(j * 32, i * 32);
                w->draw(ground_right2);
            } else if (map[i][j] == 'b') {
                ground_ora.setPosition(j * 32, i * 32);
                w->draw(ground_ora);
            } else if (map[i][j] == 'R') {
                fire.setTextureRect(sf::IntRect(((int)i_fire % q_fire) * 32, 0, 32, 32));
                fire.setPosition(j * 32, i * 32);
                w->draw(fire);
            } else if (map[i][j] == 'P') {
                portalP.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'Q') {
                portalQ.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'X') {
                ground_door_closed.setPosition(j * 32, i * 32);
                w->draw(ground_door_closed);
            } else if (map[i][j] == 'x') {
                ground_door_opened.setPosition(j * 32, i * 32);
                w->draw(ground_door_opened);
            }
        }
    }
    jetpack.anime(sf::IntRect(jetpack.getFrame() * 32, 0, 32, 32), 1);
    banana.anime(sf::IntRect(banana.getFrame() * 32, 0, 32, 32), 1);
    trophy.anime(sf::IntRect(trophy.getFrame() * 64, 0, 64, 64), 1);

    i_fire += 0.5f;

    for (auto& plataform : plataforms) {
        plataform->draw(w);
    }
}
// void Tilemap::load_from_file(int phase) {
//     int i;
//     string line;

//     ifstream map_file("./src/resource/map_" + to_string(phase) + ".dtm");

//     i = 0;
//     while (getline(map_file, line)) {
//         this->W = line.length();
//         this->map[i] = line;
//         i++;
//     }
//     map_file.close();
// }

void Tilemap::load_plataforms() {
    plataforms.clear();
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            if (this->map[i][j] == 'M') {
                Plataform* plataform = new Plataform();
                plataform->pos.top = i * 32;
                plataform->pos.left = j * 32;
                plataforms.push_back(plataform);
            }
        }
    }
}

void Tilemap::replaceAll(char a, char b) {
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            if (this->map[i][j] == a) {
                this->map[i][j] = b;
            }
        }
    }
}

void Tilemap::clear() {
    this->door_opened = false;
}
point Tilemap::getTileFromPixel(int x, int y, int height, int width) {
    point coord;
    coord.i = (int)y / height;
    coord.j = (int)x / width;
    coord.l = this->map[coord.i][coord.j];
    return coord;
}
void Tilemap::edit(sf::RenderWindow* w, sf::Event event, sf::View view) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->edit_current_char = 'A';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        this->edit_current_char = 'B';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        this->edit_current_char = 'b';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        this->edit_current_char = 'C';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->edit_current_char = 'D';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        this->edit_current_char = 'E';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        this->edit_current_char = 'F';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        this->edit_current_char = 'H';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        this->edit_current_char = 'P';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        this->edit_current_char = 'Q';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        this->edit_current_char = 'R';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        this->edit_current_char = 'J';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        this->edit_current_char = 'T';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        this->edit_current_char = 'Y';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        this->edit_current_char = 'X';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        this->edit_current_char = 'Z';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
        this->edit_current_char = '.';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        this->edit_current_char = ' ';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        this->edit_save();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*w);
        sf::Vector2f worldPos = w->mapPixelToCoords(mousePos);
        point p = this->getTileFromPixel(worldPos.x, worldPos.y, 32, 32);
        this->map[p.i][p.j] = this->edit_current_char;
    }
};
void Tilemap::edit_click(){

};
void Tilemap::edit_save() {
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            std::cout << this->map[i][j];
        }
        std::cout << endl;
    }
};
