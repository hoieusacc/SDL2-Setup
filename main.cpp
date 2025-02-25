// sử dung SDL và IO cơ bả
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

//kích thước cố định của cửa sổ
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 750;

// enum là kiểu dữ liệu lưu trữ các biến có giá trị cố định
// lưu trữ các phím nhấn
enum KeyPress {
    KEY_PRESS_DEFAULT,
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_RIGHT,
    KEY_PRESS_LEFT,
    KEY_PRESS_TOTAL
};

// khởi tạo cửa sổ
SDL_Window *window = NULL;

// tạo bề mặt cửa sổ
SDL_Surface *ScreenSurface = NULL;

// hình ảnh tương ứng với phím bấm
SDL_Surface *KeyPressSurface[KEY_PRESS_TOTAL];

// bề mặt cửa sổ hiện tại
SDL_Surface *CurrentSurface = NULL;

//khởi động SDL và tạo cửa sổ
bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initalized %s\n" << SDL_GetError() << endl;
        success = false;
    } else {
        window = SDL_CreateWindow("Nguyen Minh Duc", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if (window == NULL) {
            cout << "Window could not initalized %s\n" << SDL_GetError() << endl;
            success = false;
        } else {
            ScreenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

// tải hình ảnh bề mặt
SDL_Surface *loadSurface(string path) {
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        cout << "Unable to load " << "SDL_ERROR:" << IMG_GetError() << endl;
    }
    return loadedSurface;
}


// hàm tải ảnh mặc định, trái, phải, trên, dưới
bool loadMedia() {
    bool success = true;
    // tải hình ảnh mặc định (giao diện chính)
    KeyPressSurface[KEY_PRESS_DEFAULT] = loadSurface("1de.JPG");
    if ( KeyPressSurface[KEY_PRESS_DEFAULT] == NULL) {
        cout << "Failed to load default image" << endl;
        success = false;
    }
    KeyPressSurface[KEY_PRESS_UP] = loadSurface("1de.JPG");
    if ( KeyPressSurface[KEY_PRESS_UP] == NULL) {
        cout << "Failed to load default image" << endl;
        success = false;
    }
    KeyPressSurface[KEY_PRESS_DOWN] = loadSurface("1de.JPG");
    if ( KeyPressSurface[KEY_PRESS_DOWN] == NULL) {
        cout << "Failed to load default image" << endl;
        success = false;
    }
    KeyPressSurface[KEY_PRESS_RIGHT] = loadSurface("1de.JPG");
    if ( KeyPressSurface[KEY_PRESS_RIGHT] == NULL) {
        cout << "Failed to load default image" << endl;
        success = false;
    }
    KeyPressSurface[KEY_PRESS_LEFT]= loadSurface("1de.JPG");
    if ( KeyPressSurface[KEY_PRESS_LEFT] == NULL) {
        cout << "Failed to load default image" << endl;
        success = false;
    }
     
    return success;
} 

void close() {
    for (int i = 0; i < KEY_PRESS_TOTAL; i = i+1) {
        SDL_FreeSurface(KeyPressSurface[i]);
        KeyPressSurface[i] = NULL;
    }

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

int main(int argv, char *argc[]) {
    if (init() == false) {
        cout << "Unable to start" << endl;
    } else {
        if (loadMedia() == false) {
            cout << "unable to start" << endl;
        } else {
            bool quit = false;
            SDL_Event e;
            CurrentSurface = KeyPressSurface[KEY_PRESS_DEFAULT];
            //khi người dùng khởi động cửa sổ
            while (quit == false) {
                // khi các yêu cầu người dùng khác với mặc định dựa vào kho lữu trữ sự kiện
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                        // xử lí sự kiện phím bấm
                    } else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                CurrentSurface = KeyPressSurface[KEY_PRESS_UP];
                                break;
                            case SDLK_DOWN:
                                CurrentSurface = KeyPressSurface[KEY_PRESS_DOWN];
                                break;
                            case SDLK_RIGHT:
                                CurrentSurface = KeyPressSurface[KEY_PRESS_RIGHT];
                                break;
                            case SDLK_LEFT:
                                CurrentSurface = KeyPressSurface[KEY_PRESS_LEFT];
                                break;
                            default:
                                CurrentSurface = KeyPressSurface[KEY_PRESS_DEFAULT];
                                break;
                        }
                    }
                }
                // Sau khi xử lí xong các yêu cầu từ người dùng thì đẩy hình ảnh lên màn hình
                SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
                // Cập nhật lên cửa sổ
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    
    close();
    return 0;
} 

// Nguyễn Minh Đức