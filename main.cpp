#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

sf::Image imgtex;

int getnumber(const char *askfor);

int main(int argc, char *argv[]){

    int width, height, pixelsmax;
    bool cornersonly = false;
    if(argc < 2){
        width = getnumber("width: ");
        height = getnumber("height: ");
        pixelsmax = ((float)(width*height)/100) * getnumber("max pixels %: ");
        if(getnumber("go to corners (0/1): ") == 1)
            cornersonly = true;
    }
    else{
        if(argc < 4){
            cout << "USAGE: dla [WIDTH] [HEIGHT] [MAX PIXELS %]\n";
            return 1;
        }
        try{
            width = stoi(argv[1]);
            height = stoi(argv[2]);
            pixelsmax = ((float)(width*height)/100) * stoi(argv[3]);
        }
        catch(invalid_argument){
            cout << "ERROR, INVALID ARGUMENTS\nUSAGE: dla [WIDTH] [HEIGHT] [MAX PIXELS %]\n";
            return 1;
        }
    }


    int pixelcount = 0;
    imgtex.create(width, height, sf::Color::Black);
    srand(clock());
    imgtex.setPixel(width/2, height/2, sf::Color::White);
    sf::Color pxcolor;
    sf::Vector2 pxpos(0, 0);
    
    while (pixelcount < pixelsmax){
        if(pixelcount < pixelsmax/4){
            pxcolor = sf::Color::Red;
        }
        else if(pixelcount < pixelsmax/2){
            pxcolor = sf::Color::Green;
        }
        else if(pixelcount < (pixelsmax/4)*3){
            pxcolor = sf::Color::Blue;
        }
        else{
            pxcolor = sf::Color::Magenta;
        }
        int spawncorner = random()%4;
        if(!cornersonly){
            switch (spawncorner){
            case 0:
                pxpos = sf::Vector2((int)(random()%width), 0); 
                break;
            case 1:
                pxpos = sf::Vector2(width-1, (int)(random()%height));
                break;
            case 2:
                pxpos = sf::Vector2((int)(random()%width), height-1);
                break;
            case 3:
                pxpos = sf::Vector2(0, (int)(random()%height));
                break;
            }
        }
        else{
            switch (spawncorner){
            case 0:
                pxpos = sf::Vector2(0, 0);
                break;
            case 1:
                pxpos = sf::Vector2(width-1, 0);
                break;
            case 2:
                pxpos = sf::Vector2(width-1, height-1);
                break;
            case 3:
                pxpos = sf::Vector2(0, height-1);
                break;
            }  
        }
        while (true){
            if(pxpos.x > 0 && imgtex.getPixel(pxpos.x-1, pxpos.y) != sf::Color::Black
            || pxpos.x < width-1 && imgtex.getPixel(pxpos.x+1, pxpos.y) != sf::Color::Black

            ||pxpos.y > 0 && imgtex.getPixel(pxpos.x, pxpos.y-1) != sf::Color::Black
            ||pxpos.y < height-1 && imgtex.getPixel(pxpos.x, pxpos.y+1) != sf::Color::Black
            ){
                imgtex.setPixel(pxpos.x, pxpos.y, pxcolor);
                pixelcount++;
                cout << "hit x: " << pxpos.x << " y: " << pxpos.y << endl << pixelsmax-pixelcount << " pixels to go (" << pixelcount/(float)(pixelsmax)*100 <<"%)" << endl;
                break;
            }
            int rnum = random()%4;
            if(rnum == 0 && pxpos.x != 0){
                pxpos.x--;
                continue;
            }
            if(rnum == 1 && pxpos.x < width-1){
                pxpos.x++;
                continue;
            }
            if(rnum == 2 && pxpos.y != 0){
                pxpos.y--;
                continue;
            }
            if(rnum == 3 && pxpos.y < height-1){
                pxpos.y++;
            }
        }
        
    }
    imgtex.saveToFile("result.png");
}

int getnumber(const char *askfor){
    string inp;
    while(true){
        cout << askfor;
        cin >> inp;
        try{
            return stoi(inp);
        }
        catch(invalid_argument){
            cout << "error, try again\n";
        }
    }
}