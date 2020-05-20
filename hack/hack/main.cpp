#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>

//using namespace sf;

//========CONTROL VALUES==================================================================
unsigned long long CORRECT_HASH_VALUE = 11879186655936601130;
const long int FILE_SIZE = 168;
//========CONTROL VALUES END==============================================================



//========PROGRAMM OPTIONS================================================================
const char* input_file_name = "S:/hack/HACK.com";
const char* output_file_name = "S:/hack/HACKED.com";
const int MUSIC_LEVEL = 5;
const long int BUFFER_SIZE = FILE_SIZE + 1;
//========PROGRAMM OPTIONS END============================================================


struct Picture {
    sf::Texture texture;
    sf::Sprite sprite;

    Picture(const char* picture_src_name, int x_coord, int y_coord) {
        texture.loadFromFile(picture_src_name);
        sprite.setTexture(texture);
        sprite.setPosition(x_coord, y_coord);
    }
};


bool file_check_and_read(FILE*, char*);

void hack_in_buffer(char*);


int main() {

    sf::RenderWindow window( sf::VideoMode(1280,720),"Sooper pooper crack hack by Anonymous");

//========TEXTURES AND SPRAYS============================================================
    Picture hacked_wallpaper("hacker_wallpaper_accept.jpg", 0, 0);

    Picture not_correct_wallpaper("hacker_wallpaper_file_is_not_correct.jpg", 0, 0);

    Picture wallpaper("hacker_wallpaper.jpg", 0, 0);

    Picture hack_button("hackaem.png", 50, 50);
//========TEXTURES AND SPRAYS END========================================================

//========MUSIC==========================================================================
    sf::Music main_theme;

    if (main_theme.openFromFile("InTheEnd.ogg")) {
        main_theme.setLoop(true);
        main_theme.SoundSource::setVolume(MUSIC_LEVEL);
        main_theme.play();
    }
//========MUSIC END======================================================================

//========MENUS============================================================

    sf::Event event;
    bool button_is_active = false;

    while (window.isOpen()) {
        while (window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();
        window.clear();
        window.draw(wallpaper.sprite);
        if (!sf::IntRect(50, 50, 294, 64).contains(sf::Mouse::getPosition(window))) {
            hack_button.sprite.setColor(sf::Color::White);
            button_is_active = false;
        }
        else {
            hack_button.sprite.setColor(sf::Color::Blue);
            button_is_active = true;
        }

        window.draw(hack_button.sprite);

        window.display();

        if (button_is_active && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            break;

    }

//========MENUS END========================================================
    if (window.isOpen()) {

        char* buffer = (char*)calloc(BUFFER_SIZE, 1);
        FILE* stream = fopen (input_file_name, "r");
        bool file_is_correct = file_check_and_read(stream, buffer);


        if (!file_is_correct) {
            while (window.isOpen()) {
                while (window.pollEvent(event))
                    if(event.type == sf::Event::Closed)
                        window.close();

                window.draw(not_correct_wallpaper.sprite);
                window.display();
            }
        }
        else {
            hack_in_buffer(buffer);
            stream = fopen(output_file_name, "w");
            fwrite(buffer, FILE_SIZE, 1, stream);
            while (window.isOpen()) {
                while (window.pollEvent(event))
                    if(event.type == sf::Event::Closed)
                        window.close();

                window.draw(hacked_wallpaper.sprite);
                window.display();
            }
        }
        free(buffer);
    }

    return 0;
}



void hack_in_buffer(char* buffer) {
    buffer[0] = 0xEB;
    buffer[1] = 0x1D;
}



bool file_check_and_read(FILE* stream, char* buffer) {

    if (!stream)
        return false;

    long int file_siz = 0;
    fseek (stream, 0, SEEK_END);
    file_siz = ftell (stream);
    fseek (stream, 0, SEEK_SET);

    if (FILE_SIZE != file_siz)
        return false;

    fread(buffer, FILE_SIZE, 1, stream);

    unsigned long long hash_val = 0;
    int base = 17;
    unsigned long long factor = 1;
    for (int i = 0; i < FILE_SIZE; ++i) {
        hash_val += buffer[i] * factor;
        factor *= base;
    }

    if (hash_val != CORRECT_HASH_VALUE)
        return false;

    return true;
}
