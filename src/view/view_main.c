#include <SDL2/SDL.h>

int init_open_gl(LocalizationArray* localization_group) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        get_loc_str(localization_group, "window_title"),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Define a rectangle for the button
    SDL_Rect buttonRect = {280, 200, 80, 60};

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // If a mouse button was pressed, check if it was within the button's rectangle
                if (event.button.x >= buttonRect.x && event.button.x <= (buttonRect.x + buttonRect.w) &&
                    event.button.y >= buttonRect.y && event.button.y <= (buttonRect.y + buttonRect.h)) {
                    // The button was clicked, do something
                    printf(get_loc_str(localization_group, "button_press_text"));
                    printf("\n");
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render the button
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
        SDL_RenderFillRect(renderer, &buttonRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}