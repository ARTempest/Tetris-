#include "../include/music.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

static Mix_Music* music = nullptr;

bool initMusic(const char* filepath) {
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    std::cout << "SDL audio init failed: " << SDL_GetError() << "\n";
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cout << "SDL_mixer init failed: " << Mix_GetError() << "\n";
    return false;
  }

  music = Mix_LoadMUS(filepath);

  if (!music) {
    std::cout << "Failed to load music: " << Mix_GetError() << '\n';
    return false;
  }

  Mix_PlayMusic(music, -1);
  return true;
}

void cleanupMusic() {
  if (music) {
    Mix_FreeMusic(music);
    music = nullptr;
  }
  Mix_CloseAudio();
  SDL_Quit();
    // Only call SDL_Quit() if you're not using SDL for other things like video
}
