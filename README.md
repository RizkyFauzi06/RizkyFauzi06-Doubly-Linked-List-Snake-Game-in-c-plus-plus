# Retro Snake Game - C++ Custom Engine

A classic Snake game developed in C++ using Raylib for rendering. Rather than relying on conventional array-based body management, this project implements a custom **Doubly Linked List** to represent the snake dynamically in memory. This approach enables efficient snake movement with constant-time insertion and deletion operations.


## Gameplay

![Gameplay Demo](screenshoot\Gameplay.gif)

## Architecture Highlights

### Doubly Linked List-Based Snake Representation

The snake is modeled as a chain of linked nodes (`struct Gerbong`). Each movement step creates a new head node and removes the tail node, eliminating the need for array shifting and reducing unnecessary iteration overhead.

### Manual Memory Management

The project uses low-level dynamic memory allocation through `new` and `delete`. Careful pointer management and a custom reset routine ensure that allocated nodes are properly released when restarting or ending the game.

### Dynamic Sprite Rotation

The orientation of the snake's head, body, and tail is calculated automatically based on the relative positions of neighboring nodes. Rotation angles are derived from Cartesian coordinate differences, allowing sprites to face the correct direction without hardcoded states.

### Separation of Logic and Rendering

Game state updates are processed independently from rendering operations. This separation keeps gameplay logic organized and maintains a clear distinction between simulation and visual presentation.

## Tech Stack

* **Language:** C++
* **Graphics & Audio Library:** Raylib
* **Memory Management:** Dynamic Memory Allocation (Pointers)
* **Data Structure:** Doubly Linked List

## How to Run

### Prerequisites

Make sure the Raylib development environment is properly installed and configured.

### Installation

1. Clone the repository:

   ```bash
   git clone <repository-url>
   ```

2. Navigate to the project directory:

   ```bash
   cd SnakeGame
   ```

3. Compile the source code:

   ```bash
   g++ main.cpp -o main.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
   ```

4. Run the executable:

   ```bash
   .\main.exe
   ```

Running the executable from the project directory ensures that game assets such as textures and audio files are loaded correctly.

## Controls

| Key           | Action                  |
| ------------- | ----------------------- |
| W / A / S / D | Move Snake              |
| Arrow Keys    | Move Snake              |
| R             | Restart After Game Over |

---

Developed as a learning project focused on C++ memory management, data structures, and 2D game programming fundamentals.


# Retro Snake Game - Engine C++ Kustom

Sebuah permainan Snake klasik yang dikembangkan menggunakan C++ dan Raylib sebagai library rendering. Berbeda dengan implementasi Snake pada umumnya yang menggunakan array untuk menyimpan tubuh ular, proyek ini memanfaatkan **Doubly Linked List** sebagai struktur data utama sehingga pergerakan ular dapat dilakukan secara lebih efisien melalui operasi penambahan dan penghapusan node secara dinamis.

## Sorotan Arsitektur

### Representasi Ular Menggunakan Doubly Linked List

Tubuh ular direpresentasikan sebagai rangkaian node (`struct Gerbong`) yang saling terhubung. Setiap kali ular bergerak, program membuat node baru sebagai kepala (head) dan menghapus node ekor (tail), sehingga tidak diperlukan proses pergeseran elemen seperti pada array.

### Manajemen Memori Manual

Proyek ini menggunakan alokasi memori dinamis melalui `new` dan `delete`. Pengelolaan pointer dilakukan secara langsung, dilengkapi dengan mekanisme reset khusus untuk membersihkan seluruh node yang telah dialokasikan saat permainan diulang atau berakhir.

### Rotasi Sprite Dinamis

Orientasi kepala, badan, dan ekor ular dihitung secara otomatis berdasarkan posisi node-node yang berdekatan. Sudut rotasi diperoleh dari selisih koordinat kartesius antar node sehingga sprite selalu menghadap ke arah pergerakan yang benar tanpa memerlukan banyak kondisi khusus.

### Pemisahan Logika dan Rendering

Logika permainan diproses secara terpisah dari proses rendering. Pendekatan ini menjaga struktur kode tetap rapi serta memisahkan simulasi game dari tampilan visual yang ditampilkan ke layar.

## Teknologi yang Digunakan

* **Bahasa Pemrograman:** C++
* **Library Grafis & Audio:** Raylib
* **Manajemen Memori:** Dynamic Memory Allocation (Pointer)
* **Struktur Data:** Doubly Linked List

## Cara Menjalankan

### Prasyarat

Pastikan lingkungan pengembangan Raylib telah terpasang dan dikonfigurasi dengan benar.

### Langkah Instalasi

1. Clone repository:

   ```bash
   git clone <repository-url>
   ```

2. Masuk ke direktori proyek:

   ```bash
   cd SnakeGame
   ```

3. Kompilasi source code:

   ```bash
   g++ main.cpp -o main.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
   ```

4. Jalankan program:

   ```bash
   .\main.exe
   ```

Menjalankan executable dari direktori proyek diperlukan agar seluruh aset seperti gambar dan audio dapat dimuat dengan benar.

## Kontrol

| Tombol        | Fungsi                          |
| ------------- | ------------------------------- |
| W / A / S / D | Menggerakkan Ular               |
| Tombol Arah   | Menggerakkan Ular               |
| R             | Memulai Ulang Setelah Game Over |

---

Proyek ini dibuat sebagai sarana pembelajaran mengenai manajemen memori di C++, struktur data linked list, serta dasar-dasar pengembangan game 2D.

