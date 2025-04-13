#include "render.h"
#include "../game/game.h"

Render::Render(Game* g) {
  game = g;
}

void Render::loop() {
  while (!glfwWindowShouldClose(game->window)) {
    // Input
    game->processInput();
    
    // Rendering Commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Calls and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(game->window);
  }
}
