#include "InterfazGrafica.h"

SDL_Window *ventana = nullptr;

bool iniciar() {
    bool success = true;

    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        success = false;
    } else {
        // Setear filtrado de texturas a lineal
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Advertencia: No se pudo habilitar el fitrado de texturas lineal\n");
        }

        // Crear ventana
        ventana = SDL_CreateWindow("Pacalgo2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VENTANA_ANCHO,
                                   VENTANA_ALTO, SDL_WINDOW_SHOWN);
        if (ventana == nullptr) {
            printf("Error al crear la ventana: %s\n", SDL_GetError());
            success = false;
        } else {
            // Crear renderizador para la ventana
            renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
            if (renderizador == nullptr) {
                printf("Error al crear el renderizador: %s\n", SDL_GetError());
                success = false;
            } else {
                // Inicializar color de renderizador
                SDL_SetRenderDrawColor(renderizador, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return success;
}

bool cargarArchivos() {
    bool success = true;

    // Cargar los sprites desde la imagen
    if (!texturaSprites.cargarDesdeArchivo("../gui/imagenes/sprites.bmp", renderizador)) {
        printf("Fallo al cargar los sprites\n");
        success = false;
    } else {
        int i = 0;
        for (int y = 0; y < 144; y += 16) {
            for (int x = 0; x < 96; x += 16) {
                sprites[i].x = x;
                sprites[i].y = y;
                sprites[i].w = 16;
                sprites[i].h = 16;
                ++i;
            }
        }
    }

    // Cargar los numeros chicos desde la imagen
    if (!texturaNumerosChicos.cargarDesdeArchivo("../gui/imagenes/numeroschicos.bmp", renderizador)) {
        printf("Fallo al cargar los numeros chicos\n");
        success = false;
    } else {
        int i = 0;
        for (int x = 0; x < 180; x += 18) {
            numerosChicos[i].x = x;
            numerosChicos[i].y = 0;
            numerosChicos[i].w = 18;
            numerosChicos[i].h = 18;
            ++i;
        }
    }

    // Cargar los numeros grandes desde la imagen
    if (!texturaNumerosGrandes.cargarDesdeArchivo("../gui/imagenes/numerosgrandes.bmp", renderizador)) {
        printf("Fallo al cargar los numeros grandes\n");
        success = false;
    } else {
        int i = 0;
        for (int x = 0; x < 360; x += 36) {
            numerosGrandes[i].x = x;
            numerosGrandes[i].y = 0;
            numerosGrandes[i].w = 36;
            numerosGrandes[i].h = 36;
            ++i;
        }
    }

    // Cargar las letras chicas desde la imagen
    if (!texturaLetrasChicas.cargarDesdeArchivo("../gui/imagenes/letraschicas.bmp", renderizador)) {
        printf("Fallo al cargar las letras chicas\n");
        success = false;
    } else {
        int i = 0;
        for (int x = 0; x < 468; x += 18) {
            letrasChicas[i].x = x;
            letrasChicas[i].y = 0;
            letrasChicas[i].w = 18;
            letrasChicas[i].h = 18;
            ++i;
        }
    }

    // Cargar las letras grandes desde la imagen
    if (!texturaLetrasGrandes.cargarDesdeArchivo("../gui/imagenes/letrasgrandes.bmp", renderizador)) {
        printf("Fallo al cargar las letras grandes\n");
        success = false;
    } else {
        int i = 0;
        for (int x = 0; x < 936; x += 36) {
            letrasGrandes[i].x = x;
            letrasGrandes[i].y = 0;
            letrasGrandes[i].w = 36;
            letrasGrandes[i].h = 36;
            ++i;
        }
    }

    // Cargar el marco desde la imagen
    if (!texturaMarco.cargarDesdeArchivo("../gui/imagenes/marco.bmp", renderizador)) {
        printf("Fallo al cargar el marco\n");
        success = false;
    } else {
        marco.x = 0;
        marco.y = 0;
        marco.w = 200;
        marco.h = 600;
    }

    // Cargar el fondoGano desde la imagen
    if (!texturaFondoGano.cargarDesdeArchivo("../gui/imagenes/fondogano.bmp", renderizador)) {
        printf("Fallo al cargar el fondoGano\n");
        success = false;
    } else {
        fondoGano.x = 0;
        fondoGano.y = 0;
        fondoGano.w = 600;
        fondoGano.h = 600;
    }

    // Cargar el fondoIniciar desde la imagen
    if (!texturaFondoIniciar.cargarDesdeArchivo("../gui/imagenes/fondoiniciar.bmp", renderizador)) {
        printf("Fallo al cargar el fondoIniciar\n");
        success = false;
    } else {
        fondoIniciar.x = 0;
        fondoIniciar.y = 0;
        fondoIniciar.w = 600;
        fondoIniciar.h = 600;
    }

    // Cargar el fondoJugando desde la imagen
    if (!texturaFondoJugando.cargarDesdeArchivo("../gui/imagenes/fondojugando.bmp", renderizador)) {
        printf("Fallo al cargar el fondoJugando\n");
        success = false;
    } else {
        fondoJugando.x = 0;
        fondoJugando.y = 0;
        fondoJugando.w = 600;
        fondoJugando.h = 600;
    }

    // Cargar el fondoPerdio desde la imagen
    if (!texturaFondoPerdio.cargarDesdeArchivo("../gui/imagenes/fondoperdio.bmp", renderizador)) {
        printf("Fallo al cargar el fondoPerdio\n");
        success = false;
    } else {
        fondoPerdio.x = 0;
        fondoPerdio.y = 0;
        fondoPerdio.w = 600;
        fondoPerdio.h = 600;
    }

    return success;
}

void cerrar() {
    // Liberar las imagenes cargadas
    texturaSprites.liberar();
    texturaNumerosGrandes.liberar();
    texturaNumerosChicos.liberar();
    texturaLetrasGrandes.liberar();
    texturaLetrasChicas.liberar();
    texturaMarco.liberar();
    texturaFondoIniciar.liberar();
    texturaFondoJugando.liberar();
    texturaFondoGano.liberar();
    texturaFondoPerdio.liberar();

    // Destruir la ventana
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    ventana = nullptr;
    renderizador = nullptr;

    // Salir de los subsistemas de SDL
    SDL_Quit();
}
