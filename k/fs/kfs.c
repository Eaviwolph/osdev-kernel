#include <drivers/atapi.h>
#include <k/kfs.h>
#include <k/types.h>
#include <stdio.h>

static struct kfs_superblock superblock;
static struct kfs_inode root_inode;

// Using atapi to initialize the superblock
void kfs_init()
{
    init_atapi();
    printf("kfs_init\r\n");
    read_block(16, (u16 *)&superblock, sizeof(superblock));
    printf("superblock: %x\r\n", superblock);

    read_block(17, (u16 *)&root_inode, sizeof(root_inode));
    printf("root_inode: %x\r\n", root_inode);
}