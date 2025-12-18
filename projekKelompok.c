 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struct & Variabel Global

struct Aspirasi {
    int id;
    char nama[50];
    char isi[200];
};

struct Aspirasi *dataAspirasi = NULL; // array dinamis
int jumlahAspirasi = 0;               // banyak data yang terpakai

const char *NAMA_FILE = "aspirasi.txt";


// PROTOTYPE FUNGSI

void clearInput();
void tambahAspirasi();
void lihatSemuaAspirasi();
void cariAspirasiByNama();
void sortAspirasiByNama();
void hapusAspirasiByID();
void tampilkanMenu();
void simpanKeFile();      // NEW: simpan ke file
void loadDariFile();      // NEW: baca dari file


// Utility: bersihkan buffer input

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // buang karakter
    }
}


// File Processing: Simpan ke File

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

void loadDariFile() {
    FILE *f = fopen(NAMA_FILE, "r");

    char line[400];

    while (fgets(line, sizeof(line), f)) {
        // hapus newline di akhir
        line[strcspn(line, "\n")] = '\0';

        struct Aspirasi a;
        char *token;

        // id
        token = strtok(line, "|");
        a.id = atoi(token);

        // nama
        token = strtok(NULL, "|");
        strncpy(a.nama, token, sizeof(a.nama));
        a.nama[sizeof(a.nama) - 1] = '\0';

        // isi
        token = strtok(NULL, "|");
        strncpy(a.isi, token, sizeof(a.isi));
        a.isi[sizeof(a.isi) - 1] = '\0';
        

        struct Aspirasi *temp =
            (struct Aspirasi *)realloc(dataAspirasi, (jumlahAspirasi + 1) * sizeof(struct Aspirasi));
        if (temp == NULL) {
            printf("Memori penuh saat load data.\n");
            fclose(f);
        }
        dataAspirasi = temp;
        dataAspirasi[jumlahAspirasi] = a;
        jumlahAspirasi++;
    }

    fclose(f);
}

// Fitur 1: Tambah Aspirasi

void tambahAspirasi() {
    struct Aspirasi a;

    a.id = jumlahAspirasi + 1;

    printf("\n=== Tambah Aspirasi Warga ===\n");
    printf("Nama (boleh 'Anonim'): ");
    clearInput();
    fgets(a.nama, sizeof(a.nama), stdin);
    a.nama[strcspn(a.nama, "\n")] = '\0';

    printf("Isi aspirasi:\n");
    fgets(a.isi, sizeof(a.isi), stdin);
    a.isi[strcspn(a.isi, "\n")] = '\0';

    // tambah kapasitas array dinamis (naik 1 elemen)
    struct Aspirasi *temp =
        (struct Aspirasi *)realloc(dataAspirasi, (jumlahAspirasi + 1) * sizeof(struct Aspirasi));

    dataAspirasi = temp;
    dataAspirasi[jumlahAspirasi] = a;
    jumlahAspirasi++;

    // simpan ke file setiap kali ada penambahan
    simpanKeFile();

    printf("Aspirasi tersimpan dengan ID %d.\n", a.id);
}

// Fitur 2: Lihat Semua Aspirasi

void lihatSemuaAspirasi() {
    if (jumlahAspirasi == 0) {
        printf("\nBelum ada aspirasi.\n");
        return;
    }

    printf("\n=== Daftar Semua Aspirasi Warga ===\n");
    for (int i = 0; i < jumlahAspirasi; i++) {
        printf("--------------------------------------\n");
        printf("ID       : %d\n", dataAspirasi[i].id);
        printf("Nama     : %s\n", dataAspirasi[i].nama);
        printf("Aspirasi : %s\n", dataAspirasi[i].isi);
    }
    printf("--------------------------------------\n");
}

int main(){
    return 0;
}

// ==================================
// Fitur 3: Cari Aspirasi berdasarkan Nama (Searching)
// ==================================
void cariAspirasiByNama() {
    if (jumlahAspirasi == 0) {
        printf("\nBelum ada aspirasi.\n");
        return;
    }

    char namaCari[50];
    printf("\n=== Cari Aspirasi berdasarkan Nama ===\n");
    printf("Masukkan nama (atau 'Anonim'): ");
    clearInput();
    fgets(namaCari, sizeof(namaCari), stdin);
    namaCari[strcspn(namaCari, "\n")] = '\0';

    int found = 0;

       for (int i = 0; i < jumlahAspirasi; i++) {
        if (strcmp(dataAspirasi[i].nama, namaCari) == 0) {
            if (!found) {
                printf("\nAspirasi yang ditemukan:\n");
            }
            printf("--------------------------------------\n");
            printf("ID       : %d\n", dataAspirasi[i].id);
            printf("Nama     : %s\n", dataAspirasi[i].nama);
            printf("Aspirasi : %s\n", dataAspirasi[i].isi);
            found = 1;
        }
    }

    if (!found) {
        printf("Tidak ada aspirasi dari '%s'.\n", namaCari);
    } else {
        printf("--------------------------------------\n");
    }
}
