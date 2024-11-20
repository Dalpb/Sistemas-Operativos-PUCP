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

#define ENDFILE  0xFFFFFFFF
#define NOTMENIGN  0x00000000
#define BADBLOCK 0XFFFFFFF7

int main(int argc,char *argv[]){
    int fd,exp;
    exFatBootSector boot;

    if(argc != 3){
        printf("Uso : %s <Image File System> <Cluster index>\n",argv[0]);
        exit(1);
    }
    if((fd = open(argv[1],O_RDONLY)) <0)
        perror("No se pudo abrir la imagen del disco\n");
    
    if(read(fd,&boot,sizeof(boot))<0)
        perror("No se pudo leer imagen del disco\n");

    int clusterNum = atoi(argv[2]);

    //no existen los clusters 0 y 1, empieza desde 2
    if(clusterNum >= boot.ClusterCount || clusterNum < 2 )
        perror("No se ingresó un número de cluster válido\n");
    
    unsigned int firstFATOffset =boot.FATOffset * (unsigned int)pow(2,boot.BytePerSector); //ubicamos el primer FAT
    
    off_t pos = lseek(fd,firstFATOffset,SEEK_SET);
    if(pos == -1){
        perror("No se realizó el desplazamiento correctamente");
        return 1;
    }
    
    int mediaType,alwaysThisValue; //los "clusters" 0 y 1
    if(read(fd,&mediaType,sizeof(mediaType)) == -1){
        perror("Error en la lectura de mediaType");
        return 1;
    }
    if(read(fd,&mediaType,sizeof(alwaysThisValue)) == -1){
        perror("Error en la lectura de alwaysThisValue");
        return 1;
    }

    unsigned int clusters[boot.ClusterCount];
    if(read(fd,clusters,sizeof(clusters)) == -1){
        perror("No se puede leer\n");
        return 1;
    }

    unsigned int valor = clusters[clusterNum];
    // printf("IMPRIMIMOS EL CLUSTERS");
    // for (int i = 0; i < boot.ClusterCount; i++) {
    // printf("Cluster %d: %u\n", i, clusters[i]);
    // }
    switch(valor){
        case 0:
            printf("El cluster %d está libre\n",clusterNum );
        break;
        case ENDFILE:
            printf("El cluster %d tiene marcado como fin de archivo",clusterNum);
            break;
        case BADBLOCK:
            printf("El cluster %d está marcado como bloque defectuoso\n", clusterNum);
            break;
        default:
            printf("El cluster %d está ocupado con valor %d\n",clusterNum,valor);
    }

    exit(0);
}