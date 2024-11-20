#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct 
{
    char jump[3];
    char FSName[8]; //name
    char Chunk[53]; //must be 0x00
    long offsetPart; // sector address
    long sizeVol; // size of total volume in sector
    int FATOffset; // sector address of 1st FAT
    int FATlen; // size of FAT in sectors
    int ClusterHeapOffset; // sector adress of the Data Region
    int ClusterCount; //cantidad de clusters in the Cluster Heap
    int RootDirFirstCluster; // Cluster address of the root directory
    int VSN; // Volume serial Number 
    short FSR;
    short FlagVol; //activeFAT  1, VOLUME DIRTY  1, media failrue 1, clear to zero 1, reserved 12
    char BytePerSector; // bytes in sector, -> 2pow
    char SectorPerCluster; // bytePerSecto + SecotPerCluster <= 25
    char NumberFats; // can be 1 o 2, 2 id textFats en uso
    char DriveSelect; 
    char PercentUse;
    char reserved[7];
    char BootCode[390];
    short BootSignature;
}__attribute((packed)) exFatBootSector;


int main(int argc,char *argv[]){
    int fd,exp;
    exFatBootSector boot;

    if(argc != 2){
        printf("Uso : %s <Image File System>\n",argv[0]);
        exit(1);
    }
    if((fd = open(argv[1],O_RDONLY)) <0)
        perror("No se pudo abrir la imagen del disco\n");
    
    if(read(fd,&boot,sizeof(boot))<0)
        perror("No se pudo leer imagen del disco\n");
    

    printf("Jump Code: %c%c%c\n", boot.jump[0], boot.jump[1], boot.jump[2]);
    printf("File System Name: %.8s\n", boot.FSName); // Se usa %.8s para limitar la salida a 8 caracteres
    printf("Chunk (debe ser 0x00): %.53s\n", boot.Chunk); // Se usa %.53s para limitar la salida a 53 caracteres
    printf("Offset de la partición (dirección de sector): %ld\n", boot.offsetPart);
    printf("Tamaño total del volumen en sectores: %ld\n", boot.sizeVol);
    printf("Dirección de sector de la primera FAT: %d\n", boot.FATOffset);
    printf("Tamaño de la FAT en sectores: %d\n", boot.FATlen);
    printf("Dirección de sector de la Región de Datos: %d\n", boot.ClusterHeapOffset);
    printf("Cantidad de clusters en el Heap de Clusters: %d\n", boot.ClusterCount);
    printf("Dirección del Cluster del directorio raíz: %d\n", boot.RootDirFirstCluster);
    printf("Número de serie del volumen: %d\n", boot.VSN);
    printf("FSR: %d\n", boot.FSR);
    printf("Flags del Volumen: %d\n", boot.FlagVol);
    printf("Bytes por sector (2^): %d\n", (int)pow(2.0, boot.BytePerSector)); // 2^BytePerSector
    printf("Sectores por cluster: %d\n", (int)pow(2.0, boot.SectorPerCluster)); // 2^SectorPerCluster
    printf("Número de FATs: %d\n", boot.NumberFats);
    printf("Seleccionador de unidad: %d\n", boot.DriveSelect);
    printf("Porcentaje de uso: %d%%\n", boot.PercentUse);
    printf("Reservado: %.7s\n", boot.reserved); // Se usa %.7s para limitar la salida a 7 caracteres
    printf("Código de arranque: %.390s\n", boot.BootCode); // Se usa %.390s para limitar la salida a 390 caracteres
    printf("Firma de arranque: 0x%04X\n", boot.BootSignature); // Impresión en formato hexadecimal

    close(fd);
    exit(0);

}