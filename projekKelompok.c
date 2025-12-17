#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================================
// Struct & Variabel Global
// ==================================
struct Aspirasi {
    int id;
    char nama[50];
    char isi[200];
};

struct Aspirasi *dataAspirasi = NULL; // array dinamis
int jumlahAspirasi = 0;               // banyak data yang terpakai

const char *NAMA_FILE = "aspirasi.txt";

// ==================================
// PROTOTYPE FUNGSI
// ==================================
void clearInput();
void tambahAspirasi();
void lihatSemuaAspirasi();
void cariAspirasiByNama();
void sortAspirasiByNama();
void hapusAspirasiByID();
void tampilkanMenu();
void simpanKeFile();      // NEW: simpan ke file
void loadDariFile();      // NEW: baca dari file

// ==================================
// Utility: bersihkan buffer input
// ==================================	
void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // buang karakter
    }
}

// ==================================
// File Processing: Simpan ke File
// ==================================
void simpanKeFile() {
    FILE *f = fopen(NAMA_FILE, "w");

    // Format: id|nama|isi
    for (int i = 0; i < jumlahAspirasi; i++) {
        fprintf(f, "%d|%s|%s\n",
                dataAspirasi[i].id,
                dataAspirasi[i].nama,
                dataAspirasi[i].isi);
    }

    fclose(f);
    // printf("Data berhasil disimpan ke file.\n"); // kalau mau kasih info tiap kali simpan
}