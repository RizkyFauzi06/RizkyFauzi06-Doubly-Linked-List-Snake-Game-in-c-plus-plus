#include <iostream>
#include <raylib.h>

using namespace std;
// cell untuk menggambar gridnya dan ukuran pixel
const int cellsize = 30;
const int cellcount = 25;

// center dan color untuk posisi teks dan warnanya
int centerX = (cellcount * cellsize) / 2;
int centerY = (cellcount * cellsize) / 2; 
Color green = {173, 204, 96, 255};
Color darkgreen = {43, 51, 24, 255};

// Struct gerbong sebagai node linked list
struct Gerbong{
    int x,y;
    Gerbong* next;
    Gerbong* prev;

};

// class food untuk makanan dalam game ini, dalam konteks ini adalah apple / apel
class Food{
    public:
    int x = 5;  // posisi awal x apel
    int y = 6; // posisi awal y apel
    Texture2D GambarApel; // untuk dapat mengeload texturea gambar apel

    Food(){
        GambarApel = LoadTexture("Apel.png"); // mwngload gambar apel dari file
    }

    ~Food() {
        UnloadTexture(GambarApel); // mengunload gambar apple dari program jika telah di tutup
    }
    void Draw(){
            DrawTexture(GambarApel, x * cellsize, y *cellsize, WHITE); // function draw untuk mengambar apel nya
        }

    void RespawnAcak(){ // setelah dimakan maka apel nya akan respawn secara acak
        x = int(GetRandomValue(0, cellcount - 1));
        y = int(GetRandomValue(0,cellcount - 1));
    }
};

// class snake 
class Snake{
    public:
    Gerbong* head; // membuat node kepala untuk snake
    Gerbong* tail; // membuat node ekor untuk snake
    Vector2 ArahSekarang; // menggunakan vector 2d untuk menentukan arah tujuan dari head sehingga bisa dirubah dan merotasi gamabrnya nanti
    bool scorenaik = false; // digubnakan untuk function score naik saat memakan apel
    bool died = false; // untuk mengecek apakah mati atau tidak
    int highscore = 0; // untuk mencetak nilai high score dalam permainan
    int score = 0; // untuk mengecek score saat ini

    // untuk load texture dari gambar
    Texture2D GambarKepala; 
    Texture2D GambarBadan;
    Texture2D GambarEkor;
    
    Snake(){ // default consturctor snake
        head = new Gerbong(); // membuat node awal dari snake
        head->x = 10; // posisi x awal
        head->y = 10; // posisi y awal
        head->next = nullptr; // node selanjutnya belum ada
        head->prev = nullptr; // node sebelumnya belum ada

        tail = head; // karena baru kepaala maka tail nya saat ini di anggap sama
        ArahSekarang = {-1,0}; // arah default

        // laod texture
        GambarKepala = LoadTexture("Head.png");
        GambarBadan = LoadTexture("Body.png");
        GambarEkor = LoadTexture("Tail.png");
    }

    ~Snake() { // uncostructor ? agar load texture snake nya hilang setelah di close
        UnloadTexture(GambarKepala);
        UnloadTexture(GambarBadan);
        UnloadTexture(GambarEkor);
    }

    //function move untuk pergerakan snake dengan parameter class food
     void Move(Food& apple){
        //mengatur pergerakan / arah dari snakenya
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) ArahSekarang= {1,0};
        if (IsKeyPressed(KEY_LEFT)  || IsKeyPressed(KEY_A)) ArahSekarang = {-1,0};
        if (IsKeyPressed(KEY_DOWN)  || IsKeyPressed(KEY_S)) ArahSekarang = {0,1};
        if (IsKeyPressed(KEY_UP)    || IsKeyPressed(KEY_W)) ArahSekarang = {0,-1};

        // target adalah arah yang dituju dari posisi head saat ini
        int target_x = head->x + ArahSekarang.x;
        int target_y = head->y + ArahSekarang.y;
        //membuat gerbong kepala baru untuk posisi target x dan y dengan tujuan membuat efek bergerak 
        Gerbong* kepalaBaru = new Gerbong();
        kepalaBaru->x = target_x;
        kepalaBaru->y = target_y;

        kepalaBaru->next = head;
        kepalaBaru->prev = nullptr; 

        head->prev = kepalaBaru; // membuat head awal (head1) menjadi node ke 2 lalu merubah headbaru(head2) jadi node pertama
        head = kepalaBaru; // head 2 / kepala baru menjadi head saat ini.
        

        if(head->x == apple.x && head->y == apple.y){ // logika memakan apel
            apple.RespawnAcak(); // memanggil function apel respawn acak
            scorenaik = true; // scorenya naik
        // tail nya tidak di hapus  
        }else{
            Gerbong* ekorlama = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete ekorlama; // menghapus tail sehingga ukuran nya sama dan ada efek bergerak nya.
            scorenaik = false; 
        }

     }

     // function mengecek apakah kena batas
     bool checkHitwall(){
        if(head->x < 0 || head->y < 0){
            died = true;
        }else if(head-> x >= cellcount || head->y >= cellcount){
            died = true;
        }else{
            died = false;
        }

        if(died){
            return true;
        }else{
            return false;
        }
     }

     // mengecek apakah kena diri sendiri
    bool checkHitSelf(){
        Gerbong* temp = head->next;
        while(temp != nullptr){
            if(head->x == temp->x && head->y == temp->y){
                return true;
            }else{
                temp = temp->next;
            }
        }

        return false;
    }
    // function mereset jika mati
     void reset(){
        Gerbong* temp;
        Gerbong* temp2;
        temp = head;
        while(temp != nullptr){
            temp2 = temp -> next;
            delete temp;
            temp = temp2;
        }
        head = new Gerbong();
        head->next = nullptr;
        head->prev = nullptr;
        head->x = GetRandomValue(1,cellcount - 1);
        head->y = GetRandomValue(1,cellcount - 1);
        tail = head;
        scorenaik = false;
        score = 0;
        died = false;
     }

     // function draw snake nya
     void Draw(){
        Gerbong* temp;
        temp = head;
        while(temp != nullptr){
            int posisiX;
            int posisiY;
            posisiX = temp->x * cellsize;
            posisiY = temp->y * cellsize;
            int dx = 0;
            int dy = 0;

            // mengecek apakah temp saat ini adalah si head atau bukan, jika iya maka dx,dy nya adalah arah saat ini,
            // jika bukan maka dx dy nya adalah node sebelumnya yang dikurang dengan nilai saat ini untuk tau arah peputaran nya nanti.
            if(temp == head){
                dx = ArahSekarang.x;
                dy = ArahSekarang.y;
            }else{
                dx = temp->prev->x - temp->x;
                dy = temp->prev->y - temp->y;
            }

            // membuat arah perputaran
            float rotasi = 0.0f;
            if(dx == 1){rotasi =180.0f;}
            if(dx == -1){rotasi = 0.0f;}
            if(dy == -1){rotasi = 90.0f;}
            if(dy == 1){rotasi = 270.0f;}
            
            Rectangle sourceRec = {0.0f,0.0f,float(cellsize),float(cellsize)};
            Rectangle destRec = {(float)posisiX + (cellsize / 2.0f), 
                (float)posisiY + (cellsize / 2.0f), 
                (float)cellsize, 
                (float)cellsize
            };
            Vector2 origin = {cellsize / 2.0f, cellsize / 2.0f};

            if(temp == head){
                DrawTexturePro(GambarKepala, sourceRec, destRec, origin, rotasi, WHITE);
            } else if(temp->next == nullptr){
                DrawTexturePro(GambarEkor, sourceRec, destRec, origin, rotasi, WHITE);
            } else {
                DrawTexturePro(GambarBadan, sourceRec, destRec, origin, rotasi, WHITE);
            }
            
            temp = temp->next;
        }
    }
};

void gambargrid(){
    Color warnagaris = {43,51,24,58};

    for(int i = 0; i< cellcount; i++){
        DrawLine(i * cellsize, 0, i * cellsize, cellcount * cellsize, warnagaris); // vertival
        DrawLine(0, i* cellsize, cellcount * cellsize, i * cellsize, warnagaris); // horizontal
    }
}





int main() {
    InitWindow(cellcount * cellsize, cellcount * cellsize, "raylib [core] example - basic window");\
    InitAudioDevice(); //  biar ada suara nya game nya
    SetTargetFPS(10); 
    
    Sound suaraMakan = LoadSound("Eat.mp3"); //  nge load suara game
    Sound suaraMati = LoadSound("GameOver.mp3");
    
    Food apel;
    Snake ular;
    bool gameover = false;

    // Main game loop
    while (!WindowShouldClose())   
    {
         BeginDrawing();
            ClearBackground(green);
            gambargrid();
        if(!gameover){
            ular.Move(apel);
            if(ular.checkHitwall() || ular.checkHitSelf()){ // cek mati kena wall atau diri sendiri
                PlaySound(suaraMati); // play audio nya
                if(ular.score > ular.highscore){
                    ular.highscore = ular.score;
                }
                gameover = true;
            };
            
            if(ular.scorenaik){ // score naik
                PlaySound(suaraMakan);
                ular.score++;
            }
            DrawText(TextFormat("SCORE: %i", ular.score), 10, 10, 20, darkgreen); 
            DrawText(TextFormat("HI-SCORE: %i", ular.highscore), cellcount*cellsize - 160, 10, 20, darkgreen);
                ular.Draw();
                apel.Draw();
        }else{

            const char* gameOver = "GAME OVER";
            const char* restart = "Press R to Restart";
            DrawText(
                gameOver,
                centerX - MeasureText(gameOver, 40) / 2,
                centerY - 80,
                40,
                RED
            );

            DrawText(
                restart,
                centerX - MeasureText(restart, 20) / 2,
                centerY - 30,
                20,
                DARKGRAY
            );

            DrawText(
                TextFormat("Score: %i", ular.score),
                centerX - MeasureText(TextFormat("Score: %i", ular.score), 20) / 2,
                centerY + 10,
                20,
                BLACK
            );

            DrawText(
                TextFormat("High Score: %i", ular.highscore),
                centerX - MeasureText(TextFormat("High Score: %i", ular.highscore), 20) / 2,
                centerY + 40,
                20,
                BLACK
            );
            if(IsKeyPressed(KEY_R)){
                    apel.RespawnAcak();
                    ular.reset();
                    gameover = false;
                }
            }
            EndDrawing();
    }

        UnloadSound(suaraMakan);
        UnloadSound(suaraMati);
        CloseAudioDevice();
        CloseWindow();  
        return 0;
}