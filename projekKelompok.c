 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Aspirasi {
    int id;
    char nama[50];
    char isi[200];
};

struct Aspirasi *dataAspirasi = NULL; 
int jumlahAspirasi = 0;               

const char *NAMA_FILE = "aspirasi.txt";



void clearInput();
void tambahAspirasi();
void lihatSemuaAspirasi();
void cariAspirasiByNama();
void sortAspirasiByNama();
void hapusAspirasiByID();
void tampilkanMenu();
void simpanKeFile();      
void loadDariFile();     



void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}



void simpanKeFile() {
    FILE *f = fopen(NAMA_FILE, "w");

    for (int i = 0; i < jumlahAspirasi; i++) {
        fprintf(f, "%d|%s|%s\n",
                dataAspirasi[i].id,
                dataAspirasi[i].nama,
                dataAspirasi[i].isi);
    }

    fclose(f);
}

void loadDariFile() {
    FILE *f = fopen(NAMA_FILE, "r");

    char line[400];

    while (fgets(line, sizeof(line), f)) {

        line[strcspn(line, "\n")] = '\0';

        struct Aspirasi a;
        char *token;

        token = strtok(line, "|");
        a.id = atoi(token);

        token = strtok(NULL, "|");
        strncpy(a.nama, token, sizeof(a.nama));
        a.nama[sizeof(a.nama) - 1] = '\0';

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


//===========================
//FITUR MENAMBAHKAN ASPIRASI
//===========================

void tambahAspirasi() {
    struct Aspirasi a;

    a.id = jumlahAspirasi + 1;

    printf("\n=== Tambah Aspirasi Warga ===\n");
    printf("Nama : ");
    clearInput();
    fgets(a.nama, sizeof(a.nama), stdin);
    a.nama[strcspn(a.nama, "\n")] = '\0';

    printf("Isi aspirasi:\n");
    fgets(a.isi, sizeof(a.isi), stdin);
    a.isi[strcspn(a.isi, "\n")] = '\0';

    struct Aspirasi *temp =
        (struct Aspirasi *)realloc(dataAspirasi, (jumlahAspirasi + 1) * sizeof(struct Aspirasi));

    dataAspirasi = temp;
    dataAspirasi[jumlahAspirasi] = a;
    jumlahAspirasi++;

    simpanKeFile();

    printf("Aspirasi tersimpan dengan ID %d.\n", a.id);
}


//=================================
//FITUR MENAMPILKAN SEMUA ASPIRASI
//=================================
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


//===================================
//FITUR MENCARI ASPIRASI SESUAI NAMA
//===================================
void cariAspirasiByNama() {
    if (jumlahAspirasi == 0) {
        printf("\nBelum ada aspirasi.\n");
        return;
    }

    char namaCari[50];
    printf("\n=== Cari Aspirasi berdasarkan Nama ===\n");
    printf("Masukkan nama : ");
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

//=======================================
//FITUR MENGURUTKAN ASPIRASI SESUAI NAMA
//=======================================
void sortAspirasiByNama() {
    if (jumlahAspirasi == 0) {
        printf("\nBelum ada aspirasi.\n");
        return;
    }

    printf("\nMengurutkan aspirasi berdasarkan nama (A-Z)...\n");

    for (int i = 0; i < jumlahAspirasi - 1; i++) {
        for (int j = 0; j < jumlahAspirasi - 1 - i; j++) {
            if (strcmp(dataAspirasi[j].nama, dataAspirasi[j + 1].nama) > 0) {
                struct Aspirasi temp = dataAspirasi[j];
                dataAspirasi[j] = dataAspirasi[j + 1];
                dataAspirasi[j + 1] = temp;
            }
        }
    }

    simpanKeFile();

    printf("Data aspirasi berhasil diurutkan.\n");
}


//====================
//FITUR HAPUS ASPIRASI
//====================

  void hapusAspirasiByID() {
    if (jumlahAspirasi == 0) {
        printf("\nBelum ada aspirasi.\n");
        return;
    }

    int idHapus;
    printf("\n=== Hapus Aspirasi ===\n");
    printf("Masukkan ID aspirasi yang ingin dihapus: ");
    scanf("%d", &idHapus);

    int index = -1;
    for (int i = 0; i < jumlahAspirasi; i++) {
        if (dataAspirasi[i].id == idHapus) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Aspirasi dengan ID %d tidak ditemukan.\n", idHapus);
        return;
    }

    for (int i = index; i < jumlahAspirasi - 1; i++) {
        dataAspirasi[i] = dataAspirasi[i + 1];
    }
    jumlahAspirasi--;

    simpanKeFile();

    printf("Aspirasi dengan ID %d telah dihapus.\n", idHapus);
}

void tampilkanMenu() {
    printf("\n=====================================\n");
    printf("       SISTEM ASPIRASI WARGA RT\n");
    printf("=====================================\n");
    printf("1. Tambah Aspirasi Warga\n");
    printf("2. Lihat Semua Aspirasi\n");
    printf("3. Cari Aspirasi berdasarkan Nama\n");
    printf("4. Urutkan Aspirasi berdasarkan Nama (A-Z)\n");
    printf("5. Hapus Aspirasi berdasarkan ID\n");
    printf("6. Keluar\n");
    printf("Pilih menu (1-6): ");
}

int main() {
    int pilihan;

    loadDariFile();

    do {
        tampilkanMenu();
        if (scanf("%d", &pilihan) != 1) {
            printf("Input harus berupa angka.\n");
            clearInput();
            continue;
        }

        switch (pilihan) {
            case 1:
                tambahAspirasi();
                break;
            case 2:
                lihatSemuaAspirasi();
                break;
            case 3:
                cariAspirasiByNama();
                break;
            case 4:
                sortAspirasiByNama();
                break;
            case 5:
                hapusAspirasiByID();
                break;
            case 6:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 6);

    simpanKeFile();
    free(dataAspirasi);

    return 0;
}
