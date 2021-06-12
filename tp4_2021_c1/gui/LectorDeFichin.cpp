#include "LectorDeFichin.h"

aed2_Fichin crearFichin() {
    Nat largo = 37;
    Nat alto = 37;
    Coordenada inicio, llegada;
    set<Coordenada> paredes, fantasmas, chocolates;
    string rutaArchivo = "../gui/mapa/mapa.txt";
    vector<string> mapaLeido;
    string line;
    ifstream myfile(rutaArchivo);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            mapaLeido.push_back(line);
        }
        myfile.close();
    } else {
        cout << "No se pudo abrir el archivo\n";
    }
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < largo; ++x) {
            switch (mapaLeido[y][x]) {
                case 'I':
                    inicio = {x + 1, largo - y};
                    break;
                case 'L':
                    llegada = {x + 1, largo - y};
                    break;
                case 'P':
                    paredes.insert({x + 1, largo - y});
                    break;
                case 'F':
                    fantasmas.insert({x + 1, largo - y});
                    break;
                case 'C':
                    chocolates.insert({x + 1, largo - y});
                    break;
            }
        }
    }
    return {largo, alto, inicio, llegada, paredes, fantasmas, chocolates};
}
