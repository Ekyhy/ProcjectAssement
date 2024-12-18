#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Status {HONORER,PNS};

struct guru
{
    char nama[50];
    int NIP;
    enum Status status;

    union
    {
        int kerja;
        int cuti;
    }infoKinerja;

    union 
    {
        float gajiTotal;
        float gajiTunjangan;
        float gajiPotongan;
    }infoGaji;
    
};

int main(){
    int jumlahGuru;
    printf ("Masukkan Jumlah Guru : ");
    scanf ("%d",&jumlahGuru);
    //Segmen integrasi ke dalam struct
    struct guru *daftarGuru =(struct guru*) malloc(jumlahGuru * sizeof(struct guru));

    //Segmen Input Data Guru Honorer atau PNS
    for (int i = 0; i < jumlahGuru; i++)
    {
       printf("\nMasukkan data guru ke-%d\n",i+1);
       getchar();
       printf("NAMA :");
       scanf("%[^\n]",&daftarGuru[i].nama);

       printf("NIP :");
       scanf("%d",&daftarGuru[i].NIP);

       printf("STATUS PEGAWAI (0 = HONORER || 1 = PNS) : ");
       scanf("%d",(int*)&daftarGuru[i].status);

       if (daftarGuru[i].status == HONORER)
       {
        printf("Masukkan jumlah hari kerja :");
        scanf("%d",&daftarGuru[i].infoKinerja.kerja);
        daftarGuru[i].infoGaji.gajiTunjangan = 50000; //declare nilai gaji tunjangan guru Honorer
        daftarGuru[i].infoGaji.gajiTotal = daftarGuru[i].infoKinerja.kerja*daftarGuru[i].infoGaji.gajiTunjangan; 
       } else if (daftarGuru[i].status == PNS){
        printf("Masukkan jumlah hari cuti :");
        scanf("%d",&daftarGuru[i].infoKinerja.cuti);
        daftarGuru[i].infoGaji.gajiPotongan = 30000;
        int hariKerja = 20 - daftarGuru[i].infoKinerja.cuti;
        daftarGuru[i].infoGaji.gajiTotal = hariKerja*100000 - daftarGuru[i].infoKinerja.cuti*daftarGuru[i].infoGaji.gajiPotongan;
       } else {
        printf("Input tidak valid");
       }  
    }
    

    //Segemen Output dari data Input
    printf("\nDaftar Guru :");
    printf("\n==================================");
    for (int i = 0; i < jumlahGuru; i++)
    {
        printf("\n Nama : %s",daftarGuru[i].nama);
        printf("\n NIP  : %d",daftarGuru[i].NIP);
        
        if (daftarGuru[i].status == HONORER)
        {
            printf("\n Jumlah hari aktif kerja : %d",daftarGuru[i].infoKinerja.kerja);
            printf("\n Tunjangan per hari kerja : 50.0000");
        } else {
            printf("\n Jumlah hari non-aktif kerja : %d",daftarGuru[i].infoKinerja.cuti);
            printf("\n Potongan gaji per hari cuti : 30.0000");
        }
        printf("\n Gaji total yang di peroleh %.2f",daftarGuru[i].infoGaji.gajiTotal);
        printf("\n==================================");
    }
    
    free(daftarGuru);
    return 0;
}

