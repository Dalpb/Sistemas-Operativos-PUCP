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
    if(clusterNum >= boot.ClusterCount || clusterNum < 2 ){
        perror("No se ingresó un número de cluster válido\n");
        return 1;
    }
    
    //nos ubicamos en el clusterHeap , bitMap está ahi
    unsigned int clusterHeapLocation = boot.ClusterHeapOffset* (unsigned int)pow(2,boot.BytePerSector);

    off_t pos = lseek(fd,clusterHeapLocation,SEEK_SET);
    if(pos == -1){
        perror("No es posible hacer el desplazamiento");
        return 1;
    }
    
    char clusters[boot.ClusterCount]; //cada bit representa unn cluster, 0 libre y 1 ocupaddo

    if(read(fd,clusters,sizeof(clusters)) == -1){
        perror("Error en la lectura de los estados del cluster");
        return 1;
    } 
    //pasos
    int byteOffSet = (clusterNum - 2)/ 8; //ubico el rectangulo
    int bitOffSet = (clusterNum - 2 ) % 8; //ubico el bit del rectangulo


    char clusterState = clusters[byteOffSet*8 + bitOffSet];

    if(clusterState){
        printf("El cluster %d esta ocupado con %c \n", clusterNum,clusterState);
    }
    else{
        printf("El cluster %d esta libre\n", clusterNum);
    }

    exit(0);
}