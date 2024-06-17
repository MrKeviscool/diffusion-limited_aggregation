#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

const int WIDTH  = 300, HEIGHT = 300, PIXELSMAX = (WIDTH*HEIGHT)/5;

sf::Image imgtex;

int main(){
    int pixelcount = 0;
    imgtex.create(WIDTH, HEIGHT, sf::Color::Black);
    srand(clock());
    imgtex.setPixel(WIDTH/2, HEIGHT/2, sf::Color::White);
    sf::Color pxcolor;
    sf::Vector2 pxpos(0, 0);
    
    while (pixelcount < PIXELSMAX){
        if(pixelcount < PIXELSMAX/4){
            pxcolor = sf::Color::Red;
        }
        else if(pixelcount < PIXELSMAX/2){
            pxcolor = sf::Color::Green;
        }
        else if(pixelcount < (PIXELSMAX/4)*3){
            pxcolor = sf::Color::Blue;
        }
        else{
            pxcolor = sf::Color::Magenta;
        }
        int spawncorner = random()%4;
        switch (spawncorner){
        case 0:
            // pxpos = sf::Vector2(0, 0);
            pxpos = sf::Vector2((int)(random()%WIDTH), 0); //WORK IN PROGRESS. KEEP DOING!!!!!!
            break;
        case 1:
            // pxpos = sf::Vector2(WIDTH-1, 0);
            pxpos = sf::Vector2(WIDTH-1, (int)(random()%HEIGHT));
            break;
        case 2:
            pxpos = sf::Vector2((int)(random()%WIDTH), HEIGHT-1);
            break;
        case 3:
            pxpos = sf::Vector2(0, (int)(random()%HEIGHT));
            break;
        }

        while (true){
            if(pxpos.x > 0 && imgtex.getPixel(pxpos.x-1, pxpos.y) != sf::Color::Black
            || pxpos.x < WIDTH-1 && imgtex.getPixel(pxpos.x+1, pxpos.y) != sf::Color::Black

            ||pxpos.y > 0 && imgtex.getPixel(pxpos.x, pxpos.y-1) != sf::Color::Black
            ||pxpos.y < HEIGHT-1 && imgtex.getPixel(pxpos.x, pxpos.y+1) != sf::Color::Black
            ){
                imgtex.setPixel(pxpos.x, pxpos.y, pxcolor);
                pixelcount++;
                cout << "hit x: " << pxpos.x << " y: " << pxpos.y << endl << PIXELSMAX-pixelcount << " pixels to go (" << pixelcount/(float)(PIXELSMAX)*100 <<"%)" << endl;
                break;
            }
            int rnum = random()%4;
            if(rnum == 0 && pxpos.x != 0){
                pxpos.x--;
                continue;
            }
            if(rnum == 1 && pxpos.x < WIDTH-1){
                pxpos.x++;
                continue;
            }
            if(rnum == 2 && pxpos.y != 0){
                pxpos.y--;
                continue;
            }
            if(rnum == 3 && pxpos.y < HEIGHT-1){
                pxpos.y++;
            }
        }
        
    }
    imgtex.saveToFile("result.png");
}
